CPP_FILES := $(wildcard **/*.cpp) $(wildcard *.cpp)
OBJECT_FILES := $(patsubst %.cpp,%.o,$(CPP_FILES))

all: $(OBJECT_FILES) archive

%.o: %.cpp
	$(COMPILER) -c $^ -I ../include

archive: # creates library named SDIZOTest linking all objects together
	$(ARCHIVE) rsc ../lib/libSDIZOTest.a $(wildcard **/*.o) $(wildcard *.o)

