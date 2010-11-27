#ifndef __SHIPMENT_ACTIVITY_H__
#define __SHIPMENT_ACTIVITY_H__


#include "ActivityImpl.h"

namespace Shipping
{
  class ShipmentActivity : public Shipping::ActivityImpl
  {
    public:
	  typedef Fwk::Ptr<ShipmentActivity> Ptr;
    PackageCount packageCount() { return packageCount_;}
	  void packageCountIs(PackageCount _packageCount) { packageCount_ = _packageCount;}
	
	  private:
    PackageCount packageCount_;
  };

}
#endif
