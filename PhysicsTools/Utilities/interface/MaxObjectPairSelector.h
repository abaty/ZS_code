#ifndef RecoAlgos_MaxObjectPairSelector_h
#define RecoAlgos_MaxObjectPairSelector_h
/* \class MaxObjectPairSelector
 *
 * \author Luca Lista, INFN
 *
 * $Id: MaxObjectPairSelector.h,v 1.2 2007/01/31 14:42:59 llista Exp $
 */

template<typename F>
struct MaxObjectPairSelector {
  MaxObjectPairSelector( double max ) : 
    max_( max ), fun_() { }
  template<typename T1, typename T2>
  bool operator()( const T1 & t1, const T2 & t2 ) const { 
    return fun_( t1, t2 ) <= max_;
  }

private:
  double max_;
  F fun_;
};

#endif
