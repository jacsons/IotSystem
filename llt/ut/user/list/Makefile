CXX     = g++
CC 		= gcc
LD      = ld

target = gtest-demo
CFLAGS 	:= -O2 -g -Wall -fmessage-length=0 
LDFLAGS= -std=c++11 -L/usr/lib/ -lgtest -ldl
		
INCLUDE := -I../../../../hardware/com/include/ -I/usr/include/gtest/
SRCS := ./test_main.cpp ../../../../hardware/com/src/zmmalloc.c
objs += $(SRCS:.c=.o)
objs += $(SRCS:.cpp=.o)

$(target): $(objs)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o:%.c
	${CC} $(CFLAGS) $(INCLUDE) -c -o $@ $< 
%.0:%.cpp
	${CXX} $(CFLAGS) $(INCLUDE) -c -o $@ $< 

all:$(TARGET)
clean:
	rm -f *.o
