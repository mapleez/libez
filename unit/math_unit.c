#include "ez.h"
#include "ez_math.h"

int cmp (const void* _a, const void* _b) {
	long int a = (long int) _a;
	long int b = (long int) _b;
	return (a > b ? BIGGER : SMALLER);
}

int _cmp (int _a, int _b) {
	int a =  _a;
	int b =  _b;
	return (a > b ? BIGGER : SMALLER);
}

int array [] = {
	3, 9, 8, 7, 2,
	6, 93, 878, 21,
	38, 100, 99
};

// implicit type
int __ez_array_max (int* _arr, int _num, int (*_func) (int, int)) {
	_ez_array_max (int, _arr, _num, _func);
	// int max = -1;
	// int i = 0;
	// if (! _arr || ! _func) return -1;
	// max = _arr [i ++];
	// for (; i < _num; ++ i)
	// 	if (_func (max, _arr [i]) == SMALLER) 
	// 		max = _arr [i];
	// return max;
}



int main (int argc, char* argv []) {
	void* res = NULL;
	// int res = 0;
	// ez_moronic_cowmpouter (387, 8);
	res = __ez_array_max (array, 
		sizeof (array) / sizeof (int), cmp);

	printf ("%d\n", (int) res);
	return 0;
}

