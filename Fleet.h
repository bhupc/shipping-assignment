#ifndef __FLEET_H__
#define __FLEET_H__


#include "PtrInterface.h"
#include "Ptr.h"
#include "Types.h"


using namespace Fwk;

namespace Shipping
{
  class Fleet : public PtrInterface<Fleet>
	{
	  /* Speed, Capacity , cost*/
    /* 0 => Boat, 1 => Plane,  2 => Truck */
		
		public:
		typedef Fwk::Ptr<Fleet> Ptr;
    typedef Fwk::Ptr<Fleet const> PtrConst;
		
		private:

	  MPH speed_[3];
    Capacity capacity_[3];
    Cost cost_[3];


    public:

		Fleet(const String& _name)
		{
		name_ = _name;
		  speed_[0] = MPH(1); speed_[1] = MPH(1); speed_[2] = MPH(1);
      capacity_[0] = Capacity(1); capacity_[1] = Capacity(1); capacity_[2] = Capacity(1);
      cost_[0] = Cost(1); cost_[1] = Cost(1); cost_[2] = Cost(1);
		}
    
	  void costIs(uint32_t offset, Cost _cost) { 
		  cost_[offset] =  _cost;   
		}
		
		void speedIs(uint32_t offset, MPH _speed)
		{
		  speed_[offset] = _speed;
		}

		void capacityIs(uint32_t offset, Capacity _capacity)
		{
		  capacity_[offset] = _capacity;
		}

		Cost cost(uint32_t offset) { 
		  return cost_[offset];   
		}
		
		MPH speed(uint32_t offset)
		{
		  return speed_[offset];
		}

		Capacity capacity(uint32_t offset)
		{
		  return capacity_[offset];
		}
protected:
	String name_;

};

}

#endif

