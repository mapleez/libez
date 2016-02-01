#include "ez.h"

int main (int argc, char* argv []) {

	{ // test endian converts.
		uint32_t _32 = 0x01020304;
		uint64_t _64 = 0x0102030405060708L;

		_32 = tobigend32 (_32);
		_32 = tobigend32 (0x01020304);

		_64 = tobigend64 (_64);
		_64 = tobigend64 (0x0102030405060708L);
		println ("finished !!!");
	}
	return 0;
}
