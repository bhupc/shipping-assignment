#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "PtrInterface.h"
#include "Ptr.h"
#include "Types.h"

#include <vector>

using namespace std;


class Segment;
typedef Fwk::Ptr<Segment> SegmentPtr;
typedef Fwk::Ptr<Segment const> SegmentPtrConst;


class Location : public Fwk::PtrInterface<Location>
{

  typedef Fwk::Ptr<Location> Ptr;
  typedef Fwk::Ptr<Location const> PtrConst;


	private:
	  
	  /* This is the global name of this location */
	  String name_;
    vector<SegmentPtr> segment_;
	  	

		public:

		  class NotifieeConst : public Fwk::PtrInterface<NotifieeConst>
			{
			  public:
				  typedef Fwk::Ptr<NotifieeConst> Ptr;
			    typedef Fwk::Ptr<NotifieeConst const> PtrConst;

			    String name() const {return (notifier_ ? notifier_->name() : String()) ;}
			    Location::PtrConst notifier() const {return notifier_;}
					virtual void notifierIs(const Location::PtrConst&);
					void lrNextIs(NotifieeConst* _lrNext)
					{
					  lrNext_ = _lrNext;
					}
					static NotifieeConst::Ptr NotifieeConstIs()
					{
					  Ptr m = new NotifieeConst();
						return m;
					}

			   /* The events for which to send out the notifications */

				 /* Inform us when there is a new location */
				 virtual void onLocationNew() {}
				 virtual void onLocationDel() {}
        protected:
			    Location::PtrConst notifier_;
				  NotifieeConst* lrNext_;
				  NotifieeConst() {lrNext_ = 0;}



			};

		  class Notifiee : public NotifieeConst
			{
			  public:
				  typedef Fwk::Ptr<Notifiee> Ptr;
				  typedef Fwk::Ptr<Notifiee const> PtrConst;

					Location::Ptr notifier() const {return const_cast<Location*>(NotifieeConst::notifier().ptr()); }

					static Notifiee::Ptr NotifieeIs()
					{
					  Ptr m = new Notifiee();
						return m;
					}
			   protected:
          
					  Notifiee() {}
					 
			};

		  /* put the segment at the offset */
			virtual void segmentIs(unsigned int offset, SegmentPtr _segment);
      
			/* get the segment at the offset */

			virtual void segment(unsigned int offset) const;

      String name() const {return name_;}
     
};

#endif 
