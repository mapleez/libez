# author : ez
# date : 2015/5/18
# describe : compile the stack structure module


CC = gcc
CFLAG = 
OBJFLAG = -o
INCLUDE = -I../include/
BIN = ../src/libezstack.o ../src/libezlist.o
DEBUG = -g

all: postfix 

postfix: postfix.c 
	$(CC) $(BIN) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $^ $(DEBUG)

clear: 
	@echo "nothing to be deleted!";

