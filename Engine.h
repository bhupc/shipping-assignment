#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Ptr.h"
#include "PtrInterface.h"
#include "Instance.h"
#include "Segment.h"
#include "Location.h"
#include <vector>

using namespace std;
namespace Shipping {

// Create your rep/engine interface here.
  
 class Engine : public Fwk::PtrInterface<Engine>
 {
   public:
   typedef Fwk::Ptr<Engine> Ptr;
	 typedef Fwk::Ptr<Engine const> PtrConst;
   
	 public:

	 
	 class Notifiee: public Fwk::PtrInterface<Notifiee>
	 {
	   typedef Fwk::Ptr<Notifiee> Ptr;
		 protected:
		 Engine::Ptr notifier_;

		 public:
     Notifiee(){}
     Engine::Ptr notifier() const { return notifier_; }
     void notifierIs(Engine::Ptr engine);
		 static Notifiee::Ptr NotifieeIs()
		 {
			 Ptr m = new Notifiee();
			 return m;
		 }


		 /* Events relevant here */

		 virtual void onLocationNew(Location::Ptr){}
		 virtual void onLocationDel(Location::Ptr){}

		 virtual void onSegmentNew(Segment::Ptr){}
		 virtual void onSegmentDel(Segment::Ptr){}

	 };

	void newNotifiee(Engine::Notifiee*);
  protected:

	vector<const Engine::Notifiee*> notifiee_;

	/* Call this to add a new segment to this shipping engine */
	Segment::Ptr SegmentNew(const String& name);
	/* invoke the following in order to created diff types of Locations in the shipping engine */
	CustomerLocation::Ptr CustomerLocationNew(const String& name);
	Port::Ptr PortNew(const String&);
	Terminal::Ptr TerminalNew(const String&);
 
 };
  

} /* end namespace */

#endif
