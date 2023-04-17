all: deps main clean

INCLUDE_DIR = include
LIB_DIR = lib
USE_LIBRARIES = -lSDIZOTest -lSDIZO 
COMPILER = x86_64-w64-mingw32-g++
ARCHIVE = x86_64-w64-mingw32-ar
export

deps: # executes makefile from src to build dependencies
	$(MAKE) -C src/
	$(MAKE) -C test/

main: main.o # links object file with libraries and output executable
	$(COMPILER) main.o -L$(LIB_DIR) $(USE_LIBRARIES) -o bin/main

main.o: main.cpp # compiles main.cpp with include and outputs object file
	$(COMPILER) -c main.cpp -I $(INCLUDE_DIR) -o main.o

clean: # deletes all *.o file in subfolders
	find . -type f -name "*.o" | xargs rm