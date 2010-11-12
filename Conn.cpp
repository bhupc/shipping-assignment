#include "Conn.h"
#include <iostream>

using namespace std;
namespace Shipping
{



Conn::StatPathList Conn::path(Fleet::Ptr _fleet, Location::Ptr _source, Cost _cost, Mile _distance, bool _expedite, Time _time )
{
   Conn::StatPathList paths;
	 Conn::StatPathList results;

   vector<SegmentPtr> segments =  _source->segments();
   vector<SegmentPtr>::iterator it = segments.begin();
   
	 // These are running variables
	 Cost cost = 0;
	 Mile distance = 0;
   bool expedite = _expedite;
	 Time time = 0;

   for(; it != segments.end(); it++)
	 {
     SegmentPtr ret = (*it)->returnSegment();
     if(ret)
		 {
		   if(ret->source())
			 {
				  
			    Conn::StatPath p;
					Segment* seg = (*it).ptr();
			    if(_expedite == seg->expediteSupport())
					{
					  p.path().push_back( (*it ).ptr());
					  p.costIs(seg->cost(_fleet));
					  p.distanceIs(seg->length());
					  p.expediteIs(expedite);
						p.timeIs(time);
            paths.push(p);

				 }
					
			 }
		 }
	 }

   while(!paths.empty())
	 {
		StatPath p = paths.front();
		paths.pop();
		results.push(p);
		const Segment*& last_edge = p.path().back();
     
	  
	  Segment::Ptr ret = last_edge->returnSegment();

		Location::Ptr dest = ret->source();
		

		
    if(nodeExistsInPath(dest, p.path()))
		{
			continue;
		}

    
    vector<SegmentPtr> segments =  dest->segments();
   	vector<SegmentPtr>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtr seg = *it;
		  SegmentPtr ret = seg->returnSegment();
			if(!ret)
			{
				continue;
			}
			else
			{
			  if(!ret->source())
				{
					continue;
				}
				else
				{
				  
				  StatPath p1(p);
          if(  ((_expedite == false )||  ( (_expedite == true) && (_expedite == p.expedite()) ) )&& 
					     ( (_cost == Cost::nil()) ||  ( _cost != Cost::nil() && (( p.cost() + seg->cost(_fleet)) <= _cost ) ) )&&
							 ( (_distance == Mile::nil()) || ( _distance != Mile::nil() && ( (p.distance() + seg->length()) <= _distance) ) )&&
							 ( (_time == Time::nil() ) || ( _time != Time::nil() && ( (p.time() + seg->time(_fleet)) <= _time) ))
						)
							
					{
					  p1.path().push_back( (*it ).ptr());
					  p1.costIs(p.cost() + seg->cost(_fleet));
					  p1.distanceIs(p.distance() + seg->length());
					  p1.expediteIs(_expedite);
						p1.timeIs(p.time() + seg->time(_fleet));

            paths.push(p1);

          }

          
				}
			}
		}

	}
	
	 return results;
}

Conn::PathList Conn::path(Location::Ptr _source, Location::Ptr _destination)
{
	  Conn::PathList paths;
		Conn::PathList result;

    /* all the starting segmens */
    vector<SegmentPtr> segments =  _source->segments();
   	vector<SegmentPtr>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtr ret = (*it)->returnSegment();
		  if(ret)
			{
			  if(ret->source())
				{
				  Path p;
			    //p.push_back( GraphEdge::GraphEdgeNew(*it ));
			    p.push_back( (*it ).ptr());
          paths.push(p);
          
				}
			}
		}

		pathInternal(_destination, paths, result);
		return result;
}

void Conn::pathInternal(Location::Ptr _destination, Conn::PathList& paths, Conn::PathList& result)
{


  while(!paths.empty())
	{
		Path p = paths.front();
		paths.pop();
		const Segment*& last_edge = p.back();
     
	  
	  Segment::Ptr ret = last_edge->returnSegment();

		Location::Ptr dest = ret->source();
		

		if(dest == _destination)
		{
		  result.push(p);
		  continue;
		}

    if(nodeExistsInPath(dest, p))
		{
			continue;
		}

    
    vector<SegmentPtr> segments =  dest->segments();
   	vector<SegmentPtr>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtr ret = (*it)->returnSegment();
			if(!ret)
			{
				continue;
			}
			else
			{
			  if(!ret->source())
				{
					continue;
				}
				else
				{
				  
				  Path p1(p);
			    p1.push_back( (*it).ptr());
          paths.push(p1);
          
				}
			}
		}

	}
	

}

/*
void Conn::pathInternal(Location::Ptr _destination, Conn::PathList& paths, Conn::PathList& result)
{


  PathList::iterator pit = paths.begin();

	for(; paths.size() > 0 && pit != paths.end(); pit++)
	{
	  //Path p = (*pit);
		//GraphEdge::Ptr& last_edge = (*pit).back();
	  //Location::Ptr dest = last_edge->segment()->returnSegment()->source();
		const Segment*& last_edge = (*pit).back();
     
	  
	  Segment::Ptr ret = last_edge->returnSegment();

		Location::Ptr dest = ret->source();
		

		if(dest == _destination)
		{
		  result.push_back((*pit));
			Conn::PathList new_paths;
			shift(new_paths, paths, pit);
			paths = new_paths;
			//paths.erase(pit);
		  continue;
		}

    if(nodeExistsInPath(dest, (*pit)))
		{
		  Conn::PathList new_paths;
			shift(new_paths, paths, pit);
			paths = new_paths;

		  //paths.erase(pit);
			continue;
		}

    
    vector<SegmentPtr> segments =  dest->segments();
   	vector<SegmentPtr>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtr ret = (*it)->returnSegment();
			if(!ret)
			{
        Conn::PathList new_paths;
			  shift(new_paths, paths, pit);
			  paths = new_paths;


			  //paths.erase(pit);
				continue;
			}
			else
			{
			  if(!ret->source())
				{
          Conn::PathList new_paths;
			    shift(new_paths, paths, pit);
			    paths = new_paths;
				  
				  //paths.erase(pit);
					continue;
				}
				else
				{
				  
				  Path p1(*pit);
					//copyPath(p1, *pit);
					//p1.assign((*pit).begin(), (*pit).end());
			    p1.push_back( (*it).ptr());
          paths.push_back(p1);
          
				}
			}
		}

    Conn::PathList new_paths;
	  shift(new_paths, paths, pit);
		paths = new_paths;
	   
		//paths.erase(pit);


	}
	

  }

	*/


void Conn::copyPath(Path& p1, Path& p2)
{/*
  Path::iterator it = p2.begin();
	for(; it != p2.end(); it++)
	{
	  p1.push_back(GraphEdge::GraphEdgeNew((*it)->segment()));
	}
	*/
}

bool Conn::nodeExistsInPath(Location::Ptr loc, Path p)
{
 
  Conn::Path::iterator it = p.begin();
	for(; it != p.end(); it++)
	{
	 // if(loc == (*it)->segment()->source()) { return true;}
	    if(loc == (*it)->source()) { return true;}

	  //Segment::Ptr ret = (*it)->segment()->returnSegment();
		//if(loc == ret->source()) {return true;}
	}

	return false;
}

void Conn::printPathList(PathList& paths)
{

  cout << "\n\nPrinting path list \n\n";
  while(!paths.empty())
	{
	  Conn::printPath(paths.front());
	  paths.pop();
	}
	
}

void Conn::printPath(Path p)
{
  Conn::Path::iterator it = p.begin();

	for(; it != p.end(); it++)
	{
	  std::cout << (*it)->source()->name() << " ";
	}
	
	//SegmentPtrConst last_segment = p.back()->segment();
 // std::cout << last_segment->returnSegment()->source()->name() << "\n";

	const Segment*& last_segment = p.back();
  std::cout << last_segment->returnSegment()->source()->name() << "\n";
}

void Conn::printStatPathList(StatPathList& paths)
{
  cout << "\n\nPrinting path list \n\n";
  while(!paths.empty())
	{
	  Conn::printPath(paths.front().path());
	  paths.pop();
	}
	

}

}
