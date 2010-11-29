#ifndef __CONN_H__
#define __CONN_H__

#include "PtrInterface.h"
#include "Ptr.h"

#include "Segment.h"
#include "Location.h"
#include "Types.h"

#include <queue>

using namespace std;
using namespace Fwk;

namespace Shipping
{


class GraphEdge : public PtrInterface<GraphEdge>
{
  public:
	typedef Fwk::Ptr<GraphEdge> Ptr;
	typedef Fwk::Ptr<GraphEdge const> PtrConst;

	public:
	GraphEdge(){segment_ = NULL;}
  SegmentPtrConst segment() const {return segment_;}
	static GraphEdge::Ptr GraphEdgeNew(SegmentPtrConst _segment)
	{
	  return GraphEdge::Ptr(new GraphEdge(_segment));
	}
  GraphEdge(SegmentPtrConst _segment) {
	  segment_ = _segment;
	}

	private:
  Segment::PtrConst segment_;
  
	};


class GraphNode : public PtrInterface<GraphNode>
{
  public:
	typedef Fwk::Ptr<GraphNode> Ptr;
	typedef Fwk::Ptr<GraphNode const> PtrConst;

  public:
	GraphNode(){visited_ = false; location_ = NULL;}
  Location::Ptr location() const {return location_;}
   

  private:
	bool visited_;
	Location::Ptr location_;

};

class Conn : public PtrInterface<Conn>
{
  public:
	typedef Fwk::Ptr<Conn> Ptr;
	typedef Fwk::Ptr<Conn const> PtrConst;
  typedef vector<Segment*> Path;
  typedef queue<Path> PathList;
     
	
	class StatPath
	{
	  public:

		StatPath(){ path_ = new Conn::Path(); }
		StatPath(StatPath* p)
		{
		  StatPath* n = new StatPath(*p);
			n->path_ = new Path( *(p->path()) );
		}
	  Conn::Path* path() const{ return path_;}
		inline Cost cost() const {return cost_;}
		inline Mile distance() const {return distance_;}
    inline bool expedite() const {return expedite_;}
	  inline Time time() const {return time_;}	
    
		inline void pathIs(Conn::Path* _path) {path_ = _path;}
		inline void costIs(Cost _cost) {cost_ = _cost ;}
		inline void distanceIs(Mile _distance) {distance_ =  _distance;}
		inline void expediteIs(bool _expedite) {expedite_= _expedite;}
		inline void timeIs(Time _time) {time_ = _time; }

    private:
    Conn::Path* path_;
    Cost cost_;
		Mile distance_;
		bool expedite_;
		Time time_;
	
	};
  
	typedef queue<StatPath*> StatPathList;
	

	public:
	Conn(string _name) : name_(_name){routing_algo == "1";}
  string name() const {return name_;}
	void routingAlgoIs(string _algo){routing_algo = _algo;}
	string routingAlgo(){return routing_algo;}
 
  Conn::PathList path(Location::Ptr _source, Location::Ptr _destination);
  Conn::StatPathList path(Fleet::Ptr, Location::Ptr _source, Cost, Mile, bool, Time);
  static string printPathList(PathList&, Fleet::Ptr);
	static string printStatPathList(StatPathList&);
	static string printPath(Path);

	private:
	String name_;
	String routing_algo;
	void pathInternal(Location::Ptr, Conn::PathList&, Conn::PathList&);
  bool nodeExistsInPath(Location::Ptr, Conn::Path);
	void copyPath(Path&, Path&);
	//void shift(PathList&, PathList&, PathList::iterator&);
};

}
#endif
