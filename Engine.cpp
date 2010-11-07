#include <vector>
#include "Engine.h"

using namespace Shipping;

void Engine::NotifieeConst::notifierIs(const Engine::PtrConst& _notifier)
{
  if(notifier_ == _notifier)
	{
	  return;
	}

  notifier_ = _notifier;

  //_notifier->newNotifiee(const_cast<Engine::NotifieeConst*>(this));	
}

void Engine::newNotifiee(const Engine::NotifieeConst* _notifiee)
{
  notifiee_.push_back(_notifiee);
}

Segment::Ptr SegmentNew(const String& name)
{
  Segment::Ptr m = Segment::Ptr(new Segment(name));
	return m;
}

CustomerLocation::Ptr CustomerLocationNew(const String& name)
{
  CustomerLocation::Ptr m = CustomerLocation::Ptr(new CustomerLocation(name));
	return m;
}

Port::Ptr PortNew(const String& name)
{
  Port::Ptr m = Port::Ptr(new Port(name));
	return m;
}
Terminal::Ptr TerminalNew(const String& name)
{
  Terminal::Ptr m = Terminal::Ptr(new Terminal(name));
	return m;
}



