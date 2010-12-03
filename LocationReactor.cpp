#include "LocationReactor.h"
#include "ShipmentActivityReactor.h"
#include <sstream>


using namespace std;

namespace Shipping
{

void LocationReactor::onPackageCountInc(PackageCount _count, Cost _cummulativeCost)
{
  if(location_->locType() == 0 && first_)
	{
	  scheduleInjectActivity();
		
		first_ = false;
	}
  
	if(lastScheduled_ < manager_->now())
	{
	  lastScheduled_ = manager_->now();
	}


  PackageCount newPackageCount = _count;
  Location::Ptr destination = location_->destination(); 
  scheduleNewActivity(newPackageCount, destination, _cummulativeCost);
}


void LocationReactor::onPackageCountDelivered(PackageCount _count, Cost _cummulativeCost)
{
  if(location_->locType() == 0)
  {
	  
    // increment the totalCost
    location_->totalCostIs(location_->totalCost() +  _cummulativeCost);
		packageDelivered_ += _count;
		std::cerr << "delivered " << _count.value() << "packets " << std::endl; 
		std::cerr << "Total packets delivered " << packageDelivered_.value() << "packets " << std::endl; 

    std:: cerr << "total cost of this delivery = " << location_->totalCost().value() << " " << std::endl;
		
    std:: cerr << "Average latency of delivery for location = " << (manager_->now().value())/(packageDelivered_.value())  << " " << std::endl;
  
  }
}

void LocationReactor::scheduleInjectActivity()
{
  std::cerr << "In LocationReactor::scheduleInjectActivity()" << std::endl;
  
  if(!injectActivity_)
	{
	  // Create a new inject activity
		// FIXME append the location name with this activity name
		string s = location_->name() + ": InjectActivity";
		injectActivity_ = manager_->activityNew(s);
		injectActivity_->lastNotifieeIs(this);
	}
  // Time is always in hours
	Time t = manager_->now() + Time(24.0);
  injectActivity_->nextTimeIs(t);
	manager_->lastActivityIs(injectActivity_);

	std::cerr << "Inject Activity scheduled to finish at time = " << (manager_->now() + Time(24)).value() << " "  << std::endl;
  
}

void LocationReactor::onStatus()
{
  std::cerr << "In LocationReactor::onStatus()" << std::endl;

	if(lastScheduled_ < manager_->now())
	{
	  lastScheduled_ = manager_->now();
	}
  if(injectActivity_->status() != Activity::free) return;

  scheduleInjectActivity();

	// FIXME increment the packet count here
  // Shipment transfer rate has to be taken into account
  
  //location_->packageCountInc( (location_->transferRate())*(location_->shipmentSize()) );
  PackageCount p = PackageCount( (location_->transferRate().value())*(location_->shipmentSize().value())) ;

  std::cerr << "Injected " << p.value() << " packets into the location " << location_->name() << " " << std::endl;

  location_->packageCountInc(p, Cost(0));
}


void LocationReactor::scheduleNewActivityInt(Segment::Ptr _segment, PackageCount _count, Location::Ptr _dest, Cost _cost)
{

  const string name = getNewActivityName();
	Activity::Ptr act = manager_->activityNew(name);
  //ShipmentActivityReactor::Ptr sar = ShipmentActivityReactor::ShipmentActivityReactorNew(manager_, act, _segment);
  ShipmentActivityReactor*  sar = new ShipmentActivityReactor(manager_, act, _segment);
	sar->packageCountIs(_count);
	sar->destinationIs(_dest);
	

	//Assuming that we are transfering package size <= segment capacity
	Time transferTime = _segment->transferTime(_count, fleet_);
  
	std::cerr << "Transfer time of the segment is " << transferTime.value() << " " << std::endl;

  Time t = lastScheduled_ + transferTime;
	if(t >= manager_->now())
	{
	  // Increase the refuse count for this segment to be this activity 
    // FIXME
	}
	act->nextTimeIs(t);
	lastScheduled_ = t;

        Cost transferCost = _segment->transferCost(_count, fleet_);
        sar->cummulativeCostIs(_cost + transferCost);	

	act->lastNotifieeIs(sar);
	//sar->notifierIs(act);

	manager_->lastActivityIs(act);

	std::cerr << "Scheduling new activity called " << name << "at the location " << location_->name() << " on segment " << _segment->name() << " with next_time =  " << t.value() << " "  << std::endl;

	totalActivities_++;
} 


void LocationReactor::scheduleNewActivity(PackageCount _count, Location::Ptr destination, Cost _cost) throw (DestinationUnreachableException)
{
  if(_count == 0)
	{
	  return;
	}
  

	Conn::PathList pathList = conn_->path(location_, destination);
	
  	if(pathList.empty())
	{
	  stringstream strstream;
		strstream << "Could not fine path from " << location_->name() << " to " << destination->name() << std::endl;
	  throw DestinationUnreachableException(strstream.str());
	}

	//Get the best path from the path list for the given source and diestina
	Conn::Path p = getBestPath(location_, destination, pathList);
  
  // What if there is no path from this location to the destination
	//Now take the first segment in the best path
  	
	Segment::Ptr nextSeg = p[0];
  
  
	scheduleNewActivityInt(nextSeg, _count, destination, _cost);        

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
