# author : ez
# date : 2015/5/18
# describe : compile all the modules and arch them

BASE = ..
INCLUDE = $(BASE)/include

CFLAGS = -g -I$(INCLUDE)
CC = gcc
OBJFLAG = -o
LIBHEAD = $(INCLUDE)/ez.h
CXXFLAGS = $(CFLAGS)
ARFLAGS = rs

.PHONY: all clean
# .PRECIOUS: %/%.o
.PRECIOUS: %.o

all: $(BASE)/libez.a

$(BASE)/libez.a: ez_stack.o ez_list.o ez_sort.o ez_search.o ez_modbus.o
	@echo "Updating library..."
	$(AR) $(ARFLAGS) $@ $^

ez_stack.o: $(INCLUDE)/ez_stack.h $(LIBHEAD)
ez_list.o: $(INCLUDE)/ez_list.h $(LIBHEAD)
ez_sort.o: $(INCLUDE)/ez_sort.h $(LIBHEAD)
ez_search.o: $(INCLUDE)/ez_search.h $(LIBHEAD)
ez_modbus.o: $(INCLUDE)/ez_modbus.h $(LIBHEAD)

clean:
	rm ./*.o
	rm ../libez.a
