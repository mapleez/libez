/*
 * author : ez
 * date : 2015/4/20
 * describe : Depth first searching
*/
#include "ez_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


#	define vertex_num	8
typedef _list vertex;
typedef vertex* graphic;

#	define println(___s)  printf ("%s\n", ___s)

#	define line_number(___a) ((___a) [0])
// the first field stored the length of array [i]
int array [8][5] = {
	{3, 1, 2, 3},
	{3, 2, 4, 1},
	{4, 3, 1, 5, 6},
	{3, 4, 2, 8},
	{3, 5, 3, 7},
	{3, 6, 3, 7},
	{4, 7, 5, 6, 8},
	{3, 8, 4, 7}
}; // max number 8


// global varibles
bool* visited;
graphic grph;

// global functions;
void create_graphic ();
void dfs (int);
_list each_edge (int*, int);


// depth first search
// _idx : the vertex to start visit
void dfs (int _idx) {
	_position tmp = grph [_idx];
	// visit
	printf ("visited %d\n", _idx + 1);
	visited [_idx] = true;

	tmp = tmp -> next;
	while (tmp != NULL) {
		if (! visited [tmp -> val])
			dfs (tmp -> val);
		tmp = tmp -> next;
	}
}


void create_graphic () {
	// init 8 vertex
	int i = 0;
	// list array
	grph = (graphic) malloc (
			sizeof (vertex) * vertex_num);
	visited = (bool*) malloc (sizeof (bool) * vertex_num);
	// cannot use memset ()
	for (; i < vertex_num; i ++) {
		visited [i] = false;
		//	vertex tmp = (vertex) malloc (sizeof 
		//			(struct _node));
		//	grph [i] = tmp;
		//	grph [i] -> next = NULL;
		grph [i] = each_edge (array [i], 
				line_number (array [i]));
		//if (tmp == NULL) {
		//	printf ("");
		//}
		// malloc (sizeof (struct _node));
		show (grph [i]);
		println ("");
	}

	// memset (visited, 0, sizeof (bool) * vertex_num);
	// return grph; // no usage
}

_list each_edge (int* _idxs, int _num) {
	_list tmp = (_list) 
		malloc (sizeof (struct _node)); // list header
	_position p = tmp;
	int i = 2;
	p -> val = (uint32_t) (_idxs [1] - 1);
	p -> next = NULL;

	for (; i <= _num; i ++) {
		p -> next = (_position) 
			malloc (sizeof (struct _node));
		p = p -> next;
		// current node
		p -> val = (uint32_t) (_idxs [i] - 1);
		p -> next = NULL;
	}

	return tmp;
}


int main (argc, argv) 
	int argc;
	char* argv [];
{
	create_graphic ();
	dfs (0);
	return 0;
}


