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
   typedef Fwk::Ptr<Engine> Ptr;
	 typedef Fwk::Ptr<Engine const> PtrConst;
   
	 public:

	 class NotifieeConst : public Fwk::PtrInterface<NotifieeConst>
	 {
	   protected:
		 Engine::PtrConst notifier_;
		 NotifieeConst() {}

		 public:

		 typedef Fwk::Ptr<NotifieeConst> Ptr;
		 typedef Fwk::Ptr<NotifieeConst const> PtrConst;
     
     Engine::PtrConst notifier() const { return notifier_; }
     void notifierIs(const Engine::PtrConst& engine);
		 static NotifieeConst::Ptr NotifieeConstIs()
		 {
			 Ptr m = new NotifieeConst();
			 return m;
		 }


		 /* Events relevant here */

		 virtual void onLocationNew(Location::Ptr){}
		 virtual void onLocationDel(Location::Ptr){}

		 virtual void onSegmentNew(Segment::Ptr){}
		 virtual void onSegmentDel(Segment::Ptr){}

	 };

	 class Notifiee : public NotifieeConst
	 {
	   protected:
		 Engine::PtrConst notifier_;
		 Notifiee();
	   public:
		   typedef Fwk::Ptr<Notifiee> Ptr;
			 typedef Fwk::Ptr<Notifiee const> PtrConst;

			 Engine::Ptr notifier() const {return const_cast<Engine*>(NotifieeConst::notifier().ptr()); }

			 static Notifiee::Ptr NotifieeIs()
			 {
			   Ptr m = new Notifiee();
				 return m; 
			 }
			 
	 };


	void newNotifiee(const Engine::NotifieeConst*);
  protected:

	vector<const Engine::NotifieeConst*> notifiee_;

	/* Call this to add a new segment to this shipping engine */
	Segment::Ptr SegmentNew(const String& name);
	/* invoke the following in order to created diff types of Locations in the shipping engine */
	CustomerLocation::Ptr CustomerLocationNew(const String& name);
	Port::Ptr PortNew(const String&);
	Terminal::Ptr TerminalNew(const String&);
 
 };
  

} /* end namespace */

#endif
