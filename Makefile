all: main.cpp special_character.o
	g++ --std=c++0x main.cpp special_character.o -o powerline-shell-cpp

special_character.o: special_character.h special_character.cpp
	g++ -c --std=c++0x special_character.cpp

clean:
	rm -f special_character.o

distclean: clean
	rm -f powerline-shell-cpp
