#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include "Exceptions.h"

using namespace std;

typedef string String; 


class Mile : public Ordinal<Mile, unsigned int>
  {
    public:
    Mile() : Ordinal<Mile, unsigned int>(0){}	  
	  Mile(unsigned int val) : Ordinal<Mile, unsigned int>(val) {}
  };


  class Difficulty : public Ordinal<Difficulty, float>
  {
  public:
	  Difficulty(): Ordinal<Difficulty, float>(0.0) {}
    Difficulty(float val) throw (RangeException) : Ordinal<Difficulty, float>(val){
		  if( (val < 1.0) ||  (val > 5.0) )
	    {
	      throw RangeException("Difficulty Value out of range");
	    }

		}
		
	private:

  };

	class TransportType : public Nominal<TransportType, unsigned int>
	{
    
		private:
		TransportType(unsigned int val) : Nominal<TransportType, unsigned int>(val){}
    
		public:
    TransportType() : Nominal<TransportType, unsigned int>(0) {}		
		static TransportType none(){ return TransportType(0) ;}
		static TransportType truck_(){ return TransportType(1) ;}
		static TransportType boat_(){ return TransportType(2) ;}
		static TransportType plane_(){ return TransportType(3) ;}

	};
  




#endif
