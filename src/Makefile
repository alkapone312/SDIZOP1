SUBDIRS = list/ exception/ file/ ui/

all: deps archive

deps: # run make file in each subdirectory
	for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir; \
		done

archive: # creates library named SDIZO linking all objects together
	find . -type f -name "*.o" | xargs ar rsc ../lib/libSDIZO.a

