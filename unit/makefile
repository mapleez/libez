# author : ez
# date : 2015/10/29
# describe : compile all the unit testing

BASE = ..
INCLUDE = $(BASE)/src

CFLAGS = -g -I$(INCLUDE) -I$(INCLUDE)/internet
CC = gcc
OBJFLAG = -o
LIBNAME = $(BASE)/libez.a
LIBHEAD = $(INCLUDE)/ez.h
CXXFLAGS = $(CFLAGS)
# list_unit
EXEFILES = stack_unit sort_unit sock_unit bytes_unit log_unit mbs_unit ez_basicunit dlist_unit gstack_unit btree_unit minheap_unit math_unit util_unit bigint_unit net_utils_unit

.PHONY: all clean

all: $(EXEFILES)

$(EXEFILES): $(LIBNAME) ez_unit.o

ez_unit.o: $(INCLUDE)/ez.h $(INCLUDE)/ez_unit.h

# %: %.c
# 	$(CC) $(CFLAGS) $(OBJFLAG) $@ $^

# ez_stack:  $(LIBNAME) $(INCLUDE)/ez_stack.h $(LIBHEAD)
# ez_list:   $(LIBNAME) $(INCLUDE)/ez_list.h $(LIBHEAD)
# ez_sort:   $(LIBNAME) $(INCLUDE)/ez_sort.h $(LIBHEAD)
# ez_search: $(LIBNAME) $(INCLUDE)/ez_search.h $(LIBHEAD)
# ez_modbus: $(LIBNAME) $(INCLUDE)/ez_modbus.h $(LIBHEAD)

clean:
	@rm $(EXEFILES)
	@rm ez_unit.o

