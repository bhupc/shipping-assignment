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
    s->attributeIs("expedite support", "no");
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
    fleet->attributeIs("Truck, speed", "1");
    fleet->attributeIs("Truck, capacity", "10");
    fleet->attributeIs("Truck, cost", "30");

     
    Ptr<Instance> a = m->instance("a"); 
		a->attributeIs("Transfer Rate", "10");
		a->attributeIs("Shipment Size", "5");
		a->attributeIs("Destination", "d");
	
    		
    Activity::Manager::Ptr activityManager = activityManagerInstance();
    activityManager->nowIs(10.00);
    

return 0;
}
