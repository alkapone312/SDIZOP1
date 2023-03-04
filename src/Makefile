all: deps archive clean

deps:
	$(MAKE) -C list/

archive:
	find . -type f -name "*.o" | xargs ar rsc ../lib/libSDIZO.a

clean: # deletes all *.o file in subfolders
	find . -type f -name "*.o" | xargs rm