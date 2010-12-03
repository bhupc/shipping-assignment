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

	  MPH speed_[2][3];
    Capacity capacity_[2][3];
    Cost cost_[2][3];


    public:

		Fleet(const String& _name)
		{
		  name_ = _name;
		  for(int i = 0; i < 2; i++)
			{
			  for(int j = 0; j < 3; j++)
				{
					speed_[i][j] = MPH(1);
          capacity_[i][j] = Capacity(1);
          cost_[i][j] = Cost(1); 

				}
			}
		}
    
	  void costIs(uint32_t offset, Cost _cost) { 
		  cost_[0][offset] =  _cost;   
		}
		
		void speedIs(uint32_t offset, MPH _speed)
		{
		  speed_[0][offset] = _speed;
		}

		void capacityIs(uint32_t offset, Capacity _capacity)
		{
		  capacity_[0][offset] = _capacity;
		}

		Cost cost(uint32_t offset) { 
		  return cost_[0][offset];   
		}
		
		MPH speed(uint32_t offset)
		{
		  return speed_[0][offset];
		}

		Capacity capacity(uint32_t offset)
		{
		  return capacity_[0][offset];
		}
    
		void costIs(uint32_t slot, uint32_t offset, Cost _cost) { 
		  cost_[slot][offset] =  _cost;   
		}
		
		void speedIs(uint32_t slot, uint32_t offset, MPH _speed)
		{
		  speed_[slot][offset] = _speed;
		}

		void capacityIs(uint32_t slot, uint32_t offset, Capacity _capacity)
		{
		  capacity_[slot][offset] = _capacity;
		}

		Cost cost(uint32_t slot, uint32_t offset) { 
		  return cost_[slot][offset];   
		}
		
		MPH speed(uint32_t slot, uint32_t offset)
		{
		  return speed_[slot][offset];
		}

		Capacity capacity(uint32_t slot, uint32_t offset)
		{
		  return capacity_[slot][offset];
		}

protected:
	String name_;

};

}

#endif

