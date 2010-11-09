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


  class Location : public Fwk::PtrInterface<Location>
  {
    /* Declaring Engine as friend so as to invoke the private constructors*/

	  friend class Engine;
    public:

      typedef Fwk::Ptr<Location> Ptr;
      typedef Fwk::Ptr<Location const> PtrConst;

		public:
  		/* put the segment at the offset */
      
			/* get the segment at the offset */

			virtual SegmentPtrConst segment(unsigned int offset) const {return NULL; }

      String name() const {return name_;}

      virtual TransportType type() const { return type_;}
			virtual void typeIs(TransportType _type) {type_ = TransportType::none();}
		
	 		virtual void segmentIs(unsigned int offset, SegmentPtrConst _segment) {}
      virtual void onSegmentSourceChanged(SegmentPtrConst _segment) throw (IllegalSegmentException){}
			
			protected:
      /* This is the global name of this location */
	    String name_;
      TransportType type_;
			vector<SegmentPtrConst> segment_;
		  
      
        
  };


  class CustomerLocation : public Location
  {
    friend class Engine;

    public:
      typedef Fwk::Ptr<CustomerLocation> Ptr;
	    typedef Fwk::Ptr<CustomerLocation const> PtrConst;
    
	    SegmentPtrConst segment(unsigned int) const ;
	    void segmentIs(unsigned int, SegmentPtrConst);
      void onSegmentSourceChanged(SegmentPtrConst _segment) throw (IllegalSegmentException);
    public:
	    CustomerLocation(const String& _name) { name_ = _name; type_ = TransportType::none(); }

  };

  class Port : public Location
  {
    friend class Engine;

    public:
      typedef Fwk::Ptr<Port> Ptr;
	    typedef Fwk::Ptr<Port const> PtrConst;
  
   	  SegmentPtrConst segment(unsigned int) const;
	    void segmentIs(unsigned int, SegmentPtrConst);
	    void onSegmentSourceChanged(SegmentPtrConst _segment) throw (IllegalSegmentException);
		public:
      Port(const String& _name) {name_= _name; type_ = TransportType::none();}
  };

  class Terminal : public Location
  {
    friend class Engine; 
 
	  public:
		  
  
      typedef Fwk::Ptr<Terminal> Ptr;
	    typedef Fwk::Ptr<Terminal const> PtrConst;
			inline TransportType type() const {return type_;}
	    inline void typeIs(TransportType _type)  {type_ = _type;}

			SegmentPtrConst segment(unsigned int) const;
	    void segmentIs(unsigned int, SegmentPtrConst);
			void onSegmentSourceChanged(SegmentPtrConst) throw (IllegalSegmentException);

	  public:
	    Terminal(const String& _name) {name_ = _name; type_ = TransportType::none();}
    

  };

}
#endif 
