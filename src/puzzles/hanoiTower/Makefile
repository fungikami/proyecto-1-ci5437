CC = gcc
CXX = g++
OPT = -Wall -Ofast -Wno-unused-function -Wno-unused-variable -march=native
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --fwd_history_len=1
ROOTPATH = ../..# relative to this file
PSVNEXEC = psvnAPI/bin/psvn2c# relative to root path
BINPATH = ../../bin# relative to root path

all: hanoiTower4-12.iddfs \
	hanoiTower4-12.bfs \
	hanoiTower4-14.iddfs \
	hanoiTower4-14.bfs \
	hanoiTower4-18.iddfs \
	hanoiTower4-18.bfs

.PRECIOUS: %.c

%.c: %.psvn
	$(ROOTPATH)/$(PSVNEXEC) $(PSVNOPT) < $< > $@

%.iddfs: %.c $(ROOTPATH)/algorithms/iddfs.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/iddfs.cpp" -include $< -o $@

%.bfs: %.c $(ROOTPATH)/algorithms/bfs.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/bfs.cpp" -include $< -o $@

.PHONY: clean cleanall

clean:
	rm -fr *.dSYM *.o *~ *.c

cleanall: clean
	rm -fr *.iddfs *.bfs
