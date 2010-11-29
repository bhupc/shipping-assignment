#include <stdlib.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "Instance.h"
#include "Stats.h"
#include "Engine.h"
#include "Conn.h"
#include <sstream>
#include <cstring>
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
		
			Ptr<Instance> fleet(){return fleet_;}

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
			int segmentNumber(const string& name);
	};

	class TruckTerminalRep : public LocationRep {
		public:

			TruckTerminalRep(const string& name, ManagerImpl *manager) :
				LocationRep(name, manager)
		{
			// Should we keep the same names
			// Do TypeIS
			LocationEng_ = manager_->engine()->TruckTerminalNew(name); 
			//		LocationEng_->typeIs(TransportType::truck());
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
			LocationEng_ = manager_->engine()->PlaneTerminalNew(name);
			//	LocationEng_->typeIs(TransportType::plane());
		}
	};

	class BoatTerminalRep : public LocationRep {
		public:

			BoatTerminalRep(const string& name, ManagerImpl *manager) :
				LocationRep(name, manager)
		{
			LocationEng_ = manager_->engine()->BoatTerminalNew(name);
			//LocationEng_->typeIs(TransportType::boat());
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
			SegmentEng_->modeIs(TransportType::plane());
		}
	};




	//---------------------------------
	// STATSrep CLASS
	class StatsRep : public Instance {
		public:

			StatsRep(const string& name, ManagerImpl* manager) :
				Instance(name), manager_(manager)
		{
			StatsEng_ = manager_->engine()->StatsNew(name);

		}

			// Instance method
			string attribute(const string& name);

			// Instance method
			void attributeIs(const string& name, const string& v);
			// We are in the instance
			// READ ONLY ATTRIBUTES


		private:
			Ptr<ManagerImpl> manager_;

			Fwk::Ptr<Stats> StatsEng_;
	};

	// ------------------------------------------
	// FLEETrep CLass
	class FleetRep : public Instance {
		public:

			FleetRep(const string& name, ManagerImpl* manager) :
				Instance(name), manager_(manager)
		{

			FleetEng_ = manager_->engine()->FleetNew(name);
		}

			// Instance method
			string attribute(const string& name);

			Fleet::Ptr fleetEng(){return FleetEng_;}
			// Instance method
			void attributeIs(const string& name, const string& v);
			// We are in the instance


		protected:
			Ptr<ManagerImpl> manager_;
			Fleet::Ptr FleetEng_;
	};

	// -------------------------------------------------------
	// CONNrep
	class ConnRep : public Instance {
		public:

			ConnRep(const string& name, ManagerImpl* manager) :
				Instance(name), manager_(manager)
		{
			ConnEng_ = manager_->engine()->ConnNew(name);
		}

			// Instance method
			string attribute(const string& name);

			// Instance method
			void attributeIs(const string& name, const string& v);
			// We are in the instance
			
		private:
			Ptr<ManagerImpl> manager_;
			Conn::Ptr ConnEng_;
	};




	//-------------------------------------------------------

	ManagerImpl::ManagerImpl() {
		stats_ = NULL;
		conn_ = NULL;
		fleet_ = NULL;

		engine_ = Engine::EngineIs(); 
	}

	// ---------------------------------------------------------

	Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {

		//If this name already exist then return NULL
		if(instance_.count(name)>0){
			return NULL;	
		}
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


		return NULL;
	}

	Ptr<Instance> ManagerImpl::instance(const string& name) {
		map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

		return t == instance_.end() ? NULL : (*t).second;
	}

	void ManagerImpl::instanceDel(const string& name) {
                if(instance(name)){
                        Ptr<Instance> ptr =  instance(name);
                        if(ptr == conn_ || ptr == fleet_ || ptr == stats_){
                                cerr << "Not deleting conn, Fleet and Stats objects" << endl;
                        }
                        else{
                                // It as to be either location or segment
                                if(dynamic_cast<SegmentRep*>(ptr.ptr())){
                                        cerr << "Deleting Segment" << endl;
					(Ptr<SegmentRep>(dynamic_cast<SegmentRep*>(ptr.ptr()))->SegmentEng())->sourceIs(NULL);
                                        (Ptr<SegmentRep>(dynamic_cast<SegmentRep*>(ptr.ptr()))->SegmentEng())->deleteRef();
                                         ptr->deleteRef();
                                }
                                else if(dynamic_cast<LocationRep*>(ptr.ptr())){
                                        cerr << "Deleting Location" <<endl;
                                        (Ptr<LocationRep>(dynamic_cast<LocationRep*>(ptr.ptr()))->LocationEng())->deleteRef();
                                        ptr->deleteRef();
                                }
                                instance_.erase(name);
                        }
                }
                else{
                        cerr << "No such instance to delete"<< endl;
                }
        }


	string LocationRep::attribute(const string& name) {
		if(dynamic_cast<CustomerRep*>(this)){

		if(name=="Tranfer Rate"){}
		else if(name == "Shipment Size"){}
		else if(name == "Destination"){}
		// Read Only attributes
		else if(name == "Shipments Received"){}
		else if(name == "Average Latency"){}
		else if(name == "Total Cost"){}
		}

		int i = segmentNumber(name);
		if (i != 0) {
			if(LocationEng_->segment(i-1)){
			return (LocationEng_->segment(i-1))->name();
			}
		}

		cerr << "Tried to Read Non-Existent Attribute";
		return "";
	}


	void LocationRep::attributeIs(const string& name, const string& v) {
		if(dynamic_cast<CustomerRep*>(this)){
			if(name == "Transfer Rate"){	
			}
			else if(name == "Shipment Size"){

			}
			else if(name == "Destination"){

			}
		}
		else
			cerr << "Not a customer Location" << endl;
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
			if(SegmentEng_->returnSegment())
			return (SegmentEng_->returnSegment())->name();
		}

		// Check Nominal Ordinal Types

		if (name == "source"){
			if(SegmentEng_->source())
			return (SegmentEng_->source())->name();
		}

		if (name == "length"){
			// ** Assuming string() exists for each Type
			return (SegmentEng_->length()).string();
		}

		if (name == "difficulty"){
			return (SegmentEng_->difficulty()).string();
		}

		// Read Only
		if(name == "Shipments Received"){}
		
		// Read Only
		if(name == "Shipments Refused"){}

		
		if(name == "Capacity"){
			return (SegmentEng_->capacity()).string();
		}

		cerr << "Tried to Read non-existent attribute";
		return "";

	}


	void SegmentRep::attributeIs(const string& name, const string& v) {
		///    "source"
		///    "length"
		///    "return segment"
		///    "difficulty"
		///    "expedite support"
		/// 	"capacity"

		if(name == "Capacity"){
			int value = atoi(v.c_str());
			SegmentEng_->capacityIs(Capacity(value));
			return;
		}
		if (name == "expedite support"){
			if(v=="yes"){
				SegmentEng_->expediteSupportIs(true);
				return;
			}
			if(v=="no"){
				SegmentEng_->expediteSupportIs(false);
				return;
			}
			cerr << "Invalid attribute value for expedite support"<<endl;
		}

		if (name == "return segment"){
			if(v == ""){
				SegmentEng_->returnSegmentIs(NULL);
				return;
			}
			Ptr<SegmentRep>res = Ptr<SegmentRep>(dynamic_cast<SegmentRep*>(manager_->instance(v).ptr()));
			if(res){
				SegmentEng_->returnSegmentIs(res->SegmentEng());				
			}
			else{
				cerr << "No such Segment Found, Ignored" <<endl;
			}

			return;
		}



		if (name == "source"){
			if(v == ""){
				SegmentEng_->sourceIs(NULL);
				return;
			}
			Ptr<LocationRep> src = Ptr<LocationRep> (dynamic_cast<LocationRep*>(manager_->instance(v).ptr()));
			if(src){
				try{
					SegmentEng_->sourceIs(src->LocationEng());
				}
				catch(...){
					cerr << "Incompatible Location Segment Pair, Command Discarded" << endl;
				}
			}
			else{
				cerr << "No such Location exists, Ignored" << endl;
			}
			return;
		}

		// Check Nominal Ordinal Types
		double value = atof(v.c_str());

		if (name == "length"){
			try{
				SegmentEng_->lengthIs(Mile(value));
			}
			catch(...){
				cerr << "Tried to set illegal value, ignored" << endl;
			}
			return;
		}

		if (name == "difficulty"){
			try{
				SegmentEng_->difficultyIs(Difficulty(value));
			}
			catch(...){
				cerr << "Tried to set illegal value, ignored" << endl;
			}
			return;
		}

		cerr << "Tried to set Non Existent Attribute, Ignored" << endl;

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
		//NOTHING TO BE DONE
	}

	void FleetRep::attributeIs(const string& name, const string& v){
		double value = atof(v.c_str());
	        int value_int = atoi(v.c_str());

		if(name=="Boat, speed"){
			FleetEng_->speedIs(0,MPH(value));
		}
		if(name=="Plane, speed"){
			FleetEng_->speedIs(1,MPH(value));
		}
		if(name=="Truck, speed"){
			FleetEng_->speedIs(2,MPH(value));
		}

		if(name=="Boat, capacity"){
			FleetEng_->capacityIs(0,Capacity(value_int));
		}
		if(name=="Plane, capacity"){
			FleetEng_->capacityIs(1,Capacity(value_int));
		}
		if(name=="Truck, capacity"){
			FleetEng_->capacityIs(2,Capacity(value_int));
		}

		if(name=="Boat, cost"){
			FleetEng_->costIs(0,Cost(value));
		}
		if(name=="Plane, cost"){
			FleetEng_->costIs(1,Cost(value));
		}
		if(name=="Truck, cost"){
			FleetEng_->costIs(2,Cost(value));
		}
	}

	string StatsRep::attribute(const string& type){
		std::stringstream out;
    //out.precision(2);
		if (type == "Truck terminal") {
			out << StatsEng_->truckTerminalCount();
			return out.str();
		}

		if (type == "Plane terminal") {
			out << StatsEng_->planeTerminalCount();
			return out.str();

		}

		if (type == "Boat terminal") {
			out << StatsEng_->boatTerminalCount();
			return out.str();
		}


		if (type == "Customer") {
			out << StatsEng_->customerLocationCount();
			return out.str();

		}

		if (type == "Port") {
			out << StatsEng_->portCount();
			return out.str();

		}

		if (type == "Truck segment") {
			out << StatsEng_->truckSegmentCount();
			return out.str();
		}
		if (type == "Boat segment") {
			out << StatsEng_->boatSegmentCount();
			return out.str();

		}

		if (type == "Plane segment") {
			out << StatsEng_->planeSegmentCount();
			return out.str();
		}

		if(type=="expedite percentage"){

			cerr << "** Segment Count is - "<<StatsEng_->segmentCount() << endl;
			double temp;
			char buff[20];
			memset(buff,0,20);
			if(StatsEng_->segmentCount() >0){
				//out << ( (double)StatsEng_->expeditedSegmentCount()/(double)StatsEng_->segmentCount()  *100.0);
				
				temp = 100.0* ((double)StatsEng_->expeditedSegmentCount())/((double)StatsEng_->segmentCount()); 
			}
			else{
        temp = 0.00;
			}
			sprintf(buff, "%.2f", temp);

			return String(buff);
		}

		cerr << "Invalid Stats Query" << endl;
		return "";
	}


	string FleetRep::attribute(const string& name){
		if(name=="Boat, speed"){
			return FleetEng_->speed(0).string();
		}
		if(name=="Plane, speed"){
			return FleetEng_->speed(1).string();
		}
		if(name=="Truck, speed"){
			return FleetEng_->speed(2).string();
		}

		if(name=="Boat, capacity"){
			return FleetEng_->capacity(0).string();
		}
		if(name=="Plane, capacity"){
			return FleetEng_->capacity(1).string();
		}
		if(name=="Truck, capacity"){
			return FleetEng_->capacity(2).string();
		}

		if(name=="Boat, cost"){
			return	FleetEng_->cost(0).string();
		}
		if(name=="Plane, cost"){
			return FleetEng_->cost(1).string();
		}
		if(name=="Truck, cost"){
			return FleetEng_->cost(2).string();
		}
		cerr << "Try to read non-existent attribute, Ignored "<< endl;
		return "";
	}
	
	void ConnRep::attributeIs(const string& name, const string& value){
		// We have the routing algo
		if(name.compare("routing")== 0){
			
			if(value.compare("1")==0){
				ConnEng_->routingAlgoIs(value);
			}
			else if(value.compare("2")==0){
				ConnEng_->routingAlgoIs(value);
			}
			else{
				cerr << "Only available algorithms are 1. Dijkstra 2. BFS. Select appropriate number for the same" << endl;
			}
		}
	}

	string ConnRep::attribute(const string& name){
		stringstream input;
		input.str(name);
		bool error_flag = false;

		string token;

		input >> token;
		if(token == "routing"){
			return ConnEng_->routingAlgo();
		}
		if(token == "explore"){
			string src;
			if(!(input >> src && input >> token)){
				error_flag = true;
				cerr << "Wrong Syntax for explore query, Discarded." << endl;
			}
				
			// Check here if Destination exists else exit	
			Ptr<LocationRep> src_rep = Ptr<LocationRep> (dynamic_cast<LocationRep*>(manager_->instance(src).ptr()));
			if(!src_rep){
				cerr << "No such Start Location exists, Ignored" << endl;
				return "";
			}


			if(token!=":"){
				cerr << "No : Separator in Connect query. ";
				error_flag = true;
				return "";
			}

			string attr[] = {"distance","cost","time","expedited"};
			set<string> attr_set(attr,attr+4);
			map<string,double> params;
			int num_params = 0;

			while(input >> token && num_params <= 4){
				if(attr_set.count(token)>0){
					if(token!="expedited"){
						double value;
						if((input >> value)){
							params[token] = value;
						}
						else{
							cerr << "Could not find a value for attribute: " << token << " Command Ignored"<<endl;
							error_flag = true;
							return "";
						}
					}
					else{
						params["expedited"]=1.0;
					}
				}
				else{
					cerr << "Unknown attribute restriction specified in explore, Discarded" << endl;
					error_flag = true;
					return "";
				}
				num_params++;
			}

			char c;
			if(input >> c){
				cerr << "More than 4 attrbutes or extra characters in explore command, Ignored. " << endl;
				return "";
			}


			Mile dist_limit;
			Time time_limit;
			bool is_expedited;
			Cost cost_limit;

			if(params.count("expedited")>0){
				is_expedited= true;
			}
			else{
				is_expedited = false;
			}
			if(params.count("distance")>0){
				dist_limit = Mile(params["distance"]);
			}
			else{
				dist_limit = Mile::nil();
			}
			if(params.count("cost")>0){
				time_limit = Time(params["cost"]);
			}
			else{
				time_limit =Time::nil();
			}
			if(params.count("time")>0){
				cost_limit = Cost(params["time"]);
			}
			else{
				cost_limit = Cost::nil();
			}

	// Ptr<SegmentRep>(dynamic_cast<SegmentRep*>(manager_->instance(v).ptr())
	if(!Ptr<FleetRep>(dynamic_cast<FleetRep*>(manager_->fleet().ptr()))->fleetEng()){
		cerr << "Initialize Fleet before Explore Query, Discarding" << endl;
		return "";
	}
	Conn::StatPathList paths = ConnEng_->path(Ptr<FleetRep>(dynamic_cast<FleetRep*>(manager_->fleet().ptr()))->fleetEng(),src_rep->LocationEng(),cost_limit,dist_limit,is_expedited,time_limit);
return Conn::printStatPathList(paths);
		}
		else if(token == "connect"){
			string src, dest;

			if(!(input >> src && input >> token && input >> dest)){
				cerr << "Not enough arguements. ";
				error_flag = true;
				return "";
			}
			if(token!=":"){
				cerr << "No <:> Separator in Connect query. ";
				error_flag = true;
				return "";
			}

			char c;
			if(input >> c){
				cerr << "Extra characters in Connect query. " << endl;
				error_flag = true;
				return "";
			}

			Ptr<LocationRep> src_rep = Ptr<LocationRep> (dynamic_cast<LocationRep*>(manager_->instance(src).ptr()));
			if(!src_rep){
				cerr << "No such Start Location exists, Ignored" << endl;
				return "";
			}
	

			Ptr<LocationRep> dest_rep = Ptr<LocationRep> (dynamic_cast<LocationRep*>(manager_->instance(dest).ptr()));
			if(!dest_rep){
				cerr << "No such Destination Location exists, Ignored" << endl;
				return "";
			}

			if(!error_flag){
				
				Conn::PathList paths = ConnEng_->path(src_rep->LocationEng(),dest_rep->LocationEng());
				// Call the Engine Layer functionality with two location engine objects src_eng and dest_eng

				return Conn::printPathList(paths, Ptr<FleetRep>(dynamic_cast<FleetRep*>(manager_->fleet().ptr()))->fleetEng());
			}
		}
		else{
			cerr << "Only conn/explore queries allowed. " << endl;
			error_flag = true;
			return "";
		}

		if(error_flag){
			cerr << "Not a valid query for Conn, Please refer to errors/specifications." << endl;	
		}
		return "";

	}
} // Namespace ends

Ptr<Instance::Manager> shippingInstanceManager() {
	return new Shipping::ManagerImpl();
}
