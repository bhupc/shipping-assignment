#include "LocationReactor.h"
#include "ShipmentActivityReactor.h"
#include <sstream>


using namespace std;

namespace Shipping
{

void LocationReactor::onPackageCountInc(PackageCount _count)
{
  PackageCount newPackageCount = _count;
  Location::Ptr destination = location_->destination(); 
  scheduleNewActivity(newPackageCount, destination);
}


void LocationReactor::scheduleInjectActivity()
{
  
  if(!injectActivity_)
	{
	  // Create a new inject activity
		// FIXME append the location name with this activity name
		injectActivity_ = manager_->activityNew("InjectActivity");
		injectActivity_->lastNotifieeIs(this);
	}
  // Time is always in hours
  injectActivity_->nextTime(manager_->now() + Time(24));
	manager_->lastActivityIs(injectActivity_);
}

void LocationReactor::onStatus()
{
  scheduleInjectActivity();
	// FIXME increment the packet count here

}


void LocationReactor::scheduleNewActivityInt(Segment::Ptr _segment, PackageCount _count, Location::Ptr _dest)
{

  const string name = getNewActivityName();
	Activity::Ptr act = manager_->activityNew(name);
  ShipmentActivityReactor::Ptr sar = ShipmentActivityReactor::ShipmentActivityReactorNew(manager_, act, _segment);
	sar->packageCountIs(_count);
	sar->destinationIs(_dest);
	//Assuming that we are transfering package size <= segment capacity
	Time transferTime = _segment->transferTime(_count);
  Time t = lastScheduled_ + transferTime;
	if(t >= manager_->now())
	{
	  // Increase the refuse count for this segment to be this activity 
    // FIXME
	}
	act->nextTimeIs(t);
	lastScheduled_ = t;
	act->lastNotifieeIs(sar.ptr());

	manager_->lastActivityIs(act);

	totalActivities_++;
}


void LocationReactor::scheduleNewActivity(PackageCount _count, Location::Ptr destination) throw (DestinationUnreachableException)
{
  if(_count == 0)
	{
	  return;
	}
	Conn::PathList pathList = conn_->path(location_, destination);
  
	//Get the best path from the path list for the given source and diestina
	Conn::Path p = getBestPath(location_, destination, pathList);
  
  // What if there is no path from this location to the destination
	if(pathList.empty())
	{
	  stringstream strstream;
		strstream << "Could not fine path from " << location_->name() << " to " << destination->name() << std::endl;
	  throw DestinationUnreachableException(strstream.str());
	}
	//Now take the first segment in the best path
  	
	Segment::Ptr nextSeg = p[0];
  
  
	scheduleNewActivityInt(nextSeg, _count, destination);        

  //unsigned int capacity = (unsigned int)(nextSeg->capacity().value());	
  
  
  //unsigned int total = (_count.value() % capacity) ? (_count.value()/capacity) + 1 : (_count.value()/capacity) ;

  /*
  unsigned int notScheduled = _count.value();
	//RIght not scheduling all the packets on the same segment
	for(unsigned int i = 0; i < total ; i++)
	{
	  if(notScheduled < capacity)
		{
	    scheduleNewActivityInt(nextSeg, PackageCount(notScheduled), destination);        
		}
    else
		{
		  
	    scheduleNewActivityInt(nextSeg, PackageCount(capacity), destination);        
		}

	}

	*/

}

const string LocationReactor::getNewActivityName()
{
  stringstream strstream;

	strstream << location_->name() << ":" << totalActivities_ ;

  return strstream.str();
}


Conn::Path LocationReactor::getBestPath(Location::Ptr _src, Location::Ptr _dest, Conn::PathList _pathList)
{
  return _pathList.front();
}

}
