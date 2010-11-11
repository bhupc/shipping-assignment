#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Ptr.h"
#include "PtrInterface.h"
#include "Instance.h"
#include "Segment.h"
#include "Location.h"
#include "Fleet.h"
#include <vector>

using namespace std;
namespace Shipping {

	class Stats;
	class Conn;
// Create your rep/engine interface here.
  
 class Engine : public Fwk::PtrInterface<Engine>
 {
   public:
   typedef Fwk::Ptr<Engine> Ptr;
	 typedef Fwk::Ptr<Engine const> PtrConst;
   
	 public:

   static Fwk::Ptr<Engine> EngineIs()
	 {
	   return Fwk::Ptr<Engine>(new Engine());
	 }
	 
	 class Notifiee: virtual public Fwk::PtrInterface<Notifiee>
	 {
	   typedef Fwk::Ptr<Notifiee> NPtr;
		 protected:
		 Engine::Ptr notifier_;

		 public:
     Notifiee(){}
		 ~Notifiee(){}
     Engine::Ptr notifier() const { return notifier_; }
     void notifierIs(Engine::Ptr engine);
		 static Notifiee::NPtr NotifieeIs()
		 {
			 NPtr m = new Notifiee();
			 return m;
		 }

		 

		 /*Events relevant here */

		 virtual void onBoatTerminalNew(BoatTerminal::Ptr){}
		 virtual void onPlaneTerminalNew(PlaneTerminal::Ptr){}
		 virtual void onTruckTerminalNew(TruckTerminal::Ptr){}
       
     virtual void onBoatTerminalDel(BoatTerminal::Ptr){}
		 virtual void onPlaneTerminalDel(PlaneTerminal::Ptr){}
		 virtual void onTruckTerminalDel(TruckTerminal::Ptr){}
     
		 virtual void onPortNew(Port::Ptr){}
		 virtual void onPortDel(Port::Ptr){}

     virtual void onCustomerLocationNew(CustomerLocation::Ptr) {}
     virtual void onCustomerLocationDel(CustomerLocation::Ptr) {}
		 
		 virtual void onSegmentNew(Segment::Ptr){}
		 virtual void onSegmentDel(Segment::Ptr){}

	 };

	void newNotifiee(Engine::Notifiee*);
  protected:

	vector<Engine::Notifiee*> notifiee_;
  Fwk::Ptr<Stats> stats_;
	Fwk::Ptr<Conn> conn_;

	Engine();
  public:
	void notifieeIs(Engine::Notifiee* _notifiee) { notifiee_.push_back(_notifiee);}
/* Call this to add a new segment to this shipping engine */
	Segment::Ptr SegmentNew(const String& name);
	/* invoke the following in order to created diff types of Locations in the shipping engine */
	CustomerLocation::Ptr CustomerLocationNew(const String& name);
	Port::Ptr PortNew(const String&);
  	Fleet::Ptr FleetNew(const String&); 
	TruckTerminal::Ptr TruckTerminalNew(const String&);
	BoatTerminal::Ptr BoatTerminalNew(const String&);
	PlaneTerminal::Ptr PlaneTerminalNew(const String&);
	Fwk::Ptr<Stats> StatsNew(const String&);
	Fwk::Ptr<Conn> ConnNew(const String&);
 };
  

} /* end namespace */

#endif
