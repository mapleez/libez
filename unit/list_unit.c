#include <stdio.h>
#include "ez.h"
#include "list.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>



char* array = "typdef string stdilb"
			  "unit.c share bin bookmarks"
			  "extern void del list element first";


_list mylist;

int main (argc, argv) 
	int argc;
	char* argv [];
{	
	int i = 0, len = strlen (array) + 1;
	_position ch;
	mylist = create_list (); 
	// _element buf = (_element) malloc (sizeof (_element));
	if (NULL == mylist) {
		println ("malloc error!");
		return 0;
	}
	_position pos = mylist;

	// isempty ()
	if (empty (mylist))
		println ("is empty!");
	// insert ()
	for (; i < len; i ++) {
		if (pos != NULL &&
				insert (mylist, 
					array [i], pos)) {
			printf ("insert %c\n", array [i]);
		} else 
			printf ("insert %c error\n", array [i]);
		pos = (_position) (pos -> next);
	}

	if (find (mylist, (int) 'x') != NULL) 
		printf ("find %c \n", 'x');
	else 
		printf ("find %c error\n", 'x'); 


	if ((ch = find_pre (mylist, (int) 'x')) != NULL) 
		printf ("find_pre %c \n", ch -> val);
	else 
		println ("find_pre error\n"); 

	del_all (mylist);

	return 0;
}
