CXXFLAGS = -Wall -g

OBJECTS = Instance.o Segment.o Location.o Engine.o

default:	test1 example

test1:	test1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

example:	example.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f test1 example test1.o example.o $(OBJECTS) *~

Instance.o: Instance.cpp Instance.h PtrInterface.h Ptr.h Engine.h 
Segment.o: Segment.h Segment.cpp
Location.o: Location.h Segment.h Location.cpp Types.h Exceptions.h
Engine.o: Engine.h Engine.cpp
test1.o: test1.cpp Instance.h PtrInterface.h Ptr.h
