# author : ez
# date : 2015/5/18
# describe : compile the stack structure module


CC = gcc
INCLUDE = -I../include
BIN = ../libez.a
DEBUG = -g
CFLAGS = $(INCLUDE) $(DEBUG)
EXEFILES = postfix dfs mbs

.PHONY: all clean

all: $(EXEFILES)

$(EXEFILES): $(BIN)

# postfix: postfix.c 
# 	$(CC) $(BIN) $(INCLUDE) $(OBJFLAG) $@ $(CFLAG) $^ $(DEBUG)

clean: 
	rm postfix dfs

