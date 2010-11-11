#include "Conn.h"
#include <iostream>

using namespace std;
namespace Shipping
{


Conn::PathList Conn::path(Location::Ptr _source, Location::Ptr _destination)
{
	  Conn::PathList paths;
		Conn::PathList result;

    /* all the starting segmens */
    vector<SegmentPtrConst> segments =  _source->segments();
   	vector<SegmentPtrConst>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtrConst ret = (*it)->returnSegment();
		  if(ret)
			{
			  if(ret->source())
				{
				  Path p;
			    p.push_back( GraphEdge::GraphEdgeNew(*it));
          paths.push_back(p);
          
				}
			}
		}

		pathInternal(_destination, paths, result);
		return result;
}




void Conn::pathInternal(Location::Ptr _destination, Conn::PathList& paths, Conn::PathList& result)
{


  PathList::iterator pit = paths.begin();

	for(; pit != paths.end(); pit++)
	{
	  Path p = (*pit);
		GraphEdge::Ptr last_edge = p.back();
	  Location::Ptr dest = last_edge->segment()->returnSegment()->source();
     
		if(dest == _destination)
		{
		  result.push_back(p);
			paths.erase(pit);
		  continue;
		}

    if(nodeExistsInPath(dest, p))
		{
		  paths.erase(pit);
			continue;
		}

    
    vector<SegmentPtrConst> segments =  dest->segments();
   	vector<SegmentPtrConst>::iterator it = segments.begin();
    
	  for(; it != segments.end(); it++)
	  {
		  SegmentPtrConst ret = (*it)->returnSegment();
			if(!ret)
			{
			  paths.erase(pit);
				continue;
			}
			else
			{
			  if(!ret->source())
				{
				  paths.erase(pit);
					continue;
				}
				else
				{
				  Path p1(p);
			    p1.push_back( GraphEdge::GraphEdgeNew(*it) );
          paths.push_back(p1);
          
				}
			}
		}

		paths.erase(pit);


	}
	

  }


bool Conn::nodeExistsInPath(Location::Ptr loc, Path p)
{
  Conn::Path::iterator it = p.begin();
	for(; it != p.end(); it++)
	{
	  if(loc == (*it)->segment()->source()) { return true;}
	  Segment::Ptr ret = (*it)->segment()->returnSegment();
		if(loc == ret->source()) {return true;}
	}

	return false;
}

void Conn::printPathList(PathList& paths)
{
  cout << "\n\nPrinting path list \n\n";
  PathList::iterator it = paths.begin();
  for(; it != paths.end(); it++)
	{
	  Conn::printPath(*it);
	}
}

void Conn::printPath(Path& p)
{
  Conn::Path::iterator it = p.begin();

	for(; it != p.end(); it++)
	{
	  std::cout << (*it)->segment()->source()->name() << " ";
	}
	
	SegmentPtrConst last_segment = p.back()->segment();
  std::cout << last_segment->returnSegment()->source()->name() << "\n";

}

}
