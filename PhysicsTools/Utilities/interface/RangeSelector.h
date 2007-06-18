#ifndef RecoAlgos_RangeSelector_h
#define RecoAlgos_RangeSelector_h
/* \class RangeSelector
 *
 * \author Luca Lista, INFN
 *
 * $Id: RangeSelector.h,v 1.2 2007/01/31 14:42:59 llista Exp $
 */
#include <string>

template<typename T, double (T::*fun)() const>
struct RangeSelector {
  RangeSelector( double min, double max ) : 
    min_( min ), max_( max ) { }
  bool operator()( const T & t ) const { 
    double x = (t.*fun)();
    return min_ <= x && x <= max_; 
  }
private:
  double min_, max_;
};

#endif
