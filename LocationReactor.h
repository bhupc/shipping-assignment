#ifndef __LOCATION_REACTOR_H__
#define __LOCATION_REACTOR_H__

#include "Types.h"
#include "Location.h"
#include "Activity.h"
#include "Exceptions.h"
#include "Conn.h"
#include "Fleet.h"

#include <map>
using namespace std;
namespace Shipping
{

class LocationReactor : public Location::Notifiee, public Activity::Notifiee
{
  public:
  LocationReactor(Location::Ptr _location, Activity::Manager::Ptr _manager, Conn::Ptr _conn, Fleet::Ptr _fleet) : Location::Notifiee(_location) , manager_(_manager), conn_(_conn), fleet_(_fleet) 
	{
	  totalActivities_ = 0;  
		first_ = true;
		packageDelivered_ = 0;

    vector<SegmentPtr> segments = location_->segments();
		vector<SegmentPtr>::iterator it = segments.begin();

		for( ; it != segments.end() ; it++)
		{
		  lastScheduled_[(*it)->name()] = Time::nil();  
		}

  }


  void onPackageCountInc(PackageCount, Cost, Time, Location::Ptr, uint32_t);
  void onPackageCountDelivered(PackageCount, Cost, Time, Location::Ptr, uint32_t);
  Time averageLatency() { return manager_->now().value()/packageDelivered_.value();}  
	PackageCount packageCountDelivered() { return packageDelivered_;}
  
  class TimeComp : public binary_function<Time, Time, bool>
	{
	  public:
		  TimeComp() {}

			bool operator()(Time t1, Time t2) const
			{
			  return ( t1.value() > t2.value() );
			}
	};

  void shipmentIdIs(uint32_t id)
	{
	  shipmentId_.push_back(id);
	}
	uint32_t shipmentId(int index)
	{
	  return shipmentId_[index];
	}



	private:
	Activity::Ptr injectActivity_;
  Activity::Manager::Ptr manager_;
	Conn::Ptr conn_;
	Fleet::Ptr fleet_;
	unsigned int totalActivities_;
  map<String, Time> lastScheduled_;
	//Time lastScheduled_;
	bool first_;
	PackageCount packageDelivered_;
	vector<uint32_t> shipmentId_;
  const string getNewActivityName(); 
	void scheduleNewActivity(PackageCount, Location::Ptr, Cost, Time, Location::Ptr, uint32_t) throw (DestinationUnreachableException);
	void scheduleNewActivityInt(Segment::Ptr, PackageCount, Location::Ptr, Cost, Time, Location::Ptr,  uint32_t);
	void scheduleInjectActivity();
	void onStatus();
  Conn::Path getBestPath(Location::Ptr src, Location::Ptr dest, Conn::PathList pathList, PackageCount);
	Conn::Path getLeastTimeDJPath(Conn::PathList, PackageCount);
	Conn::Path getLeastTimeGDPath(Conn::PathList, PackageCount);
	Time getPathTime(Conn::Path, PackageCount);
	void updateToNow();
  void scheduleAckPackage(Location::Ptr, uint32_t);
	
};

}

#endif
