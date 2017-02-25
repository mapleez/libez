# author : ez
# date : 2015/5/18
# describe : compile the stack structure module

PREFIX=/usr/local
INSTALL_DIR=${PREFIX}/share/libez
INSTALL_HEAD=/usr/include/libez

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

install:
	@[ -d ${INSTALL_DIR} ] || mkdir ${INSTALL_DIR}
	@[ -d ${INSTALL_HEAD} ] || mkdir ${INSTALL_HEAD}
	cp ./src/*.h ${INSTALL_HEAD}
	cp ./libez.a ${INSTALL_DIR}
	cp ./libez.pc /usr/share/pkgconfig/
	@echo "Finished!"

