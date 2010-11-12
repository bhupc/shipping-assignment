CXXFLAGS = -Wall -g

OBJECTS = Instance.o Segment.o Location.o Engine.o Conn.o

default:	test1 example

test1:	test1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

example:	example.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f test1 example test1.o example.o $(OBJECTS) *~

Instance.o: Instance.h Instance.cpp PtrInterface.h Ptr.h Engine.h Location.h Segment.h 
Segment.o: Segment.h Segment.cpp Types.h
Location.o: Location.h Segment.h Location.cpp Types.h Exceptions.h
Engine.o: Engine.h Engine.cpp Stats.h Fleet.h 
Conn.o: Conn.h Conn.cpp Types.h
test1.o: test1.cpp Instance.h PtrInterface.h Ptr.h
example.o: example.cpp
