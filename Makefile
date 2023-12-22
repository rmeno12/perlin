CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17
DEBUGFLAGS = -g

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o main main.cpp

clean:
	rm -f main
