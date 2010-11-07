#include "Segment.h"
#include "Location.h"
#include <vector>
#include <iostream>

using namespace std;


namespace Shipping
{

  SegmentPtrConst CustomerLocation::segment(unsigned int offset) const 
  {
    return segment_[offset];  
  }

  void CustomerLocation::segmentIs(unsigned int offset, SegmentPtrConst _segment)
  {
       
  }



  SegmentPtrConst Port::segment( unsigned int offset ) const {
	  return segment_[offset];
	}

  void Port::segmentIs(unsigned int offset, SegmentPtrConst _segment)
  {
	     
	}

  SegmentPtrConst Terminal::segment(unsigned int offset) const {
	
	  return segment_[offset];
	}
  
	
	void Terminal::segmentIs(unsigned int offset, SegmentPtrConst _segment) {
	  /* Throw error in case the segment mode is not the same as the terminal type */
		if( (this->type() != TransportType::none()) && (_segment->mode() != this->type()))
		{
      //throw IncompatibleSegmentException("Got an incompatible Segment : TerminalType = " + this->type() + ", Segment Mode = " + _segment->mode());		
		}

		/* If we never had a segment attached to this terminal */
		if(type_ == TransportType::none())
		{
		  type_ = _segment->mode();
		}
    
		vector<SegmentPtrConst>::iterator it;
		segment_.insert(it + offset, _segment);
	}
}


