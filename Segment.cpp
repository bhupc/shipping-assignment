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
	  return source_->onSegmentSourceDel(Segment::PtrConst(this));
	}

	source_ = _source;

  source_->onSegmentSourceChanged(Segment::PtrConst(this));
}

void Segment::returnSegmentIs(Segment::Ptr _segment)
{
  if(returnSegment_ == _segment)
	{
	  return;
	}

	returnSegment_ = _segment;
	_segment->returnSegmentIs(returnSegment_);

}

}


