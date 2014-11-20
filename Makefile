all: main.cpp special_character.o color_code.o
	g++ --std=c++0x main.cpp special_character.o color_code.o -o powerline-shell-cpp

special_character.o: special_character.h special_character.cpp
	g++ -c --std=c++0x special_character.cpp

color_code.o: color_code.h color_code.cpp
	g++ -c --std=c++0x color_code.cpp

clean:
	rm -f special_character.o color_code.o

distclean: clean
	rm -f powerline-shell-cpp
