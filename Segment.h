#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <list>
#include "PtrInterface.h"
#include "Ptr.h"
#include "Nominal.h"
#include "Types.h"
#include "Location.h"
 
class Mile : public Ordinal<Mile, unsigned int>
{
  public:
	  Mile(unsigned int val) : Ordinal<Mile, unsigned int>(val) {}   
};


class Difficulty : public Ordinal<Difficulty, float>
{
  public:
    Difficulty(float val) : Ordinal<Difficulty, float>(val) {}
	      
};


class Segment : public Fwk::PtrInterface<Segment>
{
	  public:
		  /* Just to hide details, we typedef the smart pointer. Both the const and non const versions */
		  typedef Fwk::Ptr<Segment> Ptr;
	    typedef Fwk::Ptr<Segment const> PtrConst;

			/* The notifiee class for the Segment */

			class NotifieeConst : public Fwk::PtrInterface<NotifieeConst>
			{
		    	
			  public:
				  
				  typedef Fwk::Ptr<NotifieeConst> Ptr;
			    typedef Fwk::Ptr<NotifieeConst const> PtrConst;

			    String name() const {return (notifier_ ? notifier_->name() : String()) ;}
					Segment::PtrConst notifier() const {return notifier_;}
					virtual void notifierIs(const Segment::PtrConst&);
					void lrNextIs(NotifieeConst* _lrNext)
					{
					  lrNext_ = _lrNext;
					}
					static NotifieeConst::Ptr NotifieeConstIs()
					{
					  Ptr m = new NotifieeConst();
						
						return m;
					}
				/* The events for which to send out notifications */

         /* This informs the notifiee when a new segment is created in the 
				    system. */
				  virtual void onSegmentNew() {}

					/* this informs the notifiee when an existing segment is deleted from teh system*/
					virtual void onSegmentDel() {}
					
        protected:
				  /* This is the reference to the notifier */
				  Segment::PtrConst notifier_;
					/* This is the next of the notifies in the notifiee  list */
					NotifieeConst* lrNext_;
					/* This is the protected constructor */
					NotifieeConst() {lrNext_ = 0;}

			};

			class Notifiee : public NotifieeConst
			{
				public:
          
			    typedef Fwk::Ptr<Notifiee> Ptr;
				  typedef Fwk::Ptr<Notifiee const> PtrConst;
          
					Segment::PtrConst notifier() const { return NotifieeConst::notifier();}
					Segment::Ptr notifier() { return const_cast<Segment*>(NotifieeConst::notifier().ptr()); }
          
					static Notifiee::Ptr NotifieeIs()
					{
					  Ptr m = new Notifiee();
					  
						return m;
					}

					protected:

					Notifiee() {}
			
			};







	  private:

		  enum Mode
			{
			  truck_ = 0,
				boat_ = 1,
				plane_ = 2
			};
      /* This is the global name of the Segment */
			String name_;

			/* This is the mode of transportation on this segment */
      Location _source;

			/* This is the length of the segment ,ie. src -> dest */
			Mile length_;

			/* This is the difficulty level of transportation on this segment*/
      Difficulty _difficulty;

			/* Tells whether this segment supports expedite support or not*/
			bool expediteSupport_;

			/* This is a smart pointer to the return segment of this segment. Making it a const for now */
			Segment::PtrConst returnSegment_;
      
			/* This is the listof the notifiees to be notified on events */
		  list<NotifieeConst> _notifiee;	


			public:
        static inline Mode truck() {return truck_ ;}
	static inline Mode boat() { return boat_;}
        static inline Mode plane() { return plane_ ;}
        
        inline String  name() const {return name_; }
        
	};
#endif
