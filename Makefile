CXX = g++
CPPFLAGS = --std=c++0x -I. -Ilib
DEPS =
OBJ  = main.o $(patsubst %.cpp,%.o,$(wildcard lib/*.cpp))


.PHONY: all
all: powerline-shell-cpp

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

powerline-shell-cpp: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)


.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: distclean
distclean: clean
	rm -f powerline-shell-cpp
