# author : ez
# date : 2015/5/18
# describe : compile the stack structure module


CC =gcc
CFLAG =-c
OBJFLAG =-o
INCLUDE =-I../include/
LIBFLAG =
DEBUG = -g


all: libez

libez: libezstack.o libezlist.o libezsort.o


libezstack.o: _stack.c 	
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezlist.o: list.c 
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezsort.o: ez_sort.c
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)


clear: 
	@rm -f ./libezstack.o && echo "delete libezstack.o"; \
	 rm -f ./libezlist.o && echo "delete libezlist.o"; \
	 rm -f ./libezsort.o && echo "delete libezsort.o";
