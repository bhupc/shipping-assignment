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


int main(int ac, char** av){

    if(ac!=3){
		cout << "Correct usage is ./verification <A-size> <B-size>, e.g. ./verification 40 40" << endl;
		return 0;
	}

    Ptr<Instance::Manager> m = shippingInstanceManager();

    /* Create a diamond-shaped graph with two alternate routes */
    m->instanceNew("a", "Customer");
    m->instanceNew("b", "Customer");
    m->instanceNew("c", "Customer");
    m->instanceNew("d", "Truck terminal");
    m->instanceNew("e", "Truck terminal");
    m->instanceNew("f", "Customer");

    Ptr<Instance> s;

    /* Branch #1 */

/*
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
*/

    s = m->instanceNew("2", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "200000");
    s->attributeIs("difficulty", "4");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("2r", "Truck segment");
    s->attributeIs("source", "c");
    s->attributeIs("length", "200000");
    s->attributeIs("difficulty", "4");
    s->attributeIs("return segment", "2");
    s->attributeIs("expedite support", "no");

    /* Branch #3 */
    s = m->instanceNew("3", "Truck segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "1000000");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "no");
    s = m->instanceNew("3r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "1000000");
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
    s->attributeIs("length", "20");
    s->attributeIs("difficulty", "2");
    s->attributeIs("expedite support", "yes");
    s = m->instanceNew("6r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "20");
    s->attributeIs("difficulty", "2");
    s->attributeIs("return segment", "6");
    s->attributeIs("expedite support", "yes");

    // segment from b to e
    s = m->instanceNew("7", "Truck segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2");
    s->attributeIs("expedite support", "yes");
    s->attributeIs("Capacity", "80");
    s = m->instanceNew("7r", "Truck segment");
    s->attributeIs("source", "e");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2");
    s->attributeIs("return segment", "7");
    s->attributeIs("expedite support", "yes");
    
    s = m->instanceNew("8", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("expedite support", "yes");
    s = m->instanceNew("8r", "Truck segment");
    s->attributeIs("source", "f");
    s->attributeIs("length", "1");
    s->attributeIs("difficulty", "1");
    s->attributeIs("return segment", "8");
    s->attributeIs("expedite support", "no");

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

	  Ptr<Instance> conn = m->instanceNew("myConn", "Conn");
	  conn->attributeIs("routing algorithm", "Dijkstra"); 
    std::cout << conn->attribute("connect b : c")	<< std::endl;
    std::cout << conn->attribute("connect a : f")	<< std::endl;

    
		


    Ptr<Instance> b = m->instance("b"); 
		b->attributeIs("Transfer Rate", "10");
		b->attributeIs("Shipment Size", av[2]);
		b->attributeIs("Destination", "c");

	
	  Ptr<Instance> a = m->instance("a"); 
		a->attributeIs("Transfer Rate", "10");
		a->attributeIs("Shipment Size", av[1]);
		a->attributeIs("Destination", "f");
	

    Activity::Manager::Ptr activityManager = activityManagerInstance();
		activityManager->scaleFactorIs(0);
    activityManager->nowIs(20000.00);
    

    // after simulation statistics
   
    std::cout << "==================================================" << std::endl;
    std::cout << "Shipment size for a is " << av[1] << " and for b is " << av[2] << std::endl;

    Ptr<Instance> d = m->instance("f"); 
    std::cout << "Total packets received at f  =  " << d->attribute("Shipments Received") << "" << std::endl;
    std::cout << "Average packet latency at f  =  " << d->attribute("Average Latency") << "" << std::endl;
    std::cout << "Total delivery cost at  f  =  " << d->attribute("Total Cost") << "" << std::endl;

    
		Ptr<Instance> c = m->instance("c"); 
    std::cout << "Total packets received at c  =  " << c->attribute("Shipments Received") << "" << std::endl;
    std::cout << "Average packet latency at c  =  " << c->attribute("Average Latency") << "" << std::endl;
    std::cout << "Total delivery cost at   c =  " << c->attribute("Total Cost") << "" << std::endl;
   

    std::cout << "==================================================" << std::endl;
    /*
		Ptr<Instance> seg1 = m->instance("1"); 
		std::cout << "Total packets received on 1 = " << seg1->attribute("Shipments Received") << "" << std::endl;
		std::cout << "Total packets refused on 1 = " << seg1->attribute("Shipments Refused") << "" << std::endl;
    
		Ptr<Instance> seg3 = m->instance("3"); 
		std::cout << "Total packets received on 3 = " << seg3->attribute("Shipments Received") << "" << std::endl;
		std::cout << "Total packets refused on 3 = " << seg3->attribute("Shipments Refused") << "" << std::endl;
*/





   
return 0;
}
