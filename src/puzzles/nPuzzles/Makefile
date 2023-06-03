CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --fwd_history_len=1
ROOTPATH = ../..# relative to this file
PSVNEXEC = psvnAPI/bin/psvn2c# relative to root path

.PRECIOUS: %.c

%.c: %.psvn
	$(ROOTPATH)/$(PSVNEXEC) $(PSVNOPT) < $< > $@

%.iddfs: %.c $(ROOTPATH)/algorithms/IDDFS.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/IDDFS.cpp" -include $< -o $@
	rm -f $*.c

%.bfs: %.c $(ROOTPATH)/algorithms/BFS.cpp
	$(CXX) $(OPT) "${ROOTPATH}/algorithms/BFS.cpp" -include $< -o $@

.PHONY: clean

clean:
	rm -fr *.iddfs *.bfs *.dSYM *.o *~ *.c
