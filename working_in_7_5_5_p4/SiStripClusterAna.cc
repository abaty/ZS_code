// -*- C++ -*-
// //
// // Package:    SiStripClusterAna
// // Class:      SiStripClusterAna
// // 
// /**\class SiStripClusterAna SiStripClusterAna.cc Validation/SiStripAnalyzer/src/SiStripClusterAna.cc
//  Description: <one line class summary>
//   Implementation:
//        <Notes on implementation>
//        */
//        //
//        // Original Author:  Ivan Amos Cali
//        //         Created:  Mon Jul 28 14:10:52 CEST 2008
//        // $Id: SiStripClusterAna.cc,v 1.1 2010/11/04 15:29:18 edwenger Exp $
//        //
//        //
//         
//
//         // system include files
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
//
//         // user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/EDCollection.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"

#include "DataFormats/SiStripDigi/interface/SiStripProcessedRawDigi.h"
#include "DataFormats/SiStripDigi/interface/SiStripRawDigi.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripClusterCollection.h"

#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripPedestalsSubtractor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripCommonModeNoiseSubtractor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripRawProcessingFactory.h"

#include "Geometry/CommonTopologies/interface/RectangularStripTopology.h"
#include "Geometry/CommonTopologies/interface/TrapezoidalStripTopology.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

//ROOT inclusion
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TList.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "THStack.h"


//
// class decleration
//

class SiStripClusterAna : public edm::EDAnalyzer {
    public:
        explicit SiStripClusterAna(const edm::ParameterSet&);
        ~SiStripClusterAna();


    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

        void initHistos();

        std::auto_ptr<SiStripPedestalsSubtractor>   subtractorPed_;
   //     uint32_t CentralityBin_;


        edm::InputTag srcBaseline_;
        edm::InputTag srcProcessedRawDigi_;

        edm::Service<TFileService> fs_;

        TH1D *trackNhits_;
        TH1D *trackPt_;
        TH1D *trackEta_;
        TH1D *trackPhi_;

        TH1D *trackNhitsValid_;
        TH1D *trackPtValid_;
        TH1D *trackEtaValid_;
        TH1D *trackPhiValid_;

        TH1D* h1BadAPVperEvent_;
        TH1D* h1BadAPVsPerModule_;
        TH1D* h1ClusterSizeAllAPVs_;
        TH1D* h1ClusterChargeAllAPVs_;
        TH1D* h1ClusterSizeBadAPVs_;
        TH1D* h1ClusterChargeBadAPVs_;
        TH1D* h1ClusterSizeGoodAPVs_;
        TH1D* h1ClusterChargeGoodAPVs_;
        TH1D* h1NHIPinStereo_;
        TH1D* h1SatStripsPerAPVAll_;
        TH1D* h1SatStripsPerAPVBad_;
        TH1D* h1SatStripsPerAPVGood_;

        TH2F* h2BadAPVVsEtaVsR_;        
        TH2F* h2BadAPVperEventVsCent_;

        TCanvas* Canvas_;
        TH1D* h1ProcessedRawDigis_;
        TH1D* h1Baseline_;
        TH1D* h1Clusters_;
        TH1D *h1BaselineOrig_;

        uint16_t nModuletoDisplay_;
        uint16_t actualModule_;
        bool doOnlySummaryPlots_;
};


SiStripClusterAna::SiStripClusterAna(const edm::ParameterSet& conf){

    actualModule_ =0;

    doOnlySummaryPlots_ = conf.getUntrackedParameter<bool>( "doOnlySummaryPlots",false);

    this->initHistos();

}


SiStripClusterAna::~SiStripClusterAna()
{



}

void SiStripClusterAna::analyze(const edm::Event& e, const edm::EventSetup& es)
{
    using namespace edm;


   // edm::Handle<int> cbin_;
   // e.getByLabel("centralityBin","HFtowersTrunc",cbin_);
   // CentralityBin_ = *cbin_;
   // std::cout << "cen " << CentralityBin_ << std::endl;

    edm::ESHandle<TrackerGeometry> tracker;
    es.get<TrackerDigiGeometryRecord>().get( tracker );
    const TrackerGeometry &trGeo(*tracker);


/*    edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleBaseline;
    e.getByLabel(srcBaseline_, moduleBaseline);

    edm::Handle< edm::DetSetVector<SiStripRawDigi> > moduleRawDigi;
    e.getByLabel(srcProcessedRawDigi_,moduleRawDigi);*/

    edm::Handle<edmNew::DetSetVector<SiStripCluster> > clusters;
    edm::InputTag clusLabel("siStripClusters");
    e.getByLabel(clusLabel, clusters);

    char detIds[20];
    char evs[20];
    char runs[20];    

    TFileDirectory sdClusters_= fs_->mkdir("Clusters");   

    //looping over clusters
    //            //------------------------------------------------------------------------------------------------------------------------------------------------------------
    edmNew::DetSetVector<SiStripCluster>::const_iterator itClusters = clusters->begin();

    uint32_t spdet[] = {369124478, 436245673, 470390120, 470390181, 369125549, 402664745, 436233293, 470149029, 436295092, 470410860};
    std::vector<uint32_t> specialDetids;
    for(int i=0; i<10; i++){
        specialDetids.push_back(spdet[i]);
    }
    if(!doOnlySummaryPlots_){
        edm::Handle<edm::EDCollection<DetId> > digis;
        edm::InputTag digiLabel("siStripDigis");
        e.getByLabel(digiLabel, digis);
        edm::EDCollection<DetId>::const_iterator digiDetIds = digis->begin();
        for( ; digiDetIds != digis->end(); digiDetIds++){

            for (itClusters=clusters->begin(); itClusters != clusters->end(); ++itClusters ){
                std::vector<uint32_t>::iterator it =  std::find(specialDetids.begin(),specialDetids.end(),itClusters->detId());
                if(itClusters->detId() == digiDetIds->rawId() || it!=specialDetids.end()){
                    //std::cout << "detId: " << digiDetIds->rawId() << std::endl;

                    uint32_t detId = itClusters->detId();
                    uint32_t event = e.id().event();
                    uint32_t run = e.id().run();

                    sprintf(detIds,"%ul", detId);
                    sprintf(evs,"%ul", event);
                    sprintf(runs,"%ul", run);
                    char* dHistoName = Form("Id:%s_run:%s_ev:%s",detIds, runs, evs);
                    h1Clusters_ = sdClusters_.make<TH1D>(dHistoName,dHistoName, 768, -0.5, 767.5);

                    h1Clusters_->SetXTitle("strip#"); h1Clusters_->SetYTitle("ADC"); h1Clusters_->SetMaximum(1024.); h1Clusters_->SetMinimum(-300.);  h1Clusters_->SetLineWidth(2); h1Clusters_->SetLineStyle(2); h1Clusters_->SetLineColor(3);

                    for ( edmNew::DetSet<SiStripCluster>::const_iterator clus = itClusters->begin(); clus != itClusters->end(); ++clus){
                        int strip=clus->firstStrip();
                        for( std::vector<uint8_t>::const_iterator itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
                            h1Clusters_->Fill(strip, *itAmpl);

                            strip++;
                        }
                    }
                }
            }
        }
    }
    for (itClusters=clusters->begin(); itClusters != clusters->end(); ++itClusters ){
        for ( edmNew::DetSet<SiStripCluster>::const_iterator clus = itClusters->begin(); clus != itClusters->end(); ++clus){
            //std::cout << "geographic id: " << clus->geographicalId() << "clusterId: "<< itClusters->detId() << "digiId: " << digiDetIds->rawId() << std::endl;

            int strip=clus->firstStrip();
            //uint16_t stAPVn = strip/128, APVn;
            uint32_t clSize=0, clCharge=0; 
            for( std::vector<uint8_t>::const_iterator itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
                //APVn = strip/128;
                /*if(APVn != stAPVn){
                    bool Restored =false;
                    //for(size_t i=0; i< vRestoredAPV.size(); ++i)if(stAPVn==vRestoredAPV[i]) Restored=true;
                    if(Restored){
                        h1ClusterSizeBadAPVs_->Fill(clSize);
                        h1ClusterChargeBadAPVs_->Fill(clCharge);
                    }else{
                        h1ClusterSizeGoodAPVs_->Fill(clSize);
                        h1ClusterChargeGoodAPVs_->Fill(clCharge);
                    }
                    if(clSize> 70){
                        std::cout << "APVn: "<< APVn << " stAPVn: "<< stAPVn << " detId: " << itClusters->detId() << std::endl;
                    }
                    h1ClusterSizeAllAPVs_->Fill(clSize);
                    h1ClusterChargeAllAPVs_->Fill(clCharge);

                    clSize=0;
                    clCharge=0;
                    stAPVn=APVn;
                }*/
                //if(itClusters->detId() == digiDetIds->rawId()){
                //h1Clusters_->Fill(strip, *itAmpl);
                ++clSize;
                clCharge += *itAmpl;
                //}
                ++strip;
            }

            if(clSize>0){  //chCharge not needed because already implemented
                bool Restored =false;
                //for(size_t i=0; i< vRestoredAPV.size(); ++i) if(APVn==vRestoredAPV[i])Restored = true;

                if(Restored){
                    h1ClusterSizeBadAPVs_->Fill(clSize);
                    h1ClusterChargeBadAPVs_->Fill(clCharge);
                }else{
                    h1ClusterSizeGoodAPVs_->Fill(clSize);
                    h1ClusterChargeGoodAPVs_->Fill(clCharge);
                }
                h1ClusterSizeAllAPVs_->Fill(clSize);
                h1ClusterChargeAllAPVs_->Fill(clCharge);
            }



        }              
    }

}


// ------------ method called once each job just before starting event loop  ------------
void SiStripClusterAna::beginJob()
{  


}

// ------------ method called once each job just after ending the event loop  ------------
void 
SiStripClusterAna::endJob() {





}

void SiStripClusterAna::initHistos(){

    h1BadAPVperEvent_ = fs_->make<TH1D>("BadModulesPerEvent","BadAPVPerEvent", 20001, -0.5, 20000.5); //done
    h1BadAPVperEvent_->SetXTitle("# Modules with Bad APVs");
    h1BadAPVperEvent_->SetYTitle("Entries");
    h1BadAPVperEvent_->SetLineWidth(2);
    h1BadAPVperEvent_->SetLineStyle(2);

    h1BadAPVsPerModule_ = fs_->make<TH1D>("BadAPVsPerModule", "BadAPVsPerModule", 7, -0.5, 6.5) ;  //done
    h1BadAPVsPerModule_->SetXTitle("# Bad APVs per module");
    h1BadAPVsPerModule_->SetYTitle("Entries");
    h1BadAPVsPerModule_->SetLineWidth(2);
    h1BadAPVsPerModule_->SetLineStyle(2);

    h1NHIPinStereo_= fs_->make<TH1D>("NHIPinStereo", "NHIPinStereo", 11, -0.5, 10.5);
    h1NHIPinStereo_->SetXTitle("# HIPs in Stereo");
    h1NHIPinStereo_->SetYTitle("Entries");
    h1NHIPinStereo_->SetLineWidth(2);
    h1NHIPinStereo_->SetLineStyle(2);

    h1SatStripsPerAPVAll_= fs_->make<TH1D>("SatStripPerAPVAll", "SatStripPerAPV All", 41, -0.5, 40.5);     //done
    h1SatStripsPerAPVAll_->SetXTitle("# Saturatd Strip / APV");
    h1SatStripsPerAPVAll_->SetYTitle("Entries");
    h1SatStripsPerAPVAll_->SetLineWidth(2);
    h1SatStripsPerAPVAll_->SetLineStyle(2);

    h1SatStripsPerAPVBad_= fs_->make<TH1D>("SatStripPerAPVBad", "SatStripPerAPV Bad", 41, -0.5, 40.5);  //done
    h1SatStripsPerAPVBad_->SetXTitle("# Saturatd Strip / APV");
    h1SatStripsPerAPVBad_->SetYTitle("Entries");
    h1SatStripsPerAPVBad_->SetLineWidth(2);
    h1SatStripsPerAPVBad_->SetLineStyle(2);

    h1SatStripsPerAPVGood_= fs_->make<TH1D>("SatStripPerAPVGood", "SatStripPerAPV Good", 41, -0.5, 40.5); //done
    h1SatStripsPerAPVGood_->SetXTitle("# Saturatd Strip / APV");
    h1SatStripsPerAPVGood_->SetYTitle("Entries");
    h1SatStripsPerAPVGood_->SetLineWidth(2);
    h1SatStripsPerAPVGood_->SetLineStyle(2);

    h1ClusterSizeAllAPVs_= fs_->make<TH1D>("ClusterSizeAllAPV", "Cluster Size All APVs", 128, 1, 128); //done
    h1ClusterSizeAllAPVs_->SetXTitle("Cluster Size [strips]");
    h1ClusterSizeAllAPVs_->SetYTitle("Entries");
    h1ClusterSizeAllAPVs_->SetLineWidth(2);
    h1ClusterSizeAllAPVs_->SetLineStyle(2);
    h1ClusterSizeAllAPVs_->Sumw2();

    h1ClusterChargeAllAPVs_= fs_->make<TH1D>("ClusterChargeAllAPV", "Cluster Charge All APVs" , 30001, 1., 30000.); //done
    h1ClusterChargeAllAPVs_->SetXTitle("Cluster charge [adc]");
    h1ClusterChargeAllAPVs_->SetYTitle("Entries");
    h1ClusterChargeAllAPVs_->SetLineWidth(2);
    h1ClusterChargeAllAPVs_->SetLineStyle(2);
    h1ClusterChargeAllAPVs_->Sumw2();

    h1ClusterSizeBadAPVs_= fs_->make<TH1D>("ClusterSizeBadAPV", "Cluster Size Bad APVs", 128, 1, 128); //done
    h1ClusterSizeBadAPVs_->SetXTitle("Cluster Size [strips]");
    h1ClusterSizeBadAPVs_->SetYTitle("Entries");
    h1ClusterSizeBadAPVs_->SetLineWidth(2);
    h1ClusterSizeBadAPVs_->SetLineStyle(2);

    h1ClusterChargeBadAPVs_= fs_->make<TH1D>("ClusterChargeBadAPV", "Cluster Charge Bad APVs", 30001, 1., 30000.); //done
    h1ClusterChargeBadAPVs_->SetXTitle("Cluster charge [adc]");
    h1ClusterChargeBadAPVs_->SetYTitle("Entries");
    h1ClusterChargeBadAPVs_->SetLineWidth(2);
    h1ClusterChargeBadAPVs_->SetLineStyle(2);

    h1ClusterSizeGoodAPVs_= fs_->make<TH1D>("ClusterSizeGoodAPV", "Cluster Size Good APVs", 128, 1, 128);  //done
    h1ClusterSizeGoodAPVs_->SetXTitle("Cluster Size [strips]");
    h1ClusterSizeGoodAPVs_->SetYTitle("Entries");
    h1ClusterSizeGoodAPVs_->SetLineWidth(2);
    h1ClusterSizeGoodAPVs_->SetLineStyle(2);

    h1ClusterChargeGoodAPVs_= fs_->make<TH1D>("ClusterChargeGoodAPV", "Cluster Charge Good APVs", 30001, 1., 30000.); //done
    h1ClusterChargeGoodAPVs_->SetXTitle("Cluster charge [adc]");
    h1ClusterChargeGoodAPVs_->SetYTitle("Entries");
    h1ClusterChargeGoodAPVs_->SetLineWidth(2);
    h1ClusterChargeGoodAPVs_->SetLineStyle(2);

}
DEFINE_FWK_MODULE(SiStripClusterAna);
