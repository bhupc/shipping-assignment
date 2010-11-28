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

using namespace std;


void testExplore1() {

    /* Simple network, arranged in a line */
    Ptr<Instance::Manager> m = shippingInstanceManager();
    
		Ptr<Instance> fleet = m->instanceNew("fleet", "Fleet");
    fleet->attributeIs("Truck, speed", "1");
    fleet->attributeIs("Truck, capacity", "20");
    fleet->attributeIs("Truck, cost", "30");


    m->instanceNew("1", "Truck terminal");
    m->instanceNew("2", "Port");
    m->instanceNew("3", "Port");
    m->instanceNew("4", "Boat terminal");

    Ptr<Instance> s12 = m->instanceNew("s12", "Truck segment");
    Ptr<Instance> s21 = m->instanceNew("s21", "Truck segment");
    Ptr<Instance> s23 = m->instanceNew("s23", "Plane segment");
    Ptr<Instance> s32 = m->instanceNew("s32", "Plane segment");
    Ptr<Instance> s34 = m->instanceNew("s34", "Boat segment");
    Ptr<Instance> s43 = m->instanceNew("s43", "Boat segment");

    s12->attributeIs("length", "10");
    s21->attributeIs("length", "10");
    s23->attributeIs("length", "20");
    s32->attributeIs("length", "20");
    s34->attributeIs("length", "30"); 
    s43->attributeIs("length", "30");

    s12->attributeIs("source", "1");
    s12->attributeIs("return segment", "s21");
    s21->attributeIs("source", "2");

    s23->attributeIs("source", "2");
    s23->attributeIs("return segment", "s32");
    s32->attributeIs("source", "3");
    
    s34->attributeIs("source", "3");
    s34->attributeIs("return segment", "s43");
    s43->attributeIs("source", "4");

    Ptr<Instance> conn = m->instanceNew("conn", "Conn");
		conn->attribute("explore 1 : distance 10000");
 //   set<string> t = tokenize(conn->attribute("explore 1 : distance 100000000"));
//    ASSERT(contains(t, "1(s12:10.00:s21) 2"));
//    ASSERT(contains(t, "1(s12:10.00:s21) 2(s23:20.00:s32) 3"));
//    ASSERT(contains(t, "1(s12:10.00:s21) 2(s23:20.00:s32) 3(s34:30.00:s43) 4"));
}





void testConn3() {
    Ptr<Instance::Manager> m = shippingInstanceManager();

    /* This tests a network that has unconnected parts, and checks
     * to make sure that connect returns no paths */
   Ptr<Instance> fleet = m->instanceNew("fleet", "Fleet");
    fleet->attributeIs("Truck, speed", "1");
    fleet->attributeIs("Truck, capacity", "20");
    fleet->attributeIs("Truck, cost", "30");

   
    m->instanceNew("a", "Port");
    m->instanceNew("b", "Port");
    m->instanceNew("c", "Port");
    m->instanceNew("d", "Port");
    
    Ptr<Instance> s;
    s = m->instanceNew("1", "Truck segment");
    s->attributeIs("source", "a");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2"); 
    s->attributeIs("expedite support", "no");

    s = m->instanceNew("1r", "Truck segment");
    s->attributeIs("source", "b");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2"); 
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "1");

    s = m->instanceNew("2", "Truck segment");
    s->attributeIs("source", "c");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2"); 
    s->attributeIs("expedite support", "no");

    s = m->instanceNew("2r", "Truck segment");
    s->attributeIs("source", "d");
    s->attributeIs("length", "10");
    s->attributeIs("difficulty", "2"); 
    s->attributeIs("expedite support", "no");
    s->attributeIs("return segment", "2");

    Ptr<Instance> conn = m->instanceNew("conn", "Conn");
    conn->attribute("connect a : d");
		//ASSERT(tokenize(conn->attribute("connect a : d")).empty());
}

void testExplore2() {
    Ptr<Instance::Manager> m = shippingInstanceManager();

    Ptr<Instance> fleet = m->instanceNew("fleet", "Fleet");
    fleet->attributeIs("Truck, speed", "1");
    fleet->attributeIs("Truck, capacity", "20");
    fleet->attributeIs("Truck, cost", "30");


    /* Make a ring of segments that meets back around at the first port */
    for (int i = 0; i <= 3; i++) {
        string id = boost::lexical_cast<string>(i+1);
        Ptr<Instance> loc = m->instanceNew(id, "Port"); 
    }
    for (int i = 0; i <= 3; i++) {
        string from = boost::lexical_cast<string>(i + 1);
        string to = boost::lexical_cast<string>(((i + 1) % 4) + 1);

        string seg1name = "s" + from + to;
        string seg2name = "s" + to + from;
        Ptr<Instance> seg1 = m->instanceNew(seg1name, "Truck segment");
        Ptr<Instance> seg2 = m->instanceNew(seg2name, "Truck segment");

        seg1->attributeIs("length", "10");
        seg2->attributeIs("length", "10");
        
        seg1->attributeIs("source", from);
        seg1->attributeIs("return segment", seg2name);
        seg2->attributeIs("source", to);
    }
    
    /* Now query to see what happens when there is a cycle in 
       the graph */
    Ptr<Instance> conn = m->instanceNew("conn", "Conn");
    
    conn->attribute("explore 1 : distance 10000");
    //set<string> t = tokenize(conn->attribute("explore 1 : distance 10000"));
    //set<string> t = tokenize(conn->attribute("explore 1 : distance 100000000"));
    
//    ASSERT(contains(t, "1(s12:10.00:s21) 2(s23:10.00:s32) 3(s34:10.00:s43) 4"));
  //  ASSERT(contains(t, "1(s14:10.00:s41) 4(s43:10.00:s34) 3(s32:10.00:s23) 2"));
    //ASSERT(contains(t, "1(s12:10.00:s21) 2(s23:10.00:s32) 3"));
    //ASSERT(contains(t, "1(s14:10.00:s41) 4(s43:10.00:s34) 3"));
    //ASSERT(contains(t, "1(s12:10.00:s21) 2"));
    //ASSERT(contains(t, "1(s14:10.00:s41) 4"));
}

void testConn1() {
    Ptr<Instance::Manager> m = shippingInstanceManager();

    /* Create a diamond-shaped graph with two alternate routes */
    m->instanceNew("a", "Truck terminal");
    m->instanceNew("b", "Truck terminal");
    m->instanceNew("c", "Truck terminal");
    m->instanceNew("d", "Truck terminal");
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
    fleet->attributeIs("Truck, capacity", "20");
    fleet->attributeIs("Truck, cost", "30");

    Ptr<Instance> conn = m->instanceNew("conn", "Conn");  
    cout << conn->attribute("connect a : d") << "\n";
    //set<string> t = tokenize(conn->attribute("connect a : d"));
		
    //ASSERT(contains(t, "60.00 2.00 no; a(1:1.00:1r) b(3:1.00:3r) d"));
    //ASSERT(contains(t, "2400.00 20.00 no; a(2:10.00:2r) c(4:10.00:4r) d"));
    // REMOVED because spec was unclear
    //ASSERT(contains(t, "3000.00 30.00 no; a(5:20.00:5r) e(6:10.00:6r) d"));
    //ASSERT(contains(t, "4500.00 23.08 yes; a(5:20.00:5r) e(6:10.00:6r) d"));

}



int main(int ac, char** av)
{
  //testConn3();
	//testExplore1();
	//testExplore2();
	testConn1();
}



