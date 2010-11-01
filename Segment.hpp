#ifndef __SEGMENT_HPP__
#define __SEGMENT_HPP__

#include "PtrInterface.h"


  class Segment : public Fwk::PtrInterface
	{
	  public:
		  /* Just to hide details, we typedef the smart pointer. Both the const and non const versions */
		  typedef Fwk::Ptr<Segement> SegmentPtr;
	    typedef Fwk::Ptr<Segment const> SegmentConstPtr;

			/* The notifiee class for the Segment */

			class NotifieeConst : public Fwk::PtrInterface
			{
		    	
				typedef Fwk::Ptr<Notifiee const> NotifieeConstPtr;
			
			  public:

				/* Public constructor. I have no idea what to do here*/
          NotifieeConst(SegmentConstPtr);
				/* The events for which to send out notifications */

         /* This informs the notifiee when a new segment is created in the 
				    system. */
				  virtual void onSegmentNew() {}

					/* this informs the notifiee when an existing segment is deleted from teh system*/
					virtual void onSegmentDel() {}
					

			};





	  private:

		  enum Mode
			{
			  truck_ = 0,
				boat_ = 1,
				plane = 2
			};
      /* This is the global name of the Segment */
			String _name;

			/* This is the mode of transportation on this segment */
      Location _source;

			/* This is the length of the segment ,ie. src -> dest */
			Mile _length;

			/* This is the difficulty level of transportation on this segment*/
      Difficulty _difficulty;

			/* Tells whether this segment supports expedite support or not*/
			bool _expediteSupport;

			/* This is a smart pointer to the return segment of this segment. Making it a const for now */
      SegmentConstPtr _returnSegment;
      
			/* This is the list of the notifiees to be notified on events */
		  List<Notifiee> _notifiee;	
			

			




			public:
        static inline Mode truck() {return truck_ ;}
				static inline Mode boat() { return boat_;}
        static inline Mode plane() { return plane_ ;}

        
	};
#endif
