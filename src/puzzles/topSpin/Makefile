CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --no_state_map --no_abstraction --backwards_moves --fwd_history_len=1

psvn2c_core.c:
	cp ../../psvnAPI/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../psvnAPI/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../psvnAPI/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ./%.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../psvnAPI/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.iddfs: %.c ../../algorithms/IDDFS.cpp
	$(CXX) $(OPT) ../../algorithms/IDDFS.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.iddfs psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~
