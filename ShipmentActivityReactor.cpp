#include "ShipmentActivityReactor.h"


namespace Shipping
{
  void ShipmentActivityReactor::onStatus()
	{
    // this is to keep the segment stats
    segment_->packageCountInc(packageCount_);
    
		// this will call the src location reactor
		segment_->source()->packageCountDec(packageCount_);
		
		//this will call the destination location reactor
		segment_->returnSegment()->source()->packageCountInc(packageCount_);
    
	}
}
