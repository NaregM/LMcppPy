CXX = g++
CXXFLAGS = -I.

# ****************************************************
main: main.o linreg.o
	$(CXX) $(CXXFLAGS) -o a.out main.o linreg.o

# The main.o target can be written more simply

driver.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

myfunc.o: linreg.cpp
	$(CXX) $(CXXFLAGS) -c linreg.cpp

clean:
	rm -f *~ *.o *.out main
