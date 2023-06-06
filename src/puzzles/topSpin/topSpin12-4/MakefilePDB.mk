# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0

psvn2c_core.c:
	@cp ../../../psvnAPI/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ../../../psvnAPI/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ../../../psvnAPI/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@../../../psvnAPI/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../../../psvnAPI/global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) ../../../psvnAPI/global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c ../../../psvnAPI/global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../../psvnAPI/global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ../../../psvnAPI/global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../../psvnAPI/global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ../../../psvnAPI/global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../../psvnAPI/global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ../../../psvnAPI/src/abstractor.cpp ../../../psvnAPI/src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `dirname $*`_`basename $*`.{abst,pdb,psvn}
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor `dirname $*`.psvn `dirname $*`_`basename $*` < `basename $*`.txt > /dev/null
	@make -f MakefilePDB.mk `dirname $*`_`basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.pdb
	@rm -f abstractor `dirname $*`_`basename $*`.distSummary

%.dist_pdb: %.c ../../../psvnAPI/global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../../psvnAPI/global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
