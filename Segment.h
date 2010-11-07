#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <list>
#include "PtrInterface.h"
#include "Ptr.h"
#include "Nominal.h"
#include "Types.h"
#include "Location.h"
#include "Exceptions.h"

using namespace Shipping;

typedef Fwk::Ptr<Location> LocationPtr;

namespace Shipping
{

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
					/* This is the protected constructor */
					NotifieeConst() {}

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
		  list<NotifieeConst> _notifiee;


			public:
        inline TransportType mode() const  { return mode_;}
				inline void modeIs(TransportType _mode) {mode_ = _mode;}

        inline String  name() const {return name_; }
        LocationPtr location() const { return source_;}
        Mile length() const {return length_;}
        Difficulty difficulty() const {return difficulty_;}
        bool expediteSupport() const {return expediteSupport_; }
        Segment::PtrConst returnSegment() const {return returnSegment_;}
     public:
		    Segment(const String& _name) : name_(_name) {}
	};

}
#endif
