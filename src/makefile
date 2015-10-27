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

libez: libezstack.o libezlist.o libezsort.o libezsearch.o libezmbs.o

libezsearch.o: ez_search.c
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezstack.o: ez_stack.c 	
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezlist.o: ez_list.c 
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezsort.o: ez_sort.c
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

libezmbs.o: ez_modbus.c
	$(CC) $(LIBFLAG) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)

clean: 
	@rm -f ./libezstack.o && echo "delete libezstack.o"; \
	 rm -f ./libezlist.o && echo "delete libezlist.o"; \
	 rm -f ./libezsort.o && echo "delete libezsort.o"; \
	 rm -f ./libezsearch.o && echo "delete libezsearch.o"; \
	 rm -f ./libezmbs.o && echo "delete libezmbs.o"; 
