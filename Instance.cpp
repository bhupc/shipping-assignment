#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include "Instance.h"
#include "Engine.h"

namespace Shipping {

using namespace std;
using namespace Fwk;
//
// Rep layer classes
//

class ManagerImpl : public Instance::Manager {

public:
    ManagerImpl();

    // Manager method
    Ptr<Instance> instanceNew(const string& name, const string& type);

    // Manager method
    Ptr<Instance> instance(const string& name);

    // Manager method
    void instanceDel(const string& name);
    
		Ptr<Engine> engine() const { return engine_;}
private:
    map<string,Ptr<Instance> > instance_;
	Ptr<Instance> stats_;
	Ptr<Instance> conn_;
	Ptr<Instance> fleet_;
  Ptr<Engine> engine_;

};

class LocationRep : public Instance {
public:

    LocationRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);
	// Has no attributes to write to !

	Location::Ptr LocationEng(){return LocationEng_ ;}

protected:
    Ptr<ManagerImpl> manager_;
	Location::Ptr LocationEng_;
	// Should I store segment Pointers ? Needed for attribute reading !
	// When segment lists this as source it should update this vector 
	// We can rather use only vector as mapping pointers can be had by instance ? 
 //   Location loc = LocationInstance.getLocation(instance_name);
//	loc.segment(offset);
//	vector<string> segments_;

    int segmentNumber(const string& name);
};
                                                                                                  
class TruckTerminalRep : public LocationRep {
public:

    TruckTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
			// Should we keep the same names
			// Do TypeIS
			LocationEng_ = manager_->engine()->TerminalNew(name); 
			LocationEng_->typeIs(TransportType::truck());
	}

};

/*
CustomerLocation::Ptr CustomerLocationNew(const String& name);
	Port::Ptr PortNew(const String&);
	Terminal::Ptr TerminalNew(const String&);
*/

class PlaneTerminalRep : public LocationRep {
public:

    PlaneTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		// Do Type IS
        LocationEng_ = manager_->engine()->TerminalNew(name);
		LocationEng_->typeIs(TransportType::plane());
    }
};

class BoatTerminalRep : public LocationRep {
public:

    BoatTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        LocationEng_ = manager_->engine()->TerminalNew(name);
		LocationEng_->typeIs(TransportType::boat());
    }
};

class CustomerRep : public LocationRep {
public:

    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
		LocationEng_ = manager_->engine()->CustomerLocationNew(name);
    }
};

class PortRep : public LocationRep {
public:

    PortRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        LocationEng_ = manager_->engine()->PortNew(name);
    }

};



class SegmentRep : public Instance {
public:

    SegmentRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

	Segment::Ptr SegmentEng(){return SegmentEng_;}

    // Instance method
    void attributeIs(const string& name, const string& v);
	// We are in the instance
	// SEGMENT ATTRIBUTES ARE source, length, return segment, difficuly, expidite support,(YES/NO)

protected:
    Ptr<ManagerImpl> manager_;
	Segment::Ptr SegmentEng_;

};

class TruckSegmentRep : public SegmentRep {
public:

    TruckSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
        // Nothing else to do.
		SegmentEng_ = manager_->engine()->SegmentNew(name);
		SegmentEng_->modeIs(TransportType::truck());
    }
};

class BoatSegmentRep : public SegmentRep {
public:

    BoatSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
		SegmentEng_ = manager_->engine()->SegmentNew(name);
		SegmentEng_->modeIs(TransportType::boat());
    }
};

class PlaneSegmentRep : public SegmentRep {
public:

    PlaneSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
        // Nothing else to do.
		SegmentEng_ = manager_->engine()->SegmentNew(name);
		SegmentEng_->modeIs(TransportType::boat());
    }
};




//---------------------------------
// STATSrep CLASS
class StatsRep : public Instance {
public:

    StatsRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);
	// We are in the instance
	// READ ONLY ATTRIBUTES
	

private:
    Ptr<ManagerImpl> manager_;

};

// ------------------------------------------
// FLEETrep CLass
class FleetRep : public Instance {
public:

    FleetRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);
	// We are in the instance
	

private:
    Ptr<ManagerImpl> manager_;

};

// -------------------------------------------------------
// CONNrep
class ConnRep : public Instance {
public:

    ConnRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);
	// We are in the instance
	// Read only attributes

private:
    Ptr<ManagerImpl> manager_;

};




//-------------------------------------------------------

ManagerImpl::ManagerImpl() {
	stats_ = NULL;
	conn_ = NULL;
	fleet_ = NULL;
  engine_ = NULL;
}

// ---------------------------------------------------------

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
	//  This will have provision for every new instance possible
    if (type == "Truck terminal") {
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Plane terminal") {
        Ptr<PlaneTerminalRep> t = new PlaneTerminalRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Boat terminal") {
        Ptr<BoatTerminalRep> t = new BoatTerminalRep(name, this);
        instance_[name] = t;
        return t;
    }


	if (type == "Customer") {
        Ptr<CustomerRep> t = new CustomerRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Port") {
        Ptr<PortRep> t = new PortRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Truck segment") {
        Ptr<TruckSegmentRep> t = new TruckSegmentRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Boat segment") {
        Ptr<BoatSegmentRep> t = new BoatSegmentRep(name, this);
        instance_[name] = t;
        return t;
    }

	if (type == "Plane segment") {
        Ptr<PlaneSegmentRep> t = new PlaneSegmentRep(name, this);
        instance_[name] = t;
        return t;
    }

	// One thing for STATS, CON, FLEET is there can be only one instance, if there is an attempt to intialise other for same manager
	// return the prev.
	if(type=="Conn"){
		if(conn_)
			return conn_;
		else
		{
			Ptr<ConnRep> t = new ConnRep(name, this);
			instance_[name] = t;
			conn_ = t;
			return t;
		}	
	}

	if(type=="Stats"){
		if(stats_)
			return stats_;
		else
		{
			Ptr<StatsRep> t = new StatsRep(name, this);
			instance_[name] = t;
			stats_ = t;
			return t;
		}	
	}

	if(type=="Fleet"){
		if(fleet_)
			return fleet_;
		else
		{
			Ptr<FleetRep> t = new FleetRep(name, this);
			instance_[name] = t;
			fleet_ = t;
			return t;
    }
	}

	// Do also for CONN, STATS, FLEET

    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

    return t == instance_.end() ? NULL : (*t).second;
}

void ManagerImpl::instanceDel(const string& name) {
}



string LocationRep::attribute(const string& name) {
    int i = segmentNumber(name);
    if (i != 0) {
        cout << "Tried to read interface " << i;
		// Now give the ith Segment to user
		// if(i < segments_.size() && i>0)
		//	return segments_[i];
		return (LocationEng_->segment(i-1))->name();
    }
    return "";
}


void LocationRep::attributeIs(const string& name, const string& v) {
    //nothing to do
}

string SegmentRep::attribute(const string& name) {
	// Read the attribute name and act accordingly
	if (name == "expedite support"){
		if(SegmentEng_->expediteSupport()){
			return "yes";
		}
		else
			return "no";
	}

	if (name == "return segment"){
		return (SegmentEng_->returnSegment())->name();
	}

	// Check Nominal Ordinal Types

	if (name == "source"){
		return (SegmentEng_->source())->name();
	}

	if (name == "length"){
		// ** Assuming string() exists for each Type
		return (SegmentEng_->length()).string();
	}

	if (name == "difficulty"){
		return (SegmentEng_->difficulty()).string();
	}

	return "";

}


void SegmentRep::attributeIs(const string& name, const string& v) {
///    "source"
///    "length"
///    "return segment"
///    "difficulty"
///    "expedite support"
	if (name == "expedite support"){
		if(v=="yes"){
			SegmentEng_->expediteSupportIs(true);
			return;
		}
		if(v=="no"){
			SegmentEng_->expediteSupportIs(false);
			return;
		}
	}

	if (name == "return segment"){
		// Issue is Private
		// Name-> RepLayerObject -> locationEng
     Ptr<SegmentRep>res = Ptr<SegmentRep>(dynamic_cast<SegmentRep*>(manager_->instance(v).ptr()));
		 if(res){
				SegmentEng_->returnSegmentIs(res->SegmentEng());				
		 }

		return;
	}

	

	if (name == "source"){
		Ptr<LocationRep> src = Ptr<LocationRep> (dynamic_cast<LocationRep*>(manager_->instance(v).ptr()));
		if(src){
			SegmentEng_->sourceIs(src->LocationEng());
			}
		return;
	}

	// Check Nominal Ordinal Types
	double value = atof(v.c_str());

	if (name == "length"){
		SegmentEng_->lengthIs(Mile(value));
		return;
	}

	if (name == "difficulty"){
		SegmentEng_->difficultyIs(Difficulty(value));
		return;
	}

}

static const string segmentStr = "segment";
static const int segmentStrlen = segmentStr.length();

int LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return atoi(t);
    }
    return 0;
}



/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */

void StatsRep::attributeIs(const string& name,const string& v){
}

void ConnRep::attributeIs(const string& name,const string& v){
}

void FleetRep::attributeIs(const string& name, const string& v){
}

string StatsRep::attribute(const string& name){
	return "";
}

string ConnRep::attribute(const string& name){
	return "";
}

string FleetRep::attribute(const string& name){
	return "";
}

}

Ptr<Instance::Manager> shippingInstanceManager() {
    return new Shipping::ManagerImpl();
}


