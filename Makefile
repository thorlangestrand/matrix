all:
	g++ -Wall -I include src\main.cpp \
	-static-libgcc -static-libstdc++ -static -lsfml-graphics -lsfml-window -lsfml-system \
	-O3 -o bin/main -L lib 

z:
	g++ -Wall src/*.cpp -I include -o bin/main

sf: 
	g++ -Wall -I include src\main.cpp \
	-L lib -l sfml-graphics -l sfml-window -l sfml-system \
	-o bin/main

