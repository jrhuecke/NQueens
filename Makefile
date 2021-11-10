CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = nqueens.o queen.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ nqueens.o queen.o 
	
queen.o: queen.cpp queen.h
	$(CXX) -g $(CXXFLAGS) -c queen.cpp
	
nqueens.o: queen.cpp queen.h nqueens.cpp
	$(CXX) -g $(CXXFLAGS) -c nqueens.cpp
	

	

	
clean:
	rm *.o
	rm nqueens