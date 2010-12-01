#include "ShipmentActivityReactor.h"


namespace Shipping
{
  void ShipmentActivityReactor::onStatus()
	{
    std::cerr << "activity_->status = " << activity_->status() << "\n\n" ;
	  if( activity_->status() != 0)  return;
    // this is to keep the segment stats
		std::cerr << "\n\n Activity Done \n\n"; 
    segment_->packageCountInc(packageCount_);
    
		// this will call the src location reactor
		segment_->source()->packageCountDec(packageCount_);
		
		//this will call the destination location reactor
		segment_->returnSegment()->source()->packageCountInc(packageCount_);
    
	}
}
