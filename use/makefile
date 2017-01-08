# author : ez
# date : 2015/5/18
# describe : compile the stack structure module


CC = gcc
INCLUDE = -I../src/
BIN = ../libez.a
DEBUG = -g
CFLAGS = $(INCLUDE) $(DEBUG)
EXEFILES = mbs web ezcli daemonsrv

.PHONY: all clean

all: $(EXEFILES) ezsrv

$(EXEFILES): $(BIN)

ezsrv:
	$(MAKE) -C ezserver/ all

clean: 
	rm $(EXEFILES)
	$(MAKE) -C ezserver/ clean

