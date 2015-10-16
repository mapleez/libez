# author : ez
# date : 2015/5/18
# describe : compile the stack structure module

SUBDIR = src use.d 
MAKE = make

subsystem:
	@for subdir in $(SUBDIR); \
		do \
			echo "make in $$subdir";	\
			(cd $$subdir && $(MAKE)) || exit 1; \
		done

clear:
	@for subdir in $(SUBDIR);	\
		do \
			(cd $$subdir && $(MAKE) clear) || exit 1;	\
		done

#CC=gcc
#CFLAG=-c
#OBJFLAG=-o
#INCLUDE=-I./include/
#SRC=./src
#DEBUG=-g
#
#
#all: libez
#
#libez: libezstack.o libezlist.o
#
#libezstack.o: $(SRC)/ez_stack.c _stack.h
#	$(CC) $(INCLUDE) $(SRC) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)
#
#libezlist.o: _list.c _list.h
#	$(CC) $(INCLUDE) $(SRC) $(OBJFLAG) $@ $(CFLAG) $(SRC)$< $(DEBUG)


# unit: libezstack.o main.o
# 	$(CC) $(INCLUDE) $(OBJFLAG) $@ libezstack.o main.o $(DEBUG)

# main.o: unit.c
#	$(CC) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $< $(DEBUG)


# clear: 
#	@rm -f ./libezstack.o && echo "clear libezstack.o"; \
#	 rm -f ./main.o && echo "clear main.o"

