#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include <cstdlib>
#include <cstdio>
#include "Exceptions.h"
#include "Ptr.h"
#include "PtrInterface.h"
#include "Nominal.h"

using namespace std;
 
typedef unsigned int uint32_t;


class Cost : public Ordinal<Cost, double>
  {
    public:
		String string_;
    Cost() : Ordinal<Cost, double>(1.0){
			
			string_="1.0";
		}	  
	  Cost(double val) throw (RangeException): Ordinal<Cost, double>(val){
		if(val < 0){ throw RangeException("Invalid value for type Cost");}
		 char buf[100];
		 sprintf(buf, "%.2f", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
	  static Cost nil() {  return Cost(0); }
		Cost operator+(Cost _cost) { return Cost(value_ + _cost.value());}
  };


class Time : public Ordinal<Time, double>
{
  public:
	String string_;
  Time() : Ordinal<Time, double>(0){
	 string_="0";
  }	  
  Time(double val)  throw (RangeException) : Ordinal<Time, double>(val) {
		 if(val < 0) { throw RangeException("Invalid Value for Type MPH");}
		 char buf[100];
		 sprintf(buf, "%.2f", val);
		 string_.assign(buf);
  }
		
	String string() const {return string_; }
  Time operator+(Time _time) { return Time(value_ + _time.value());}
  Time operator-(Time _time) { return Time(value_ - _time.value());}
	Time operator/(double _t) { return Time(value_ / _t);}
	Time operator*(unsigned int _t) { return Time(value_*_t);}
	static Time nil() {  return Time(0); }

};

class MPH : public Ordinal<MPH, double>
  {
    public:
		String string_;
    MPH() : Ordinal<MPH, double>(1.0){
			
			string_="1.0";
		}	  
	  MPH(double val)  throw (RangeException) : Ordinal<MPH, double>(val) {
		 if(val < 0) { throw RangeException("Invalid Value for Type MPH");}
		 char buf[100];
		 sprintf(buf, "%.2f", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
  };



class Mile : public Ordinal<Mile, double>
  {
    public:
		String string_;
    Mile() : Ordinal<Mile, double>(1.0){
			
			string_="1.0";
		}	  
	  Mile(double val) throw (RangeException) :  Ordinal<Mile, double>(val) {
		 if(val < 0) { throw RangeException("Invalid value for type Mile");}
		 char buf[100];
		 sprintf(buf, "%.2f", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
	  static Mile nil() {  return Mile(0); }

		Cost operator*(Cost _cost){ return Cost(_cost.value()*value_); } 
		Time operator/(MPH _speed) {return Time(value_/_speed.value());}
		Mile operator+(Mile _m){ return Mile(value_ + _m.value());}
  };



class Capacity : public Ordinal<Capacity, int>
  {
    public:
		String string_;
    Capacity() : Ordinal<Capacity, int>(1){
			
			string_="1";
		}	  
	  Capacity(int val) throw (RangeException): Ordinal<Capacity, int>(val) {
		 if(val < 0) { throw RangeException("Invalid Capacity Value");}
		 char buf[100];
		 sprintf(buf, "%d", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
		Capacity operator*(Capacity _capacity){ return Capacity(_capacity.value()*value_); } 
		Capacity operator/(int value){ return Capacity(value_/value); } 
  };


  class Difficulty : public Ordinal<Difficulty, double>
  {
  public:
	  Difficulty(): Ordinal<Difficulty, double>(1.0) {/*value_ = 1.0;*/ string_ = "1.0"; }
    Difficulty(double val) throw (RangeException) : Ordinal<Difficulty, double>(val){
		  if( (val < 1.0) ||  (val > 5.0) )
	    {
	      throw RangeException("Difficulty Value out of range");
	    }

			char buf[100];
			sprintf(buf, "%.2f", val);
      string_.assign(buf);
		}
		String string() const {return string_;}
		
	private:

	  String string_;
  };


class ShipmentCount;
class PackageCount : public Ordinal<PackageCount, unsigned int>
  {
    public:
		String string_;
    PackageCount() : Ordinal<PackageCount, unsigned int>(0){
			
			string_="0";
		}	
		
	  PackageCount(unsigned int val) :  Ordinal<PackageCount, unsigned int>(val) {
		char buf[100];
		 sprintf(buf, "%d", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
	  static PackageCount nil() {  return PackageCount(0); }

		PackageCount operator+(PackageCount _count) { return PackageCount(value_ + _count.value());}
		PackageCount operator-(PackageCount _count) { return PackageCount(value_ - _count.value());}

		PackageCount& operator+=(PackageCount _count) 
		{ 
	    value_ += _count.value(); 
		  char buf[100];
		  sprintf(buf, "%d", value_);
		  string_.assign(buf);
			
			return *this;
			
		}
	  PackageCount& operator-=(PackageCount _count) 
		{ 
		
		  value_ -= _count.value(); 
       char buf[100];
		  sprintf(buf, "%d", value_);
		  string_.assign(buf);
			
			return *this;
		
		}


   //PackageCount operator*=(ShipmentCount _count); 
  };



	class TransportType : public Nominal<TransportType, unsigned int>
	{
    
		private:
		TransportType(unsigned int val) : Nominal<TransportType, unsigned int>(val){}
    
		public:
    TransportType() : Nominal<TransportType, unsigned int>(0) {}		
		static const TransportType none(){ return TransportType(0) ;}
		static const TransportType truck(){ return TransportType(1) ;}
		static const TransportType boat(){ return TransportType(2) ;}
		static const TransportType plane(){ return TransportType(3) ;}

	};
  
class ShipmentCount : public Ordinal<ShipmentCount, unsigned int>
  {
    public:
		String string_;
    ShipmentCount() : Ordinal<ShipmentCount, unsigned int>(0){
			
			string_="0";
		}	
		
	  ShipmentCount(unsigned int val) :  Ordinal<ShipmentCount, unsigned int>(val) {
		char buf[100];
		 sprintf(buf, "%d", val);
		 string_.assign(buf);
		}
		
		String string() const {return string_; }
	   	
	  static ShipmentCount nil() {  return ShipmentCount(0); }

		ShipmentCount operator+(ShipmentCount _count) { return ShipmentCount(value_ + _count.value());}
		ShipmentCount operator-(ShipmentCount _count) { return ShipmentCount(value_ - _count.value());}

		ShipmentCount& operator+=(ShipmentCount _count) { 
		
		  value_ += _count.value();
			char buf[100];
		  sprintf(buf, "%d", value_);
		  string_.assign(buf);
	
			return *this;
		
		}
		ShipmentCount& operator-=(ShipmentCount _count) { 
		
		  value_ -= _count.value(); 
		  char buf[100];
		  sprintf(buf, "%d", value_);
		  string_.assign(buf);
	

		  return *this;
		}
		//PackageCount& operator*=(PackageCount _count) { value_ *= _count.value(); return *this;}

  };


//PackageCount PackageCount::operator*=(ShipmentCount _count) { return PackageCount(value_ * _count.value());}


#endif
