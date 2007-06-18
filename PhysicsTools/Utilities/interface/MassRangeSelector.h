#ifndef RecoAlgos_MassRangeSelector_h
#define RecoAlgos_MassRangeSelector_h
/* \class MassRangeSelector
 *
 * \author Luca Lista, INFN
 *
 * $Id: MassRangeSelector.h,v 1.2 2007/01/31 14:42:59 llista Exp $
 */

struct MassRangeSelector {
  MassRangeSelector( double massMin, double massMax ) : 
    massMin_( massMin ), massMax_( massMax ) { }
  template<typename T>
  bool operator()( const T & t ) const { 
    double mass = t.mass();
    return ( mass >= massMin_ && mass <= massMax_ ); 
  }

private:
  double massMin_, massMax_;
};

#endif
