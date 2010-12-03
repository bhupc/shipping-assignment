#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <list>
#include <vector>
#include "PtrInterface.h"
#include "Ptr.h"
#include "Nominal.h"
#include "Types.h"
#include "Exceptions.h"
#include "Fleet.h"
#include <iostream>
using namespace std;

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
			Segment::Ptr returnSegment_;

			TransportType mode_;
			/* This is the listof the notifiees to be notified on events */
			vector<Segment::Notifiee*> notifiee_;

			PackageCount packageCount_;
			Capacity capacity_;


			  public:
			inline TransportType mode() const  { return mode_;}
			inline Capacity capacity(){return capacity_;}

		//	 inline shipmentsReceived(){};
		//	 	

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



			 Cost cost(Fleet::Ptr _fleet) { 
				Cost c(1.0);
				if(mode_ == TransportType::boat())
				{
					c = length_*(_fleet->cost(0));
				}
				if(mode_ == TransportType::plane())
				{
					c = length_*(_fleet->cost(1));

				}
				if(mode_ == TransportType::truck())
				{
					c = length_*(_fleet->cost(2));
				}

				// assume that by default there is always a truck
				else c = length_*(_fleet->cost(2));
				//cerr << "difficulty_.value = " << difficulty_.value() << "\n";
				return Cost(c.value()*difficulty_.value());
			}

			 Time time(Fleet::Ptr _fleet) {
				double factor  = 1;
				if(expediteSupport_) {factor= 1.5;}
				if(mode_ == TransportType::boat())
				{
					return length_/(_fleet->speed(0))/factor;
				}
				if(mode_ == TransportType::plane())
				{
					return length_/(_fleet->speed(1))/factor;
				}
				if(mode_ == TransportType::truck())
				{
					return length_/(_fleet->speed(2))/factor;
				}

				return length_/(_fleet->speed(2))/factor;
			}

      Capacity totalCapacity(Fleet::Ptr _fleet)
			{
			  
				if(mode_ == TransportType::boat())
				{
				  return capacity_*_fleet->capacity(0);
				}
	      
				if(mode_ == TransportType::plane())
				{
				  return capacity_*_fleet->capacity(1);
				}
	      
				if(mode_ == TransportType::truck())
				{
				  return capacity_*_fleet->capacity(2);
				}

				  return capacity_*_fleet->capacity(2);
			}


			Segment::Ptr returnSegment() const {return returnSegment_;}
			void returnSegmentIs(Segment::Ptr);
			void onReturnSegmentChange(Segment::Ptr);
			void notifieeIs(Notifiee* const _notifiee) { notifiee_.push_back(_notifiee);}
			void packageCountInc(PackageCount _count) { packageCount_ += _count;} 
			PackageCount packageCount() { return packageCount_;}
			Capacity capacity() const { return capacity_; }
			void capacityIs(Capacity _capacity) { capacity_=_capacity;}
			Cost transferCost(PackageCount _count, Fleet::Ptr _fleet)
			{
		          int capacity = totalCapacity(_fleet).value();
			  int count = _count.value();
			  unsigned int times = (count%capacity) ? ( (count/capacity) + 1):(count/capacity);
                          return Cost( times*(cost(_fleet)).value()); 
		          	      
			}
			Time transferTime(PackageCount _count, Fleet::Ptr _fleet)  { 
			  // Segment Capacity is number of packets 
        int capacity = totalCapacity(_fleet).value();
				int count = _count.value();
			  unsigned int times = (count%capacity) ? ( (count/capacity) + 1):(count/capacity);
				return Time( times*(time(_fleet)).value());
			}
			  public:
			Segment(const String& _name) : name_(_name) {
				expediteSupport_ = false;
				difficulty_ = Difficulty(1.0);
				length_ = Mile(1.0);
				capacity_ = Capacity(1);	
			}


    };

}
#endif
