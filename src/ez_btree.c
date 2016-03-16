#include <stdlib.h>
#include "ez_btree.h"
#include "ez.h"

static int __default_match (void*, void*);
static void* __default_copy (pez_btree, void*);
static pez_btree __ez_btree_delete (pez_btree, void*);

static int __default_match (void* _a, void* _b) {
	long a = (long) _a;
	long b = (long) _b;
	return a > b ? BIGGER : 
		a == b ? EQUAL : SMALLER;
}

static void* __default_copy (pez_btree _tree, void* _data) {
	intptr_t a = (intptr_t) _data;
	intptr_t b = (intptr_t) _tree -> _data;
	BASIC_SWAP (a, b);
}

static 
pez_btree __ez_btree_delete (pez_btree _tree, void* _data) {
	int cmp = -2; // an invalid comparing return-value.
	pez_btree tmp = NULL;
	if (! _tree) return NULL; // not found
	cmp = __default_match (_tree -> _data, _data);
	if (cmp == BIGGER) { // go left
		_tree -> _left = __ez_btree_delete (_tree -> _left, _data);
	} else if (cmp == SMALLER) { // go right
		_tree -> _right = __ez_btree_delete (_tree -> _right, _data);
	} else if (_tree -> _left && _tree -> _right) {
		/*
		 * We handle this node that has 2 children in the way,
		 * which we find the minumim element from it's right child
		 * and recove the value to current node. Then find the minumim
		 * node and delete it, which must be a leaf child.
		*/
		tmp = ez_btree_findmin (_tree -> _right);
		_tree -> _data = tmp -> _data;
		_tree -> _right = __ez_btree_delete 
			(/*_tree -> _right*/_tree -> _right, _tree -> _data);
	} else { // found and had one or 0 child.
		tmp = _tree;
		if (_tree -> _left == NULL)
			_tree = _tree -> _right;
		else if (_tree -> _right == NULL)
			_tree = _tree -> _left;
		free (tmp);
	}
	return _tree;
}

static void __default_traversal (pez_btree _tree) {
	printf ("%i ", (long) _tree -> _data);
}

pez_btree ez_btree_create (void* _data) {
	pez_btree tree = (pez_btree) malloc (SIZE_BTREENODE);
	if (! tree) return NULL;
	tree -> _left = tree -> _right = NULL;
	tree -> _data = _data;
	return tree;
}


void ez_btree_dispose (pez_btree _tree) {
	if (! _tree) return;
	ez_btree_dispose (_tree -> _left);
	ez_btree_dispose (_tree -> _right);
	// debug
	printf ("Delete element : %i\n", (long) _tree -> _data);
	free (_tree);
}

pez_btree ez_btree_insert (pez_btree _tree, void* _data) {
	int cmp = 0;
	pez_btree_node res = NULL;
	if (! _tree) return NULL;
	if (! _tree -> _data) {
		_tree -> _data = _data;
		return _tree;
	}
	cmp = __default_match (_tree -> _data, _data);
	if (cmp == BIGGER) {
		// bigger
		if (_tree -> _left)
			return ez_btree_insert (_tree -> _left, _data);
		res = (pez_btree_node) malloc (SIZE_BTREENODE);
		if (res) res -> _data = _data;
		_tree -> _left = res;
		return res;
	} else if (cmp == EQUAL) {
		// equal... *o*
		println ("What should I do if both elements equal!?");
		return NULL;
	} else if (cmp == SMALLER) {
		// smaller
		if (_tree -> _right)
			return ez_btree_insert (_tree -> _right, _data);
		res = (pez_btree_node) malloc (SIZE_BTREENODE);
		if (res) res -> _data = _data;
		_tree -> _right = res;
		return res;
	} else {
		// ERROR.
		println ("Eh~ error.");
		return NULL;
	}
}

pez_btree ez_btree_find (pez_btree _tree, void* _data) {
	int cmp = __default_match (_tree -> _data, _data);
	if (cmp == BIGGER) {
		// bigger
		if (_tree -> _left) 
			return ez_btree_find (_tree -> _left, _data);
		return NULL;
	} else if (cmp == EQUAL) {
		// equal... *o*
		return _tree;
	} else if (cmp == SMALLER) {
		// smaller
		if (_tree -> _right)
			return ez_btree_find (_tree -> _right, _data);
		return NULL;
	} else {
		// ERROR.
		println ("Eh~ error.");
		return NULL;
	}
}

pez_btree 
ez_btree_findmax (pez_btree _tree) {
	if (! _tree)
		return NULL;
	if (_tree -> _right)
		return ez_btree_findmax (_tree -> _right);
	return _tree;
}

pez_btree ez_btree_findmin (pez_btree _tree) {
	if (! _tree)
		return NULL;
	if (_tree -> _left)
		return ez_btree_findmin (_tree -> _left);
	return _tree;
}

int ez_btree_delete (pez_btree* _tree, void* _data) {
	*_tree = __ez_btree_delete (*_tree, _data);
	return 1;
}

void ez_btree_preorder (pez_btree _tree, node_access_func _func) {
	node_access_func f = _func ? _func : __default_traversal;
	if (! _tree) return;
	// traversal
	f (_tree);
	ez_btree_preorder (_tree -> _left, f);
	ez_btree_preorder (_tree -> _right, f);
}

void 
ez_btree_inorder (pez_btree _tree, node_access_func _func) {
	node_access_func f = _func ? _func : __default_traversal;
	if (! _tree) return;
	// traversal
	ez_btree_inorder (_tree -> _left, f);
	f (_tree);
	ez_btree_inorder (_tree -> _right, f);
}

void ez_btree_postorder (pez_btree _tree, node_access_func _func) {
	node_access_func f = _func ? _func : __default_traversal;
	if (! _tree) return;
	// traversal
	ez_btree_postorder (_tree -> _left, f);
	ez_btree_postorder (_tree -> _right, f);
	f (_tree);
}


