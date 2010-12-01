/*
 * Sample client code for CS249A Assignment 3.
 *
 * This file contains a rough skeleton of what your simulation 
 * client code looks like. In particular, you might find it useful 
 * for writing your verification.cpp file. This file does not 
 * compile.
 *
 * Everything in this file is a sketch - you don't need to follow 
 * it at all, including the placement of statements and naming of 
 * attributes and variables. However, please document your design 
 * decisions in README. For example, if you decide to use a command 
 * line parameter to switch between real and virtual-time managers, 
 * please describe how to do that in your README.
 *
 * Another example is semantics of attribute mutators: you may 
 * decide when a mutator takes effect. For instance, setting a 
 * customer's transfer rate between two settings of the virtual time 
 * manager's "now" attribute (say, 50 and 100) could imply stopping 
 * shipment injections at virtual time 50, or at virtual time 100. 
 * Make sure you document your decision and take this into account 
 * when performing analyses.
 *
 */

#include <iostream>
#include <vector>
#include "Instance.h"
#include "ActivityImpl.h"

using namespace std;

int main(int argc, char *argv[]) {
  try
  {
    Ptr<Instance::Manager> manager = shippingInstanceManager();

	/* Set up the network */
	vector< Ptr<Instance> > loc;
	vector< Ptr<Instance> > seg;

	// Locations
    loc.push_back( manager->instanceNew("customer1", "Customer") );
    loc.push_back( manager->instanceNew("customer2", "Customer") );
    loc.push_back( manager->instanceNew("port1", "Port") );
    loc.push_back( manager->instanceNew("tt1", "Truck terminal") );
    loc.push_back( manager->instanceNew("tt2", "Truck terminal") );
    loc.push_back( manager->instanceNew("customer3", "Customer") );

	// Segments
    seg.push_back( manager->instanceNew("ps1", "Plane segment") );
    seg.push_back( manager->instanceNew("ps2", "Plane segment") );
    seg.push_back( manager->instanceNew("bs1", "Boat segment") );
    seg.push_back( manager->instanceNew("bs2", "Boat segment") );
    seg.push_back( manager->instanceNew("ts1", "Truck segment") );
    seg.push_back( manager->instanceNew("ts2", "Truck segment") );
    seg.push_back( manager->instanceNew("ts3", "Truck segment") );
    seg.push_back( manager->instanceNew("ts4", "Truck segment") );
    seg.push_back( manager->instanceNew("ts5", "Truck segment") );
    seg.push_back( manager->instanceNew("ts6", "Truck segment") );
    seg.push_back( manager->instanceNew("ts7", "Truck segment") );
    seg.push_back( manager->instanceNew("ts8", "Truck segment") );

	// Connections...
	seg[0]->attributeIs("source", "customer1");
	seg[1]->attributeIs("source", "port1");
	seg[1]->attributeIs("return segment", "ps1");

	seg[2]->attributeIs("source", "customer2");
	seg[2]->attributeIs("source", "port1");
	seg[3]->attributeIs("return segment", "ps2");

	// And so on...

    Ptr<Instance> fleet = manager->instanceNew("Fleet", "Fleet");
    fleet->attributeIs("Truck speed", "1");
    fleet->attributeIs("Truck capacity", "1");

	// Set some segment (shipment) capacities
	seg[4]->attributeIs("Capacity", "1");
	seg[6]->attributeIs("Capacity", "1");

	/* For groups, you could set routing algorithm here
	 * Note that we are not advocating any particular design
	 * here, but only giving an example of how you might 
	 * set the routing algorithm. You may also use attribute
	 * names other than "routing algorithm" 
	 */
	Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
	conn->attributeIs("routing algorithm", "Dijkstra"); 
	// conn->attributeIs("routing algorithm", "Some very cool algorithm worthy of a Turing award");

	/* Switching between real-time and virtual-time managers
	 * can be as simple as simple commenting and uncommenting certain 
	 * statements in the program. You are not required to support fancy 
	 * switching, though it will ease our grading effort (and time needed) 
	 * quite a bit if the switching did not require searching some lines 
	 * in lots of code and recompiling =)
	 *
	 * When you use the real-time manager, there's no need for the client to 
	 * interact directly with the virtual-time manager, since the latter is 
	 * driven as an activity by the real-time manager. 
	 *
	 * Again, the attribute names here are not set in stone. You are free to 
	 * use any names that make sense and follow the attribute-only interface 
	 * design conventions.
	 *
	 * Another thing to notice is that using real-time manager doesn't mean 
	 * you need to simulate an event flow that synchronizes with real-time. 
	 * For example, in the code snippet below, we're setting the elapsed 
	 * number of real seconds to be some value. The manager then sleeps for 
	 * the time difference between the two settings (18 seconds in this case). 
	 * Upon awakening, the 18 seconds is multipled by the scaling factor to get 
	 * the number of virtual hours passed, and every (virtual) activity that 
	 * have been scheduled between those 18 hours are executed in order.
	 *
	 * Thus, the simulation is really a batch processing engine, where the 
	 * batch size is determined by the client's settings of the real/virtual 
	 * times at difference places.
	 */
    Activity::Manager::Ptr activityManager = activityManagerInstance();
    activityManager->nowIs(6.0);
//    RealTimeManager::Ptr realTimeManager = realTimeManagerInstance();
//  realTimeManager->realTimePassedIs(6.0);

	// Stop injection activity from the first two customers
    loc[0]->attributeIs("Transfer Rate", "0");
    loc[1]->attributeIs("Transfer Rate", "0");

    activityManager->nowIs(24.0);
//  realTimeManager->realTimePassedIs(18.0);

	/* Print simulation statistics for analysis 
	 * You'll need some numbers to put into your README and for analysis. 
	 * The format is completely up to you, but make sure it is easily 
	 * readable, otherwise we might misunderstand your analysis
	 */
	//printSimStats();
  }
  catch(Exception e)
  {
	cout << e.what() << endl;
  }
  catch(...)
  {
  }

  return 0;
}

