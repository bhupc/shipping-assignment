#include "Segment.h"
#include "Location.h"
#include "Exceptions.h"

namespace Shipping
{

void Shipping::Segment::sourceIs(Segment::Ptr _segment, Location::Ptr _source)
{
  source_ = _source;

	/* notify all the reactors */
  source_->onSegmentSourceChanged(_segment);
}



}


