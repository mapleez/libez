# author : ez
# date : 2015/5/18
# describe : compile the stack structure module

.PHONY: all lib unit use clean

all: lib unit use

lib:
	$(MAKE) -C src/ all

unit:
	$(MAKE) -C unit/ all

use:
	$(MAKE) -C use/ all

clean:
	rm libez.a
	$(MAKE) -C src/ clean
	$(MAKE) -C unit/ clean
	$(MAKE) -C use/ clean

