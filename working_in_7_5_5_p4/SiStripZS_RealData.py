# Auto generated configuration file
# using: 
# Revision: 1.222.2.6 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: hiRecoDM -n 10 --scenario HeavyIons -s RAW2DIGI,L1Reco,RECO --processName TEST --datatier GEN-SIM-RECO --eventcontent FEVTDEBUG --customise SimGeneral.DataMixingModule.DataMixer_DataConditions_3_8_X_data2010 --cust_function customise --geometry DB --filein file:DMRawSimOnReco_DIGI2RAW.root --fileout hiRecoDM_RECO.root --conditions FrontierConditions_GlobalTag,MC_38Y_V12::All --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('hiRecoDM nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)
#process.Timing = cms.Service("Timing")
#process.MessageLogger.cerr.threshold = cms.untracked.string("DEBUG")
#process.MessageLogger.categories+=cms.vstring("SiStripFedCMExtractor","SiStripProcessedRawDigiSkimProducer")

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/express/Run2010B/ExpressPhysics/FEVT/Express-v2/000/146/417/10F981FF-5EC6-DF11-9657-0030486733B4.root'
    #'file:../testGenSimOnReco/SingleZmumu_MatchVertexDM_DIGI2RAW.root'
    #'file:DMRawSimOnReco_DIGI2RAW.root'
    #'file:DMRawSimOnReco_DIGI2RAW.root'
	#'/store/data/Run2010B/HeavyIonTest/RAW/v1/000/146/421/E6B24CF0-5EC6-DF11-B52D-00304879FC6C.root'
    #'file:/data/abaty/VirginRaw_CentralitySkims/VirginRAW_2010_HICorePhysics_SKIM_Cent_0_5_1.root',
    'file:/data/abaty/VirginRaw_CentralitySkims/VirginRAW_2010_HICorePhysics_SKIM_Cent_0_5_1.root'
    #'file:/data/abaty/VirginRaw_CentralitySkims/VirginRAW_2010_HICorePhysics_SKIM_Cent_0_5_10.root',
    #'file:/data/abaty/VirginRaw_CentralitySkims/VirginRAW_2010_HICorePhysics_SKIM_Cent_25_50_102.root',
    #'file:/data/abaty/VirginRaw_CentralitySkims/VirginRAW_2010_HICorePhysics_SKIM_Cent_50_100_104.root'
   )
)

#process.source = cms.Source("NewEventStreamFileReader",
#fileNames = cms.untracked.vstring('root://eoscms.cern.ch//store/group/phys\_heavyions/TrackerStudies/run260499/run260499_ls0004_streamStage1_StorageManager.dat'
#)
#)

#process.source = cms.Source("NewEventStreamFileReader",
#fileNames = cms.untracked.vstring('file:Data.00148514.0021.A.storageManager.01.0000.dat'
#)
#)


# Output definition
process.RECOoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    #outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('hiReco_E6B24CF0-5EC6-DF11-B52D-00304879FC6C_10ev.root'),
	#fileName = cms.untracked.string('test.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RECO')
    )
)

# Additional output definition
#process.RECOoutput.outputCommands.extend(['keep *_siStripProcessedRawDigisSkim_*_*',
#                                               'keep *_*_APVCM_*'])

# Other statements
#process.GlobalTag.globaltag = 'GR_R_73_V3A'
#process.GlobalTag.globaltag = 'GR_R_39X_V1::All'
#process.GlobalTag.globaltag = 'MC_39Y_V4::All'


#GT Customization for 7_5_3_p1
process.GlobalTag = cms.ESSource( "PoolDBESSource",    
#    globaltag = cms.string( "74X_dataRun2_HLT_frozen_v1" ),
#    globaltag = cms.string( "75X_mcRun2_asymptotic_v6" ),
     globaltag = cms.string( "75X_dataRun2_Prompt_v1" ),


    RefreshEachRun = cms.untracked.bool( True ),
    RefreshOpenIOVs = cms.untracked.bool( False ),
    toGet = cms.VPSet(
    ),
    DBParameters = cms.PSet(
      authenticationPath = cms.untracked.string( "." ),
      connectionRetrialTimeOut = cms.untracked.int32( 60 ),
      idleConnectionCleanupPeriod = cms.untracked.int32( 10 ),
      messageLevel = cms.untracked.int32( 0 ),
      enablePoolAutomaticCleanUp = cms.untracked.bool( False ),
      enableConnectionSharing = cms.untracked.bool( True ),
      enableReadOnlySessionOnUpdateConnection = cms.untracked.bool( False ),
      connectionTimeOut = cms.untracked.int32( 0 ),
      connectionRetrialPeriod = cms.untracked.int32( 10 )
    ),
    RefreshAlways = cms.untracked.bool( False ),
    connect = cms.string( "frontier://(proxyurl=http://localhost:3128)(serverurl=http://localhost:800\
0/FrontierOnProd)(serverurl=http://localhost:8000/FrontierOnProd)(retrieve-ziplevel=0)/CMS_CONDITIONS\
" ),
    ReconnectEachRun = cms.untracked.bool( True ),
    BlobStreamerName = cms.untracked.string( "TBufferBlobStreamingService" ),
    DumpStat = cms.untracked.bool( False )
)


if 'GlobalTag' in process.__dict__:
    from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag
    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = '75X_dataRun2_Prompt_v1')
    #process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = '75X_mcRun2_asymptotic_v6')
#    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = '74X_dataRun2_HLT_frozen_v1')
    #process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'GR_R_53_LV6')
    process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_CONDITIONS'
    process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')
    for pset in process.GlobalTag.toGet.value():
        pset.connect = pset.connect.value().replace('frontier://FrontierProd/', 'frontier://FrontierProd/')
    # fix for multi-run processing                                                                    
    process.GlobalTag.RefreshEachRun = cms.untracked.bool( False )
    process.GlobalTag.ReconnectEachRun = cms.untracked.bool( False )

## Offline Silicon Tracker Zero Suppression
from RecoLocalTracker.SiStripZeroSuppression.DefaultAlgorithms_cff import *
process.siStripZeroSuppression.Algorithms.PedestalSubtractionFedMode = cms.bool(False)
process.siStripZeroSuppression.Algorithms.CommonModeNoiseSubtractionMode = cms.string("IteratedMedian")
process.siStripZeroSuppression.doAPVRestore = cms.bool(True)
process.siStripZeroSuppression.produceRawDigis = cms.bool(True)
process.siStripZeroSuppression.produceCalculatedBaseline = cms.bool(True)
process.siStripZeroSuppression.storeCM = cms.bool(True)
process.siStripZeroSuppression.storeInZScollBadAPV = cms.bool(True)


process.TFileService = cms.Service("TFileService",
        fileName=cms.string("7_5_manyAPVs.root"))

process.baselineAna = cms.EDAnalyzer("SiStripBaselineAnalyzer",
        Algorithms = DefaultAlgorithms,
        srcBaseline =  cms.InputTag('siStripZeroSuppression','BADAPVBASELINEVirginRaw'),
        srcBaselinePoints =  cms.InputTag('siStripZeroSuppression','BADAPVBASELINEPOINTSVirginRaw'),
        srcAPVCM  =  cms.InputTag('siStripZeroSuppression','APVCMVirginRaw'),
        #srcProcessedRawDigi =  cms.InputTag('siStripZeroSuppression','VirginRaw'),
        srcProcessedRawDigi =  cms.InputTag('siStripDigis','VirginRaw'),
        nModuletoDisplay = cms.uint32(200),
        plotClusters = cms.bool(True),
        plotBaseline = cms.bool(True),
        plotBaselinePoints = cms.bool(True),
        plotRawDigi     = cms.bool(True),
        plotAPVCM   = cms.bool(True),
        plotPedestals = cms.bool(False)
)
    

								  
# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.siStripDigis)
process.reconstruction_step = cms.Path(process.striptrackerlocalreco+process.baselineAna)
#process.reconstruction_step = cms.Path(process.trackerlocalreco)#+process.baselineAna)
#process.reconstruction_step = cms.Path(process.striptrackerlocalreco)
#process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
#process.Timer_step = cms.Path(process.myTimer)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.hipmonitor_step, process.RECOoutput_step)
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step, process.RECOoutput_step)
# customisation of the process
'''
def customise(process):
    process.stripConditions = cms.ESSource("PoolDBESSource",
            process.CondDBSetup,
            timetype = cms.untracked.string('runnumber'),
            connect = cms.string('frontier://PromptProd/CMS_COND_31X_STRIP'),
            toGet = cms.VPSet(
                cms.PSet(
                    record = cms.string('SiStripNoisesRcd'),
                    tag = cms.string('SiStripNoise_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripPedestalsRcd'),
                    tag = cms.string('SiStripPedestals_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripFedCablingRcd'),
                    tag = cms.string('SiStripFedCabling_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripBadChannelRcd'),
                    tag = cms.string('SiStripBadChannel_FromOnline_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripLatencyRcd'),
                    tag = cms.string('SiStripLatency_GR10_v2_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripThresholdRcd'),
                    tag = cms.string('SiStripThreshold_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripBadFiberRcd'),
                    tag = cms.string('SiStripBadChannel_FromOfflineCalibration_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripBadModuleRcd'),
                    tag = cms.string('SiStripBadChannel_FromOfflineAnalysis_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripBadStripRcd'),
                    tag = cms.string('SiStripBadChannel_FromPromptReaction_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripConfObjectRcd'),
                    tag = cms.string('SiStripShiftAndCrosstalk_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripLorentzAngleRcd'),
                    tag = cms.string('SiStripLorentzAngle_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripApvGain2Rcd'),
                    tag = cms.string('SiStripApvGain_FromParticles_GR10_v1_hlt')
                    ),
                cms.PSet(
                    record = cms.string('SiStripApvGainRcd'),
                    tag = cms.string('SiStripApvGain_GR10_v1_hlt')
                    )
            )
    )

    process.es_prefer_strips = cms.ESPrefer("PoolDBESSource","stripConditions")
   
    return(process)
process = customise(process)'''
