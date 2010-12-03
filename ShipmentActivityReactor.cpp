#include "ShipmentActivityReactor.h"


namespace Shipping
{
  void ShipmentActivityReactor::onStatus()
	{
    std::cerr << "activity_->status = " << activity_->status() << "\n\n" ;
	  if( activity_->status() != Activity::free)  return;
    // this is to keep the segment stats
		std::cerr << "\n\n Activity Done \n\n"; 
    segment_->packageCountInc(packageCount_);
    
		// this will call the src location reactor
		segment_->source()->packageCountDec(packageCount_);
		
		//this will call the destination location reactor
		// set the destination for this location
    Location::Ptr nextSrc = segment_->returnSegment()->source();
		if(nextSrc == destination_)
		{
		  std::cerr << "DESTINATION " << destination_->name() << " REACHED!!!" << std::endl;
			std::cerr << "Delivered " << packageCount_.value() << "packets. " << std::endl;
			nextSrc->packageCountDelivered(packageCount_, cummulativeCost_);
			return;
		}
		std::cerr << "The destiination for this segment is " << nextSrc->name() << std::endl;
		nextSrc->destinationIs(destination_);
		nextSrc->packageCountInc(packageCount_, cummulativeCost_);

	}
}
