SRCS = bmplib.cpp hbook.cpp main.cpp mbook.cpp pbook.cpp point.cpp
OBJS = $(SRCS:.cpp=.o)

CXX = g++ -pthread --std=c++11 -O0

.SUFFIXES: .cc .o
.cpp.o:
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

default: arena
all: arena

arena: $(OBJS)
	$(CXX) -o $@ $^ $(LD_FLAGS)

clean:
	/bin/rm -f *.o
	/bin/rm -f arena