#include "ActivityReactor.h"

static int num = 0;

void ProducerActivityReactor::onStatus() {
    Queue::Ptr q = NULL;
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
    switch (activity_->status()) {
	
    case Activity::executing:
	//I am executing now
	q = managerImpl->queue();
	std::cout << activity_->name() <<" enqueueing number " << num << endl;
	q->enQ(num);
	num++;
	break;
	
    case Activity::free:
	//when done, automatically enqueue myself for next execution
	activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
	activity_->statusIs(Activity::nextTimeScheduled);
	break;

    case Activity::nextTimeScheduled:
	//add myself to be scheduled
	manager_->lastActivityIs(activity_);
	break;
	
    default:
	break;
    }

}

void ConsumerActivityReactor::onStatus() {
    Queue::Ptr q = NULL;
    int n = 0;
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);

    switch (activity_->status()) {
    case Activity::executing:
	//I am executing now
	q = managerImpl->queue();
	n = q->deQ();
	cout << activity_->name() << " dequeing number " << n << endl;
	break;
	
    case Activity::free:
	//When done, automatically enqueue myself for next execution
	activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
	activity_->statusIs(Activity::nextTimeScheduled);
	break;

    case Activity::nextTimeScheduled:
	//add myself to be scheduled
	manager_->lastActivityIs(activity_);
	break;

    default:
	break;
    }

}
