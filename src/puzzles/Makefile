SUBDIRS := $(wildcard */.)

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(RM) -rf */*.o */*.dSYM */*~ */*.c */*.iddfs */*.bfs