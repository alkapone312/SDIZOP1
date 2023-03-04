all: deps main clean

INCLUDE_DIR = include
LIB_DIR = lib
USE_LIBRARIES = -lSDIZO

deps:
	$(MAKE) -C src/

main: main.o
	g++ main.o -L$(LIB_DIR) $(USE_LIBRARIES) -o bin/main

main.o: main.cpp
	g++ -c main.cpp -I $(INCLUDE_DIR) -o main.o

clean: # deletes all *.o file in subfolders
	find . -type f -name "*.o" | xargs rm