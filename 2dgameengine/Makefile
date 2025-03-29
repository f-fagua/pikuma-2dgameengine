################################################################################
# Declare some Makefile variables
################################################################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/" -I/opt/homebrew/include
SRC_FILES = ./src/*.cpp \
			./src/Game/*.cpp \
			./src/Logger/*.cpp
LINKER_FLAGS = `sdl2-config --libs --cflags` -L/opt/homebrew/lib -llua -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
OBJ_NAME = bin/gameengine

################################################################################
# Declare some Makefile rules
################################################################################
build: 
	mkdir -p bin
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)