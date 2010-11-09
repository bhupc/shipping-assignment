#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <list>
#include "PtrInterface.h"
#include "Ptr.h"
#include "Nominal.h"
#include "Types.h"
#include "Exceptions.h"



namespace Shipping
{
    class Location;

    typedef Fwk::Ptr<Location> LocationPtr;
    class Segment : public Fwk::PtrInterface<Segment>
    {
	  public:
		  /* Just to hide details, we typedef the smart pointer. Both the const and non const versions */
		  typedef Fwk::Ptr<Segment> Ptr;
      typedef Fwk::Ptr<Segment const> PtrConst;

			/* The notifiee class for the Segment */

			  private:
      /* This is the global name of the Segment */
			String name_;

			/* This is the mode of transportation on this segment */
      LocationPtr source_;

			/* This is the length of the segment ,ie. src -> dest */
			Mile length_;

			/* This is the difficulty level of transportation on this segment*/
      Difficulty difficulty_;

			/* Tells whether this segment supports expedite support or not*/
			bool expediteSupport_;

			/* This is a smart pointer to the return segment of this segment. Making it a const for now */
			Segment::PtrConst returnSegment_;

      TransportType mode_;
			/* This is the listof the notifiees to be notified on events */


			public:
        inline TransportType mode() const  { return mode_;}
				inline void modeIs(TransportType _mode) {mode_ = _mode;}

        inline String  name() const {return name_; }
        inline LocationPtr source() const {return source_;}
				void sourceIs(Segment::Ptr, LocationPtr); 
				Mile length() const {return length_;}
				void lengthIs(Mile _length) { length_ = _length;}
        Difficulty difficulty() const {return difficulty_;}
				void difficultyIs(Difficulty _difficulty) { difficulty_ = _difficulty;}
        bool expediteSupport() const {return expediteSupport_; }
				void expediteSupportIs(bool _expediteSupport) { expediteSupport_ = _expediteSupport;}

        Segment::PtrConst returnSegment() const {return returnSegment_;}
        void returnSegmentIs(Segment::PtrConst _segment) { returnSegment_ = _segment;}
     public:
		    Segment(const String& _name) : name_(_name) {}
	};

}
#endif
