#include <iostream>
#include <vector>
#include "Instance.h"
#include "ActivityImpl.h"
#include<sstream>
using namespace std;

string Stringify(int i){
	stringstream s;
	s << i;
	return s.str();
}
int main(int argc, char *argv[]) {
	try
	{
		Ptr<Instance::Manager> manager = shippingInstanceManager();

		/* Set up the network */
		vector< Ptr<Instance> > cust_locs;
		vector< Ptr<Instance> > lev1_seg;
		vector< Ptr<Instance> > lev1_seg_r;


		Ptr<Instance> destination = manager->instanceNew("Destination", "Customer");

		// Make 100 sources pointing to above destination
    int num_left_srcs = 100;
		for(int i=1;i<=num_left_srcs;i++){

			string src_name = "cust" + Stringify(i);
			Ptr<Instance> cust_loc = manager->instanceNew(src_name, "Customer");
			cust_locs.push_back(cust_loc);

			string seg_name = "seg" + Stringify(i);
			Ptr<Instance> truck_seg = manager->instanceNew(seg_name,"Truck segment"); 
			lev1_seg.push_back(truck_seg);
			truck_seg->attributeIs("source",src_name);

			string seg_name_r = "seg" + Stringify(i) + "r";
			Ptr<Instance> rev_truck_seg =  manager->instanceNew(seg_name_r,"Truck segment");
			lev1_seg_r.push_back(rev_truck_seg);
			rev_truck_seg->attributeIs("return segment",seg_name);
			rev_truck_seg->attributeIs("source","Destination");
		}

		Ptr<Instance> lev3_truck_terminal = manager->instanceNew("lev3_truck_terminal","Truck terminal");

		Ptr<Instance> seg23 = manager->instanceNew("main_seg23","Truck segment");
		seg23->attributeIs("source","Destination");

		Ptr<Instance> seg32 = manager->instanceNew("main_seg32","Truck segment");

		seg32->attributeIs("source","lev3_truck_terminal");
		seg32->attributeIs("return segment","main_seg23");


			int j_limit = 10;
			for(int j=1;j<=j_limit;j++){
				string lev4_term_name = "lev4_term"+ Stringify(j);
				Ptr<Instance> lev4_term = manager->instanceNew(lev4_term_name,"Truck terminal");

				string seg_name = "lev4_seg" + Stringify(j);
				Ptr<Instance> truck_seg = manager->instanceNew(seg_name,"Truck segment");
				truck_seg->attributeIs("source","lev3_truck_terminal");

				string seg_name_r = "lev4_seg" + Stringify(j) + "r";
				Ptr<Instance> rev_truck_seg =  manager->instanceNew(seg_name_r,"Truck segment");
				rev_truck_seg->attributeIs("return segment",seg_name);
				rev_truck_seg->attributeIs("source",lev4_term_name);

				/* Now build 10 more customers from each of these leav4_term_name*/
        int k_limit = 10;
				for(int k=1;k<=k_limit;k++){
					string lev5_cust_name = "lev5_cust"+ Stringify(j) +Stringify(k);
					Ptr<Instance> lev5_cust = manager->instanceNew(lev5_cust_name,"Customer");
					cust_locs.push_back(lev5_cust);

					string seg_name = "lev5_seg" + Stringify(j)+ Stringify(k);
					Ptr<Instance> truck_seg = manager->instanceNew(seg_name,"Truck segment");
					truck_seg->attributeIs("source",lev4_term_name);

					string seg_name_r = "lev5_seg" + Stringify(j)+ Stringify(k) + "r";
					Ptr<Instance> rev_truck_seg =  manager->instanceNew(seg_name_r,"Truck segment");
					rev_truck_seg->attributeIs("return segment",seg_name);
					rev_truck_seg->attributeIs("source",lev5_cust_name);


				}

			}

    Ptr<Instance> fleet = manager->instanceNew("fleet", "Fleet");

    // attributes of the fleet between 8AM -8PM

    fleet->attributeIs("Truck, speed, slot 1", "1");
    fleet->attributeIs("Truck, capacity, slot 1", "10");
    fleet->attributeIs("Truck, cost, slot 1", "30");
    
    // attributes of the fleet between 8PM-8AM

		fleet->attributeIs("Truck, speed, slot 2", "1");
    fleet->attributeIs("Truck, capacity, slot 2", "10");
    fleet->attributeIs("Truck, cost, slot 2", "30");




	Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
	//conn->attributeIs("routing algorithm", "Dijkstra"); 
	conn->attributeIs("routing algorithm", "1"); 
	
	/*
	cout << conn->attribute("connect Destination : lev5_cust11") << endl;

	cout << conn->attribute("connect lev4_term1 : lev5_cust11") << endl;

	cout << conn->attribute("connect Destination : lev3_truck_terminal") << endl;;
	cout << conn->attribute("connect Destination : cust1") << endl;
*/

	vector<Ptr<Instance> >::iterator itr = cust_locs.begin();

	int index = 0;
	for(;itr!=cust_locs.end();itr++){
		(*itr)->attributeIs("Transfer Rate", "1");
		int i = (index<100)?100:(rand()%1000 +1);
		index++;
		(*itr)->attributeIs("Shipment Size", Stringify(i));
		(*itr)->attributeIs("Destination", "Destination");
	}

 

	Activity::Manager::Ptr activityManager = activityManagerInstance();
	
	// Set the scaleFactor to 0.0 to behave like a virtual activity manager 
	activityManager->scaleFactorIs(0.0);
  // Start the simulation now	
	activityManager->nowIs(24.0);
	
	// Print statistics

  Ptr<Instance> d = manager->instance("Destination"); 

	std::cout << "Total packets received at d  =  " << d->attribute("Shipments Received") << "" << std::endl;
    std::cout << "Average packet latency at d  =  " << d->attribute("Average Latency") << "" << std::endl;
    std::cout << "Total delivery cost at  d  =  " << d->attribute("Total Cost") << "" << std::endl;


  Ptr<Instance> seg1 = manager->instance("main_seg32"); 
		std::cout << "Total packets received on 1 = " << seg1->attribute("Shipments Received") << "" << std::endl;
		std::cout << "Total packets refused on 1 = " << seg1->attribute("Shipments Refused") << "" << std::endl;
  
  
	
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

