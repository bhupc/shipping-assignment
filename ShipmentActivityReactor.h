#ifndef __SHIPMENT_ACTIVITY_REACTOR_H__
#define __SHIPMENT_ACTIVITY_REACTOR_H__


#include "ActivityImpl.h"
#include "Segment.h"
#include "Location.h"
#include "Conn.h"


using namespace std;
using namespace Shipping;


namespace Shipping
{

  class ShipmentActivityReactor : public Activity::Notifiee
  {
    public:
		typedef Fwk::Ptr<ShipmentActivityReactor> Ptr;

    static ShipmentActivityReactor::Ptr ShipmentActivityReactorNew(Activity::Manager::Ptr _manager, Activity::Ptr _activity, Fwk::Ptr<Segment> _segment)
		{
		  return Fwk::Ptr<ShipmentActivityReactor>(new ShipmentActivityReactor(_manager, _activity, _segment));

		}
    
		ShipmentActivityReactor(Fwk::Ptr<Activity::Manager> _manager, Activity::Ptr _activity, Fwk::Ptr<Segment> _segment)
	  :Activity::Notifiee(_activity.ptr()), segment_(_segment), activity_(_activity), manager_(_manager) 
	  {
                  
                  cummulativeCost_ = Cost::nil();
									cummulativeTime_ = Time::nil();
		  std::cerr << "Created a new Shipment Activity Reactor " << std::endl;
		}
    
	 
		Fwk::Ptr<Segment> segment() const { return segment_;}
		Fwk::Ptr<Activity> activity() const { return activity_;}
		Fwk::Ptr<Activity::Manager> activityManager() const {return manager_;}
		PackageCount packageCount() const {return packageCount_;}
    void packageCountIs(PackageCount _packageCount) { packageCount_=_packageCount;}
		Location::Ptr destination() const { return destination_;}
		void destinationIs(Location::Ptr _destination) {  destination_=_destination;}
		Location::Ptr source() const { return source_;}
    void sourceIs(Location::Ptr _source) { source_ = _source;}

    Cost cummulativeCost() { return cummulativeCost_;}
    void cummulativeCostIs( Cost _cummulativeCost) { cummulativeCost_ = _cummulativeCost;}
    void cummulativeTimeIs( Time _cummulativeTime) { cummulativeTime_ = _cummulativeTime;}
    void shipmentIdIs(uint32_t _id) { shipmentId_ = _id;}
		uint32_t shipmentId() { return shipmentId_;}
		void onStatus();

	  protected:
	  Fwk::Ptr<Segment> segment_;
 	  Activity::Ptr activity_;
	  Fwk::Ptr<Activity::Manager> manager_;

		PackageCount packageCount_;
		Fwk::Ptr<Location> destination_;
		Fwk::Ptr<Location> source_;
    Cost cummulativeCost_;
    Time cummulativeTime_;	 
    uint32_t shipmentId_;
 };

}



#endif
