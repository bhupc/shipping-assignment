#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <list>
#include <vector>
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

      class Notifiee: virtual public Fwk::PtrInterface<Notifiee>
	    {
	      typedef Fwk::Ptr<Notifiee> NPtr;
		    
				protected:
		    Segment::Ptr notifier_;

		    public:
        Notifiee(){}
        Segment::Ptr notifier() const { return notifier_; }
        void notifierIs(Segment::Ptr engine);
		    static Notifiee::NPtr NotifieeIs()
		    {
			    NPtr m = new Notifiee();
			    return m;
		    }


		     /*Events relevant here */
         virtual void onSegmentExpeditedIs(Segment::Ptr _segment, bool _expedited) {}

         virtual void onSegmentModeIs(Segment::Ptr _segment) {}
		 	 };

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
      vector<Segment::Notifiee*> notifiee_;

			public:
        inline TransportType mode() const  { return mode_;}

				inline void modeIs(TransportType _mode) {
				  if(_mode == mode_) { return;}
				  mode_ = _mode;

				  vector<Segment::Notifiee*> ::iterator it = notifiee_.begin();
					for(; it != notifiee_.end(); it++)
					{
					  (*it)->onSegmentModeIs(Ptr(this));
					}

				}

        inline String  name() const {return name_; }
        inline LocationPtr source() const {return source_;}
				void sourceIs(LocationPtr); 
				Mile length() const {return length_;}
				void lengthIs(Mile _length) { length_ = _length;}
        Difficulty difficulty() const {return difficulty_;}
				void difficultyIs(Difficulty _difficulty) { difficulty_ = _difficulty;}
        bool expediteSupport() const {return expediteSupport_; }
				
				void expediteSupportIs(bool _expediteSupport) { 
				   if(_expediteSupport != expediteSupport_)
					 {
					   expediteSupport_ = _expediteSupport;
						 vector<Segment::Notifiee*> ::iterator it = notifiee_.begin();
						 for(; it != notifiee_.end(); it++)
						 {
						   (*it)->onSegmentExpeditedIs(Ptr(this), expediteSupport_);
						 }
					 }
				}

        Segment::PtrConst returnSegment() const {return returnSegment_;}
        void returnSegmentIs(Segment::PtrConst _segment) { returnSegment_ = _segment;}
				void notifieeIs(Notifiee* const _notifiee) { notifiee_.push_back(_notifiee);}
     public:
		    Segment(const String& _name) : name_(_name) {
					expediteSupport_ = false;
				}
	};

}
#endif
