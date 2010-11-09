#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include <cstdlib>
#include <cstdio>
#include "Exceptions.h"

using namespace std;

typedef string String; 


class Mile : public Ordinal<Mile, double>
  {
    public:
		String string_;
    Mile() : Ordinal<Mile, double>(0.0){
			
			string_="0.0";
		}	  
	  Mile(double val) : Ordinal<Mile, double>(val) {
		 char buf[10];
		 sprintf(buf, "%.2f", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
  };


  class Difficulty : public Ordinal<Difficulty, double>
  {
  public:
	  String string_;
	  Difficulty(): Ordinal<Difficulty, double>(0.0) {string_ = "0.0"; }
    Difficulty(double val) throw (RangeException) : Ordinal<Difficulty, double>(val){
		  if( (val < 1.0) ||  (val > 5.0) )
	    {
	      throw RangeException("Difficulty Value out of range");
	    }

			char buf[10];
			sprintf(buf, "%.2f", val);
      string_.assign(buf);
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
		static TransportType truck(){ return TransportType(1) ;}
		static TransportType boat(){ return TransportType(2) ;}
		static TransportType plane(){ return TransportType(3) ;}

	};
  




#endif
