#include <stdio.h>
#include "ez.h"
#include "ez_list.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


int array [] = {
1,2,3,4,5,6,7,8,9, 10,
11,12,13, 14,15,16,17,18,19,20,21,22,23};


_list mylist;

int main (argc, argv) 
	int argc;
	char* argv [];
{	
	int i = 0, len = 23;
	_position ch;
	mylist = ez_list_create (); 
	// _element buf = (_element) malloc (sizeof (_element));
	if (NULL == mylist) {
		println ("malloc error!");
		return 0;
	}
	_position pos = mylist;

	// isempty ()
	if (ez_list_empty (mylist))
		println ("is empty!");
	// insert ()
	for (; i < len; i ++) {
		if (pos != NULL &&
				ez_list_insert (mylist, 
					array [i], pos)) {
			printf ("insert %c\n", array [i]);
		} else 
			printf ("insert %c error\n", array [i]);
		pos = (_position) (pos -> next);
	}

	if (ez_list_find (mylist, (int) 20)!= NULL) 
		printf ("find %d \n", 20);
	else 
		printf ("find %d error\n", 20); 


	if ((ch = ez_list_find_pre (mylist, (int) 12)) != NULL) 
		printf ("find_pre %d \n", ch -> val);
	else 
		printf ("find_pre %d error\n", ch -> val); 

	ez_list_del_all (mylist);

	return 0;
}
