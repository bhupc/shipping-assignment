#include "Segment.h"
#include "Location.h"
#include "Exceptions.h"

namespace Shipping
{

void Shipping::Segment::sourceIs(Location::Ptr _source)
{
  
	if(source_ == _source)
	{
	  return;
	}
	if(_source == NULL)
	{
	  return source_->onSegmentSourceDel(Segment::Ptr(this));
	}

	/* To be Changed ??*/
	if(source_){
		source_->onSegmentSourceDel(Segment::Ptr(this));
	}
	source_ = _source;
  	source_->onSegmentSourceChanged(Segment::Ptr(this));
}

void Segment::onReturnSegmentChange(Segment::Ptr _segment)
{
  returnSegment_ = _segment;  
}

void Segment::returnSegmentIs(Segment::Ptr _segment)
{
  if(returnSegment_ == _segment)
	{
	  return;
	}
  if(_segment == NULL)
	{
	  //returnSegment_->returnSegmentIs(NULL);
		returnSegment_->onReturnSegmentChange(NULL);
		returnSegment_ = NULL;
		return;
	}

   returnSegment_ = _segment;
   returnSegment_->onReturnSegmentChange(Segment::Ptr(this));
	 //returnSegment_->returnSegmentIs(Segment::Ptr(this));

}


}


