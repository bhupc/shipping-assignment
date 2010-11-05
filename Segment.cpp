#include "Segment.h"
#include "Exceptions.h"

Difficulty::Difficulty(float val) : Ordinal<Difficulty, float>(val)
{
  if( (val < 1.0) ||  (val > 5.0) )
	{
	   throw RangeException("Difficulty Value out of range");
	}


}


