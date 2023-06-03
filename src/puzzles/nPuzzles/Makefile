CC = gcc
CXX = g++
OPT = -Wall -Ofast -Wno-unused-function -Wno-unused-variable -march=native
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --fwd_history_len=1
ROOTPATH = ../..# relative to this file
PSVNEXEC = psvnAPI/bin/psvn2c# relative to root path
BINPATH = ../../bin# relative to root path

all: 15puzzle.iddfs \
	15puzzle.bfs \
	24puzzle.iddfs \
	24puzzle.bfs

.PRECIOUS: %.c

%.c: %.psvn
	$(ROOTPATH)/$(PSVNEXEC) $(PSVNOPT) < $< > $@

%.iddfs: %.c $(ROOTPATH)/algorithms/IDDFS.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/IDDFS.cpp" -include $< -o $@

%.bfs: %.c $(ROOTPATH)/algorithms/BFS.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/BFS.cpp" -include $< -o $@

.PHONY: clean cleanall

clean:
	rm -fr *.dSYM *.o *~ *.c

cleanall: clean
	rm -fr *.iddfs *.bfs
