#include "LocationReactor.h"
#include "ShipmentActivityReactor.h"
#include <sstream>
#include <vector>


using namespace std;

namespace Shipping
{


void LocationReactor::updateToNow()
{
  vector<SegmentPtr> segments = location_->segments();
	vector<SegmentPtr>::iterator it = segments.begin();

	for( ; it != segments.end() ; it++)
	{
	  Time t = 	lastScheduled_[ (*it)->name()]; 
    if(t < manager_->now())
	  {

	  	lastScheduled_[ (*it)->name()] = manager_->now();  
	  }
   
	}

}


void LocationReactor::scheduleAckPackage(Location::Ptr _destination, uint32_t _shipmentId)
{
    
  updateToNow();
  scheduleNewActivity(PackageCount(1), _destination, Cost(0), Time(0), location_, _shipmentId);
}

void LocationReactor::onPackageCountInc(PackageCount _count, Cost _cummulativeCost, Time _cummulativeTime, Location::Ptr _source, uint32_t _shipmentId)
{
  if(location_->locType() == 0 && first_)
	{
	  scheduleInjectActivity();
		
		first_ = false;
	}
  
	
/*	
	if(lastScheduled_ < manager_->now())
	{
	  lastScheduled_ = manager_->now();
	}
*/
  updateToNow();

  PackageCount newPackageCount = _count;
  Location::Ptr destination = location_->destination(); 
  scheduleNewActivity(newPackageCount, destination, _cummulativeCost, _cummulativeTime, _source, _shipmentId);
	
}


void LocationReactor::onPackageCountDelivered(PackageCount _count, Cost _cummulativeCost, Time _cummulativeTime, Location::Ptr _source, uint32_t _shipmentId)
{
  if(location_->locType() == 0)
  {
	   
		//check whether this was sent by me

		vector<uint32_t> temp(shipmentId_);
		vector<uint32_t>::iterator it = temp.begin();
		shipmentId_.clear();
		bool got = false;
		for(; it != temp.end(); it++)
		{
		  if( *it == _shipmentId)
			{
			  got = true;
				std::cerr << "Got the receipt for the shipment ID " << _shipmentId << "at location " << location_->name() << " "  << std::endl;
				location_->ackReceivedInc(1);
				
			}
			else
			{
			  shipmentId_.push_back(*it);
			}
		}

		if(got) { return;}

	  // increment the totalCost
    location_->totalCostIs(location_->totalCost() +  _cummulativeCost);
    location_->totalTimeIs(location_->totalTime() +  _cummulativeTime);
		
		packageDelivered_ += _count;
		std::cerr << "ADDED " << _count.value() << "to the number of packets at " << location_->name() << " " << std::endl;

		std::cerr << "delivered " << _count.value() << "packets " << std::endl; 
		std::cerr << "Total packets delivered " << packageDelivered_.value() << "packets " << std::endl; 

    std:: cerr << "total cost of this delivery = " << location_->totalCost().value() << " " << std::endl;
		
    std:: cerr << "Average latency of delivery for location = " << (manager_->now().value())/(packageDelivered_.value())  << " " << std::endl;
  
  
	  // Do send the receipt back to the source of this activity
    
    scheduleAckPackage(_source, _shipmentId);
   		

	
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
  /*
	if(lastScheduled_ < manager_->now())
	{
	  lastScheduled_ = manager_->now();
	}
	*/
	updateToNow();

  if(injectActivity_->status() != Activity::free) return;

  scheduleInjectActivity();

	// FIXME increment the packet count here
  // Shipment transfer rate has to be taken into account
  
  //location_->packageCountInc( (location_->transferRate())*(location_->shipmentSize()) );
  PackageCount p = PackageCount( (location_->transferRate().value())*(location_->shipmentSize().value())) ;

  std::cerr << "Injected " << p.value() << " packets into the location " << location_->name() << " " << std::endl;
  uint32_t id = location_->nextShipmentId();
  location_->packageCountInc(p, Cost(0), Time(0), location_, id);
	shipmentIdIs(id);
}


void LocationReactor::scheduleNewActivityInt(Segment::Ptr _segment, PackageCount _count, Location::Ptr _dest, Cost _cost, Time _cummulativeTime, Location::Ptr _source, uint32_t shipmentId)
{

  const string name = getNewActivityName();
	Activity::Ptr act = manager_->activityNew(name);
  //ShipmentActivityReactor::Ptr sar = ShipmentActivityReactor::ShipmentActivityReactorNew(manager_, act, _segment);
  ShipmentActivityReactor*  sar = new ShipmentActivityReactor(manager_, act, _segment);
	sar->packageCountIs(_count);
	sar->destinationIs(_dest);
	sar->sourceIs(_source);
  sar->shipmentIdIs(shipmentId);	

	//Assuming that we are transfering package size <= segment capacity
	Time transferTime = _segment->transferTime(_count, fleet_, manager_->now());
  
	std::cerr << "Transfer time of the segment is " << transferTime.value() << " " << std::endl;

  //Time t = lastScheduled_ + transferTime;
  Time t = lastScheduled_[_segment->name()] + transferTime;
	
	if(t >= manager_->now())
	{
	  // Increase the refuse count for this segment to be this activity 
    // FIXME
	}
	act->nextTimeIs(t);
	lastScheduled_[_segment->name()] = t;

   Cost transferCost = _segment->transferCost(_count, fleet_, manager_->now());
   sar->cummulativeCostIs(_cost + transferCost);	
   //sar->cummulativeTimeIs(_cummulativeTime + transferTime + (act->nextTime() - manager_->now()) );
   sar->cummulativeTimeIs(_cummulativeTime + act->nextTime() - manager_->now() );
	act->lastNotifieeIs(sar);
	//sar->notifierIs(act);

	manager_->lastActivityIs(act);

	std::cerr << "Scheduling new activity called " << name << "at the location " << location_->name() << " on segment " << _segment->name() << " with next_time =  " << t.value() << " "  << std::endl;

	totalActivities_++;
} 


void LocationReactor::scheduleNewActivity(PackageCount _count, Location::Ptr destination, Cost _cost, Time _time, Location::Ptr _source, uint32_t shipmentId) throw (DestinationUnreachableException)
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
	Conn::Path p = getBestPath(location_, destination, pathList, _count);
  
  // What if there is no path from this location to the destination
	//Now take the first segment in the best path
  	
	Segment::Ptr nextSeg = p[0];
  
  
	scheduleNewActivityInt(nextSeg, _count, destination, _cost, _time, _source, shipmentId);        

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

/* We just consider the time as it looks  now and not considering the actual time due to scheduled changes in fleet attributes*/

Time LocationReactor::getPathTime(Conn::Path _path, PackageCount _count)
{
  Conn::Path::iterator it = _path.begin();
	Time total;
	for(; it != _path.end(); it++)
	{
	  total = total + (*it)->transferTime(_count, fleet_, manager_->now());   
	}


	return total;
}


Conn::Path LocationReactor::getLeastTimeDJPath(Conn::PathList _pathList, PackageCount _count)
{
  Conn::PathList pathList(_pathList);
  Time leastTime;
	Conn::Path retPath;
  
  while(!pathList.empty())
	{
	  Conn::Path path = pathList.front();
    Time t = getPathTime(path, _count);
    if(leastTime == Time(0))
		{
		  leastTime = t;
			retPath = path;
		}
		else if(t < leastTime)
		{
		  leastTime = t;
		  retPath = path;    
		}

		pathList.pop();


	}
  
	return retPath;
}




Conn::Path LocationReactor::getLeastTimeGDPath(Conn::PathList _pathList, PackageCount _count)
{
  Conn::Path retPath;
  
	Conn::PathList pathList(_pathList);
  Time leastTime;
  
  while(!pathList.empty())
	{
	  Conn::Path path = pathList.front();
    Time t = path[0]->transferTime(_count, fleet_, manager_->now());
		if(leastTime == Time(0))
		{
		  leastTime = t;
			retPath = path;
		}
		else if(t < leastTime)
		{
		  leastTime = t;
		  retPath = path;    
		}

		pathList.pop();


	}

	return retPath;
}

Conn::Path LocationReactor::getBestPath(Location::Ptr _src, Location::Ptr _dest, Conn::PathList _pathList, PackageCount _count)
{
  
	Conn::Path ret ;
	if(conn_->routeAlgorithm() == "1")
	{
    ret = getLeastTimeDJPath(_pathList, _count);
	}
	else
	{
	  ret = getLeastTimeGDPath(_pathList, _count);
	}
  return  ret;
}

}
