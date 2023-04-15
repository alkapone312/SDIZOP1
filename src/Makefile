CPP_FILES := $(wildcard **/*.cpp) $(wildcard *.cpp)
OBJECT_FILES := $(patsubst %.cpp,%.o,$(CPP_FILES))

all: $(OBJECT_FILES) archive

%.o: %.cpp
	g++ -c $^ -I ../include

archive: # creates library named SDIZO linking all objects together
	ar rsc ../lib/libSDIZO.a $(wildcard **/*.o) $(wildcard *.o)

