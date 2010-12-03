#include "Segment.h"
#include "Location.h"
#include "Exceptions.h"
#include <vector>
#include <iostream>

using namespace std;


namespace Shipping
{
  
	void Location::packageCountInc(PackageCount _packageCount, Cost _cost, Time _time)
	{
    packageCount_ += _packageCount;
    // inform the notifieeIs

		for(unsigned int i = 0; i < notifiee_.size() ; i++)
		{
		  notifiee_[i]->onPackageCountInc(_packageCount, _cost, _time);
		}
	}
  
	void Location::packageCountDelivered(PackageCount _packageCount, Cost _cumulativeCost, Time _cummulativeTime)
	{
    //packageCount_ += _packageCount;
    // inform the notifieeIs

		for(unsigned int i = 0; i < notifiee_.size() ; i++)
		{
		  notifiee_[i]->onPackageCountDelivered(_packageCount, _cumulativeCost, _cummulativeTime);
		}
	}



  SegmentPtr CustomerLocation::segment(unsigned int offset) const 
  {
    return segment_[offset];  
  }

  void CustomerLocation::segmentIs( unsigned int offset, SegmentPtr _segment ) {
	  
		// Not used now
	}


	void CustomerLocation::onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException)
	{
	  segment_.push_back(_segment);
	}


  SegmentPtr Port::segment( unsigned int offset ) const {
	  return segment_[offset];
	}

  void Port::segmentIs( unsigned int offset, SegmentPtr _segment ) {
	   // Not usednow
	}


	void Port::onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException)
	{
        
    segment_.push_back(_segment);             	
	
	}
  

  SegmentPtr Terminal::segment(unsigned int offset) const {
	
	  return segment_[offset];
	}
  
  
	
	void Terminal::segmentIs(unsigned int offset, SegmentPtr _segment) {
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
    
		vector<SegmentPtr>::iterator it;
		segment_.insert(it + offset, _segment);
	}

	void Terminal::onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException)
	{
 	  if( (this->type() != TransportType::none()) && (_segment->mode() != this->type()))
		{
      throw IllegalSegmentException("Got an incompatible Segment");		
		}

		/* If we never had a segment attached to this terminal */
		if(type_ == TransportType::none())
		{
		  type_ = _segment->mode();
		}
    
		segment_.push_back(_segment);
       
	}
    

}


