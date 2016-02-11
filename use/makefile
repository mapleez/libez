# author : ez
# date : 2015/5/18
# describe : compile the stack structure module


CC = gcc
INCLUDE = -I../include
BIN = ../libez.a
DEBUG = -g
CFLAGS = $(INCLUDE) $(DEBUG)
EXEFILES = postfix dfs mbs web ezcli

.PHONY: all clean

all: $(EXEFILES) ezsrv

$(EXEFILES): $(BIN)

ezsrv:
	$(MAKE) -C ezserver/ all

# postfix: postfix.c 
# 	$(CC) $(BIN) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $^ $(DEBUG)

clean: 
	rm $(EXEFILES)
	$(MAKE) -C ezserver/ clean

