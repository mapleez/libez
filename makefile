# author : ez
# date : 2015/5/18
# describe : compile the stack structure module

lib:
	$(MAKE) -C src/ all

clean:
	$(MAKE) -C src/ clean


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

