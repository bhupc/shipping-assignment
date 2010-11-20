#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "ActivityImpl.h"
    
class ProducerActivityReactor : public Activity::Notifiee {
 public:
 ProducerActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate) 
     : Notifiee(activity), rate_(rate), activity_(activity), manager_(manager) {}

    void onStatus();

 protected:
    double rate_;
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	
};

class ConsumerActivityReactor : public Activity::Notifiee {
 public:
 ConsumerActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate)
     : Notifiee(activity), rate_(rate), activity_(activity), manager_(manager) {}

    void onStatus();

 protected:
    double rate_;
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;

};
    
    

#endif
