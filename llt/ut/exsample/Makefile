TARGET=test
GFLAG ="-fPIC -Wall -std=c++11"

all:
	gtest-config --min-version=1.0 || echo "Insufficient Google Test version."
	g++  $(gtest-config --cppflags --CXXFLAGS) $GFLAG -o $(TARGET).o -c test.cpp
	g++  $(gtest-config --ldflags --libs) -o $(TARGET) $(TARGET).o

print:
	@echo $CXXFLAGS
	@echo $GFLAG


clean:
	rm -rf *.o $(TARGET)
