CXX = g++
CPPFLAGS = --std=c++0x -Wall -Wextra -Werror  -I. -Ilib -Isegments
DEPS = $(wildcard lib/*.h) $(wildcard lib/*.cpp) $(wildcard segments/*.h) $(wildcard segments/*.cpp)
OBJ  = main.o $(patsubst %.cpp,%.o,$(wildcard lib/*.cpp)) $(patsubst %.cpp,%.o,$(wildcard segments/*.cpp))


.PHONY: all
all: powerline-shell-cpp

%.o: %.c $(DEPS) main.c
	$(CXX) -c -o $@ $< $(CXXFLAGS)

powerline-shell-cpp: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)


.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: distclean
distclean: clean
	rm -f powerline-shell-cpp
