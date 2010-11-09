#include <vector>
#include "Engine.h"

using namespace Shipping;

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
	return m;
}

CustomerLocation::Ptr Engine::CustomerLocationNew(const String& name)
{
  CustomerLocation::Ptr m = CustomerLocation::Ptr(new CustomerLocation(name));
	return m;
}

Port::Ptr Engine::PortNew(const String& name)
{
  Port::Ptr m = Port::Ptr(new Port(name));
	return m;
}
Terminal::Ptr Engine::TerminalNew(const String& name)
{
  Terminal::Ptr m = Terminal::Ptr(new Terminal(name));
	return m;
}



