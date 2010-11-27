#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "PtrInterface.h"
#include "Ptr.h"
#include "Types.h"
#include "Segment.h"
#include "Exceptions.h"

#include <vector>

using namespace std;

namespace Shipping 
{

	class Engine;
  typedef Fwk::Ptr<Segment> SegmentPtr;
  typedef Fwk::Ptr<Segment const> SegmentPtrConst;


  class Location : virtual public Fwk::PtrInterface<Location>
  {
    /* Declaring Engine as friend so as to invoke the private constructors*/

	  friend class Engine;
    public:

      typedef Fwk::Ptr<Location> Ptr;
      typedef Fwk::Ptr<Location const> PtrConst;
     
		public:

		  class Notifiee
			{
			  public:
        Notifiee(Location::Ptr _location) : location_(_location) {}

				virtual void onPackageCountInc(PackageCount _count) {}
			  
				protected:
				Location::Ptr location_;
			};
  		/* put the segment at the offset */
      
			/* get the segment at the offset */

			virtual SegmentPtr segment(unsigned int offset) const {return NULL; }
      virtual vector<SegmentPtr> segments() const { return segment_;}
      String name() const {return name_;}

      virtual TransportType type() const { return type_;}
			virtual uint32_t locType() const {return locType_;}
			virtual void typeIs(TransportType _type) {type_ = TransportType::none();}
      		
	 		virtual void segmentIs(unsigned int offset, SegmentPtr _segment) {}
      virtual void onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException){
			   
			}
			virtual void onSegmentSourceDel(SegmentPtr _segment)
			{

			  // Find the segment and delete it
			  vector<SegmentPtr> :: iterator it = segment_.begin();
				for(; it != segment_.end(); it++)
				{
				  if(_segment == (*it)) 
					{
	           segment_.erase(it);
						 return;
					}
				}
			}
      
			void notifieeIs(Notifiee* _notifiee)
			{
			  notifiee_.push_back(_notifiee);
			}
			
			PackageCount packageCount() { return packageCount_;}
			void packageCountIs(PackageCount _count) { packageCount_ = _count;}
			void packageCountInc(PackageCount);
			void packageCountDec(PackageCount _count) {packageCount_ -= _count;}
			Location::Ptr destination() const { return destination_;}
			void destinationIs(Location::Ptr _destination) { destination_=_destination;}
			protected:
      /* This is the global name of this location */
	    String name_;
      TransportType type_;
			vector<SegmentPtr> segment_;
		  uint32_t locType_;
			vector<Notifiee*> notifiee_;
      
			PackageCount packageCount_; 
      Location::Ptr destination_;        
  };


  class CustomerLocation : public Location
  {
    friend class Engine;

    public:
      typedef Fwk::Ptr<CustomerLocation> Ptr;
	    typedef Fwk::Ptr<CustomerLocation const> PtrConst;
    
	    SegmentPtr segment(unsigned int) const ;
	    void segmentIs(unsigned int, SegmentPtr);
      void onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException);
    public:
	    CustomerLocation(const String& _name) { name_ = _name; type_ = TransportType::none(); locType_ = 0;}

  };

  class Port : public Location
  {
    friend class Engine;

    public:
      typedef Fwk::Ptr<Port> Ptr;
	    typedef Fwk::Ptr<Port const> PtrConst;
  
   	  SegmentPtr segment(unsigned int) const;
	    void segmentIs(unsigned int, SegmentPtr);
	    void onSegmentSourceChanged(SegmentPtr _segment) throw (IllegalSegmentException);
		public:
      Port(const String& _name) {name_= _name; type_ = TransportType::none(); locType_ = 1;}
  };

  class Terminal : public Location
  {
    friend class Engine; 
 
	  public:
		  
  
      typedef Fwk::Ptr<Terminal> Ptr;
	    typedef Fwk::Ptr<Terminal const> PtrConst;
			inline TransportType type() const {return type_;}
	    inline void typeIs(TransportType _type)  {type_ = _type;}

			SegmentPtr segment(unsigned int) const;
	    void segmentIs(unsigned int, SegmentPtr);
			void onSegmentSourceChanged(SegmentPtr) throw (IllegalSegmentException);

	  public:
	    Terminal(const String& _name) {name_ = _name; type_ = TransportType::none(); locType_ = 2;}
    

  };

	class BoatTerminal : public Terminal
	{
	  friend class Engine;
		public:
		typedef Fwk::Ptr<BoatTerminal> Ptr;
		typedef Fwk::Ptr<BoatTerminal const> PtrConst;

		public:
		BoatTerminal(const String& name) : Terminal(name) {type_ = TransportType::boat();}

	};

class PlaneTerminal : public Terminal
	{
	  friend class Engine;
		public:
		typedef Fwk::Ptr<PlaneTerminal> Ptr;
		typedef Fwk::Ptr<PlaneTerminal const> PtrConst;

		public:
		PlaneTerminal(const String& name) : Terminal(name) {type_ = TransportType::plane();}

	};

class TruckTerminal : public Terminal
	{
	  friend class Engine;
		public:
		typedef Fwk::Ptr<TruckTerminal> Ptr;
		typedef Fwk::Ptr<TruckTerminal const> PtrConst;

		public:
		TruckTerminal(const String& name) : Terminal(name) {type_ = TransportType::truck();}

	};



}
#endif 
