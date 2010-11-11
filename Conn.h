#ifndef __CONN_H__
#define __CONN_H__

#include "PtrInterface.h"
#include "Ptr.h"

#include "Segment.h"
#include "Location.h"
#include "Types.h"

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
	  return Ptr(new GraphEdge(_segment));
	}
	private:
  Segment::PtrConst segment_;

	GraphEdge(SegmentPtrConst _segment) : segment_(_segment) {}
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
  typedef vector<GraphEdge::Ptr> Path;
  typedef vector<Path> PathList;


	public:
	Conn(string _name) : name_(_name){}
  string name() const {return name_;}

 
  Conn::PathList path(Location::Ptr _source, Location::Ptr _destination);
    	
	private:
	String name_;
	void pathInternal(Location::Ptr, Conn::PathList&, Conn::PathList&);
  bool nodeExistsInPath(Location::Ptr, Conn::Path);
};

}
#endif
