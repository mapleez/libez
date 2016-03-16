#ifndef _EZ_BTREE_H_
#	define _EZ_BTREE_H_

typedef struct ez_btree 
	*pez_btree, ez_btree;

typedef struct ez_btree {
	pez_btree _left;
	pez_btree _right;
	void* _data;
} ez_btree_node,
	*pez_btree_node;

typedef void (*node_access_func) (pez_btree);

#	define SIZE_BTREENODE (sizeof (ez_btree))

extern pez_btree ez_btree_create (void*);
extern void ez_btree_dispose (pez_btree);
extern pez_btree ez_btree_insert (pez_btree, void*);
extern pez_btree ez_btree_find (pez_btree, void*);
extern pez_btree ez_btree_findmax (pez_btree);
extern pez_btree ez_btree_findmin (pez_btree);
extern int ez_btree_delete (pez_btree*, void*);

extern void ez_btree_preorder (pez_btree, node_access_func);
extern void ez_btree_inorder (pez_btree, node_access_func);
extern void ez_btree_postorder (pez_btree, node_access_func);


#endif // ~ _EZ_BTREE_H_
