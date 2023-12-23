CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17
DEBUGFLAGS = -g

all: main

vis: main vis.py
	./main | python vis.py

main: main.cpp
	$(CXX) $(CXXFLAGS) -MM -MT $@ -o $@.d $<
	$(CXX) $(CXXFLAGS) -o $@ $<
-include main.d

debug: main.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -MM -MT $@ -o $@.d $<
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f main
