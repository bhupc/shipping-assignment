#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (manager == NULL) {
        cerr << "Unexpected NULL manager." << endl;
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (stats == NULL) {
        cerr << "Unexpected NULL stats." << endl;
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return 1;
    }

    fleet->attributeIs("Boat, speed", "60");
    fleet->attributeIs("Truck, capacity", "50");
    fleet->attributeIs("Plane, cost", "20");
    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;

    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  


    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  
    Ptr<Instance> port2 = manager->instanceNew("port2", "Port");  
    
   
    if (customer1 == NULL || customer2 == NULL || port1 == NULL) {
        cerr << "Unexpected NULL customer or port." << endl;
	return 1;
    }

    // -- Segments
    // boat
    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");  
    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");  

    Ptr<Instance> boatSeg1r = manager->instanceNew("boatSeg1r", "Boat segment");  
    Ptr<Instance> boatSeg2r = manager->instanceNew("boatSeg2r", "Boat segment");  



    // truck
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");  
    Ptr<Instance> truckSeg1r = manager->instanceNew("truckSeg1r", "Truck segment");  
    Ptr<Instance> truckSeg2r = manager->instanceNew("truckSeg2r", "Truck segment");  


    if (boatSeg1 == NULL || boatSeg2 == NULL || truckSeg1 == NULL || truckSeg2 == NULL) {
        cerr << "Unexpected NULL segment." << endl;
        return 1;
    }

		truckSeg1->attributeIs("source", "customer1");
		truckSeg2->attributeIs("source", "port2");
		
		truckSeg1r->attributeIs("source", "port1");
		truckSeg2r->attributeIs("source", "customer2");
		
		boatSeg1->attributeIs("source", "port1");
		boatSeg2->attributeIs("source" , "customer1");
    
		boatSeg1r->attributeIs("source", "customer2");
		boatSeg2r->attributeIs("source" , "port2");
    

		
   // return segs

	 boatSeg1->attributeIs("return segment", "boatSeg1r");
	 boatSeg2->attributeIs("return segment", "boatSeg2r");
   truckSeg1->attributeIs("return segment", "truckSeg1r");
	 truckSeg2->attributeIs("return segment", "truckSeg2r");


   cout << "boatseg2r reverse segment is " << boatSeg2r->attribute("return segment") << "\n";
    /*
		boatSeg2->attributeIs("source", "port1");
    boatSeg1->attributeIs("return segment", "boatSeg2");
    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl;

    // -- Segment lengths
    boatSeg1->attributeIs("length", "400");
    boatSeg2->attributeIs("length", "400");
    truckSeg1->attributeIs("length", "-1");
    truckSeg2->attributeIs("length", "900");

    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "-2");
    boatSeg2->attributeIs("difficulty", "1");
    truckSeg1->attributeIs("difficulty", "1");
    truckSeg2->attributeIs("difficulty", "1");
    
    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes");
    boatSeg2->attributeIs("expedite support", "yes");
    truckSeg1->attributeIs("expedite support", "yes");
	 truckSeg2->attributeIs("expedite support", "no");
*/
    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

    if (conn == NULL) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }

    cout << "**** explore customer1 : distance 1500 ****" << endl;
    cout << conn->attribute("explore customer1 : distance 1500") << endl;
	
    cout << conn->attribute("explore customer1 : distance 1500 expedited time 6 cost 6") << endl;
    cout << endl;

    cout << "*** connect customer1 : customer2 ****" << endl;
    cout << conn->attribute("connect customer1 : customer2") << endl;
    cout << endl;

    // -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
    cout << "# PLane segments : " << stats->attribute("Plane segment") << endl;		
    cout << "# Boat segments : " << stats->attribute("Boat segment") << endl;
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;

    cerr << "Done!" << endl;

    return 0;
}
