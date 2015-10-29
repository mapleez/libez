# author : ez
# date : 2015/5/18
# describe : compile the stack structure module

CC =gcc
CFLAG =-c
OBJFLAG = -o
INCLUDE =-I../include/
LIBFLAG =
DEBUG = -g
BASE = ..

.PHONY: clean all libez
.PRECIOUS: %/%.o

all: libez

libez: libezstack.o libezlist.o libezsort.o libezsearch.o libezmbs.o

libezstack.o: $(BASE)/include/ez_stack.h
libezlist.o: $(BASE)/include/ez_list.h
libezsort.o: $(BASE)/include/ez_sort.h
libezsearch.o: $(BASE)/include/ez_search.h
libezmbs.o: $(BASE)/include/ez_modbus.h

clean:
	rm ./*.o
