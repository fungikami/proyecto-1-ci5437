# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=1 --bwd_history_len=0

ROOTPATH = ../../..# relative to this file

psvn2c_core.c:
	@cp $(ROOTPATH)/psvnAPI/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp $(ROOTPATH)/psvnAPI/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp $(ROOTPATH)/psvnAPI/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

priority_queue.hpp:
	cp $(ROOTPATH)/algorithms/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp $(ROOTPATH)/algorithms/node.hpp ./node.hpp

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@$(ROOTPATH)/psvnAPI/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c $(ROOTPATH)/psvnAPI/global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) $(ROOTPATH)/psvnAPI/global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c $(ROOTPATH)/psvnAPI/global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOTPATH)/psvnAPI/global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c $(ROOTPATH)/psvnAPI/global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOTPATH)/psvnAPI/global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c $(ROOTPATH)/psvnAPI/global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOTPATH)/psvnAPI/global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) $(ROOTPATH)/psvnAPI/src/abstractor.cpp $(ROOTPATH)/psvnAPI/src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `dirname $*`_`basename $*`.{abst,pdb,psvn}
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor `dirname $*`.psvn `dirname $*`_`basename $*` < `basename $*`.txt > /dev/null
	@make `dirname $*`_`basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.pdb
	@rm -f abstractor `dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.psvn

%.dist_pdb: %.c $(ROOTPATH)/psvnAPI/global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) $(ROOTPATH)/psvnAPI/global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

%.a_star: %.c $(ROOTPATH)/algorithms/a_star.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) $(ROOTPATH)/algorithms/a_star.cpp -include $< -include heuristic.cpp -o $@

%.ida_star: %.c $(ROOTPATH)/algorithms/ida_star.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) $(ROOTPATH)/algorithms/ida_star.cpp -include $< -include heuristic.cpp -o $@

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
