#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__
#include "Types.h"
#include <exception>


using namespace std;

typedef string String;

class Exception : public exception
{
  private:
	  String  what_;
	
	public:

		Exception(String _what)
		{
		  what_ = _what;
		}
    
		~Exception() throw() {}
		const char* what() const throw()
		{
		  return what_.c_str();
		}
};

class RangeException : public Exception
{
  public:
  RangeException(String _what) : Exception(_what){}
};

class IllegalSegmentException : public Exception
{
  public:
  IllegalSegmentException(String _what) : Exception(_what){}
};

#endif

