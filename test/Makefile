all: ListTest.o archive

%.o: %.cpp
	g++ -c $^ -I ../include

archive: # creates library named SDIZOTest linking all test objects together
	find . -type f -name "*.o" | xargs ar rsc ../lib/libSDIZOTest.a

