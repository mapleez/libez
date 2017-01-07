#	author : ez
# date : 2016/2/8
# describe : compile my own server program.

CC = gcc
INCLUDE = -I../../src
BIN = ../../libez.a
DEBUG = -g
CFLAGS = $(INCLUDE) $(DEBUG)
EXEFILES = ezsrv

.PHONY: all clean

all: $(EXEFILES)

$(EXEFILES):	$(BIN)

clean:
	rm ezsrv
