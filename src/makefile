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

$(BASE)/libez.a: ez_stack.o ez_list.o ez_sort.o ez_search.o ez_modbus.o ez_queue.o ez_endpoint.o ez_channel.o ez_socktools.o ez_bytes.o ez_log.o ez_event.o ez_select.o ez_dlinklist.o ez_gstack.o ez_btree.o ez_hash.o ez_heap.o
	@echo "Updating library..."
	$(AR) $(ARFLAGS) $@ $^

ez_stack.o: $(INCLUDE)/ez_stack.h $(LIBHEAD)
ez_gstack.o: $(INCLUDE)/ez_gstack.h $(LIBHEAD)
ez_list.o: $(INCLUDE)/ez_list.h $(LIBHEAD)
ez_sort.o: $(INCLUDE)/ez_sort.h $(LIBHEAD)
ez_search.o: $(INCLUDE)/ez_search.h $(LIBHEAD)
ez_modbus.o: $(INCLUDE)/ez_modbus.h $(LIBHEAD)
ez_queue.o: $(INCLUDE)/ez_queue.h $(LIBHEAD)
ez_channel.o: $(INCLUDE)/internet/ez_channel.h $(LIBHEAD)
ez_endpoint.o: $(INCLUDE)/internet/ez_endpoint.h $(LIBHEAD)
ez_socktools.o: $(INCLUDE)/internet/ez_socktools.h $(LIBHEAD)
ez_bytes.o: $(INCLUDE)/ez_bytes.h $(LIBHEAD)
ez_log.o: $(INCLUDE)/ez_log.h $(LIBHEAD)
ez_select.o: $(LIBHEAD)
ez_event.o: $(INCLUDE)/ez_event.h $(LIBHEAD) ez_select.o
ez_dlinklist.o: $(INCLUDE)/ez_dlinklist.h $(LIBHEAD)
ez_btree.o: $(INCLUDE)/ez_btree.h $(LIBHEAD)
ez_btree.o: $(INCLUDE)/ez_hash.h $(LIBHEAD)
ez_heap.o: $(INCLUDE)/ez_heap.h $(LIBHEAD)

clean:
	rm ./*.o
	rm ../libez.a

