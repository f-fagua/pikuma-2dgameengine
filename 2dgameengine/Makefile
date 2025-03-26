build: 
	mkdir -p bin
	g++ -Wall -std=c++17 -I"./libs/" src/*.cpp `sdl2-config --libs --cflags` -I/opt/homebrew/include -L/opt/homebrew/lib -llua -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -o bin/gameengine

run:
	./bin/gameengine

clean:
	rm bin/gameengine