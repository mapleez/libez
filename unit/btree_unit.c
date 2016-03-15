#include "ez_btree.h"
#include "ez.h"
#include <stdio.h>

int __datas [] = {
	1, 3, 97, 7845, 751,
	172, 32, 45, 735, 99, 123,
	93, 46, 65, 11, 3234, 8, 20, 3
};

int __default_match__ (void* _a, void* _b) {
	long a = (long) _a;
	long b = (long) _b;
	int res = a > b ? BIGGER : a == b ? EQUAL : SMALLER;
	return res;
}


int main (int argc, char* argv []) {

//	{
//		int res = -2;
//		res = __default_match ((void*) 100, (void*) 200);
//		res = __default_match ((void*) 200, (void*) 200);
//		res = __default_match ((void*) 400, (void*) 200);
//		printf ("%d\n", res);
//	}

	{
		pez_btree res = ez_btree_create (NULL),
							max = NULL, min = NULL;
		int count = sizeof (__datas) / sizeof (int), 
				i = 0;
		for (; i < count; i ++) {
			int elm = __datas [i];
			printf ("Inserting element : %d...", elm);
			pez_btree insertion = ez_btree_insert (res, 
					(void*) (long) (__datas [i]));
			if (insertion && (long) insertion -> _data == (long) elm)
				printf ("Done!\n");
			else
				printf ("Err!\n");
		}

		if ((max = ez_btree_findmax (res)))
			printf ("Max element : %d\n", (long) max -> _data);

		if ((min = ez_btree_findmin (res)))
			printf ("Min element : %d\n", (long) min -> _data);

		println ("Preorder : \n");
		ez_btree_preorder (res, NULL);

		println ("\nInorder : \n");
		ez_btree_inorder (res, NULL);

		println ("\npostorder : \n");
		ez_btree_postorder (res, NULL);

		ez_btree_dispose (res);
	}
	return 0;
}


