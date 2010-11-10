#ifndef __STATS_H__
#define __STATS_H__

#include "PtrInterface.h"
#include "Ptr.h"
#include "Segment.h"
#include "Types.h"
#include "Engine.h"

using namespace Fwk;

namespace Shipping
{
  class CustomerLocation;

  class Stats : public PtrInterface<Stats>, public Engine::Notifiee, public Segment::Notifiee
	{
	  public:

		typedef Fwk::Ptr<Stats> Ptr;
		typedef Fwk::Ptr<Stats const> PtrConst;
    
		//overrriding the methods in PtrInterface to solve the Diamond issue

		const PtrInterface<Stats>* newRef() const { return this->PtrInterface<Stats>::newRef();}
    void deleteRef() const { this->PtrInterface<Stats>::deleteRef();} 
		//accessors

    uint32_t segmentCount() const { return totalSegmentCount_;}
		uint32_t expeditedSegmentCount() const { return expeditedSegmentCount_;}
    uint32_t truckSegmentCount() const { return truckSegmentCount_;}
		uint32_t boatSegmentCount() const { return boatSegmentCount_; }
		uint32_t planeSegmentCount() const { return planeSegmentCount_; }
		
		uint32_t boatTerminalCount() const { return boatTerminalCount_;}
		uint32_t planeTerminalCount() const { return planeTerminalCount_;}
		uint32_t truckTerminalCount() const { return truckTerminalCount_;}
    uint32_t customerLocationCount() const {return customerLocationCount_;}
    uint32_t portCount() const { return portCount_;}
    

     Stats(const string& _name){
			name_ = _name;
		expeditedSegmentCount_ = 0;
		totalSegmentCount_ = 0;
		truckSegmentCount_ = 0;
		planeSegmentCount_ = 0;
		boatSegmentCount_ = 0;
		
		customerLocationCount_ = 0;
		portCount_ = 0;

		boatTerminalCount_ = 0;
		planeTerminalCount_ = 0;
		truckTerminalCount_ = 0;
    

		 }


	  void onSegmentNew(Segment::Ptr _segment){
	    totalSegmentCount_++;	
		}

		void onSegmentDel(Segment::Ptr _segment) 
		{
		  totalSegmentCount_--;
			if(_segment->expediteSupport()){ 
			  expeditedSegmentCount_--;  
			}
		  
		}
		void onSegmentModeIs(Segment::Ptr _segment)
		{
		  // Not handling the previous mode problem
		  if(_segment->mode() == TransportType::boat()) { boatSegmentCount_++;}
			else if(_segment->mode() == TransportType::plane()) { planeSegmentCount_++;}
			else if(_segment->mode() == TransportType::truck()){ truckSegmentCount_++;}
		}

		void onBoatTerminalNew(BoatTerminal::Ptr _location) {
		  boatTerminalCount_++;      
		}
		void onPlaneTerminalNew(PlaneTerminal::Ptr _location) {
		  planeTerminalCount_++;
		}
		void onTruckTerminalNew(TruckTerminal::Ptr _location) {
		  truckTerminalCount_++;
		}
	  
		void onBoatTerminalDel(BoatTerminal::Ptr _location) {
		  boatTerminalCount_--;
		}
		void onPlaneTerminalDel(PlaneTerminal::Ptr _location) {
		  planeTerminalCount_--;
		}
		void onTruckTerminalDel(TruckTerminal::Ptr _location) {
		  truckTerminalCount_--;
		}

		void onCustomerLocationNew(Fwk::Ptr<CustomerLocation> _location)
		{
		  customerLocationCount_++;
		}
		
		void onCustomerLocationDel(Fwk::Ptr<CustomerLocation> _location)
		{
		  customerLocationCount_--;
		}

    void onSegmentExpeditedIs(Segment::Ptr _segment, bool _expedited) {
		  if(_expedited)
			{
			  expeditedSegmentCount_++;
		  }
			else
			{
			  expeditedSegmentCount_--;
			}
		}


		void onPortNew(Port::Ptr _port)
		{
		  portCount_++;
		}

		void onPortDel(Port::Ptr _port)
		{
		  portCount_--;  
		}

		private:
    
		uint32_t expeditedSegmentCount_;
		uint32_t totalSegmentCount_;
		uint32_t truckSegmentCount_;
		uint32_t planeSegmentCount_;
		uint32_t boatSegmentCount_;
		
		uint32_t customerLocationCount_;
		uint32_t portCount_;

		uint32_t boatTerminalCount_;
		uint32_t planeTerminalCount_;
		uint32_t truckTerminalCount_;
    
		string name_;
	};

}

#endif
