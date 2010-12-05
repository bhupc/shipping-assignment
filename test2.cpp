#include <string>
#include <set>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/signal.h>
#include <boost/lexical_cast.hpp>
#include "Instance.h"

#include "Activity.h"

using namespace std;


int main(){

    Ptr<Instance::Manager> m = shippingInstanceManager();

    /* Create a diamond-shaped graph with two alternate routes */
    m->instanceNew("a", "Customer");
    m->instanceNew("b", "Truck terminal");
    m->instanceNew("c", "Truck terminal");
    m->instanceNew("d", "Customer");
    m->instanceNew("e", "Truck terminal");

    Ptr<Instance> s;

    /* Branch #1 */
    s = m->instanceNew("1", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "yes");
    s = m->instanceNew("1r", "Truck segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("return segment", "1");
    s->attributeIs("expedite support", "no");

    s = m->instanceNew("2", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "4");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("2r", "Truck segment");
    s->attributeIs("source", "c");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "4");
    s->attributeIs("return segment", "2");
    s->attributeIs("expedite support", "no");

    /* Branch #3 */
    s = m->instanceNew("3", "Truck segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("3r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("return segment", "3");
    s->attributeIs("expedite support", "no");

    s = m->instanceNew("4", "Truck segment");
    s->attributeIs("source", "c");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "4");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("4r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "4");
    s->attributeIs("return segment", "4");
    s->attributeIs("expedite support", "no");

    /* Branch #4 */
    s = m->instanceNew("5", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "20");
    s->attributeIs("difficulty", "4");
    s->attributeIs("expedite support", "yes");
    s = m->instanceNew("5r", "Truck segment");
    s->attributeIs("source", "e");
    s->attributeIs("length", "20");
    s->attributeIs("difficulty", "4");
    s->attributeIs("return segment", "5");
    s->attributeIs("expedite support", "yes");

    s = m->instanceNew("6", "Truck segment");
    s->attributeIs("source", "e");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2");
    s->attributeIs("expedite support", "yes");
    s = m->instanceNew("6r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "20");
    s->attributeIs("difficulty", "2");
    s->attributeIs("return segment", "6");
    s->attributeIs("expedite support", "yes");

    /* Set up default values */
    Ptr<Instance> fleet = m->instanceNew("fleet", "Fleet");

    // attributes of the fleet between 8AM -8PM

    fleet->attributeIs("Truck, speed, slot 1", "1");
    fleet->attributeIs("Truck, capacity, slot 1", "10");
    fleet->attributeIs("Truck, cost, slot 1", "30");
    
    // attributes of the fleet between 8PM-8AM

		fleet->attributeIs("Truck, speed, slot 2", "2");
    fleet->attributeIs("Truck, capacity, slot 2", "10");
    fleet->attributeIs("Truck, cost, slot 2", "30");



     
    Ptr<Instance> a = m->instance("a"); 
		a->attributeIs("Transfer Rate", "10");
		a->attributeIs("Shipment Size", "5");
		a->attributeIs("Destination", "d");
	
    		
    Activity::Manager::Ptr activityManager = activityManagerInstance();
    activityManager->nowIs(100.00);
		activityManager->scaleFactorIs(0);
    

    // after simulation statistics
    
    Ptr<Instance> d = m->instance("d"); 
    std::cout << "Total packets received at d  =  " << d->attribute("Shipments Received") << "" << std::endl;
    std::cout << "Average packet latency at d  =  " << d->attribute("Average Latency") << "" << std::endl;
    std::cout << "Total delivery cost at  d  =  " << d->attribute("Total Cost") << "" << std::endl;
    std::cout << "Total ack received at  a  =  " << a->attribute("Acknowledgements Received") << "" << std::endl;

    Ptr<Instance> seg1 = m->instance("1"); 
		std::cout << "Total packets received on 1 = " << seg1->attribute("Shipments Received") << "" << std::endl;
		std::cout << "Total packets refused on 1 = " << seg1->attribute("Shipments Refused") << "" << std::endl;
    
		Ptr<Instance> seg3 = m->instance("3"); 
		std::cout << "Total packets received on 3 = " << seg3->attribute("Shipments Received") << "" << std::endl;
		std::cout << "Total packets refused on 3 = " << seg3->attribute("Shipments Refused") << "" << std::endl;






   
return 0;
}
