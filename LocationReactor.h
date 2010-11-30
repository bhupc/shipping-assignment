#ifndef __LOCATION_REACTOR_H__
#define __LOCATION_REACTOR_H__

#include "Types.h"
#include "Location.h"
#include "Activity.h"
#include "Exceptions.h"
#include "Conn.h"

using namespace std;
namespace Shipping
{

class LocationReactor : public Location::Notifiee, public Activity::Notifiee
{
  public:
  LocationReactor(Location::Ptr _location, Activity::Manager::Ptr _manager, Conn::Ptr _conn) : Location::Notifiee(_location) , manager_(_manager), conn_(_conn) 
	{
	  totalActivities_ = 0;  
		lastScheduled_ = Time::nil();
	}


  void onPackageCountInc(PackageCount);
  
	private:
	Activity::Ptr injectActivity_;
  Activity::Manager::Ptr manager_;
	Conn::Ptr conn_;
	unsigned int totalActivities_;
	Time lastScheduled_;
  const string getNewActivityName(); 
	void scheduleNewActivity(PackageCount, Location::Ptr) throw (DestinationUnreachableException);
	void scheduleNewActivityInt(Segment::Ptr, PackageCount, Location::Ptr);
	void scheduleInjectActivity();
	void onStatus();
  Conn::Path getBestPath(Location::Ptr src, Location::Ptr dest, Conn::PathList pathList);
	
};

}

#endif
