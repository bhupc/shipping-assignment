#include <vector>
#include "Engine.h"
#include "Stats.h"
#include "Conn.h"

using namespace Shipping;

 Engine::Engine()
{
  stats_ = Fwk::Ptr<Stats>(new Stats("_engine_stats_"));  
  this->notifieeIs(stats_.ptr());


  conn_ = Fwk::Ptr<Conn>(new Conn("_engine_conn_"));

}

void Engine::Notifiee::notifierIs(Engine::Ptr _notifier)
{
  if(notifier_ == _notifier)
	{
	  return;
	}

  notifier_ = _notifier;

  notifier_->newNotifiee(this); 
  //notifier_->newNotifiee(const_cast<Engine::NotifieeConst*>(this));	

}

void Engine::newNotifiee(Engine::Notifiee* _notifiee)
{
  notifiee_.push_back(_notifiee);
}

Segment::Ptr Engine::SegmentNew(const String& name)
{
  Segment::Ptr m = Segment::Ptr(new Segment(name));
  m->notifieeIs(stats_.ptr()); 
  vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onSegmentNew(m);
	}

	return m;
}

CustomerLocation::Ptr Engine::CustomerLocationNew(const String& name)
{
  CustomerLocation::Ptr m = CustomerLocation::Ptr(new CustomerLocation(name));
  	
	vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onCustomerLocationNew(m);
	}

	
	return m;
}

Port::Ptr Engine::PortNew(const String& name)
{
  Port::Ptr m = Port::Ptr(new Port(name));
  
	vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onPortNew(m);
	}


	return m;
}

BoatTerminal::Ptr Engine::BoatTerminalNew(const String& name)
{
  BoatTerminal::Ptr m = BoatTerminal::Ptr(new BoatTerminal(name));
  
	vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onBoatTerminalNew(m);
	}

 
	return m;
}

Fleet::Ptr Engine::FleetNew(const String& name)
{
  Fleet::Ptr m = Fleet::Ptr(new Fleet(name));
        return m;
}

Stats::Ptr Engine::StatsNew(const String& name)
{
  
	return stats_;
 /*
   Fwk::Ptr<Stats> m = Fwk::Ptr<Stats>(new Stats(name));
        return m;
				*/
}

Conn::Ptr Engine::ConnNew(const String& name)
{
  return conn_;
}



PlaneTerminal::Ptr Engine::PlaneTerminalNew(const String& name)
{
  PlaneTerminal::Ptr m = PlaneTerminal::Ptr(new PlaneTerminal(name));
	
	vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onPlaneTerminalNew(m);
	}
	return m;
}


TruckTerminal::Ptr Engine::TruckTerminalNew(const String& name)
{
  TruckTerminal::Ptr m = TruckTerminal::Ptr(new TruckTerminal(name));
 	
	vector<Engine::Notifiee*>::iterator it = notifiee_.begin();
	for(; it != notifiee_.end(); it++)
	{
	  (*it)->onTruckTerminalNew(m);
	}


	return m;
}




