/*
 * 12.7 BST-based symbol table
 *
 * The STsearch and STinsert functions in this implementation use the
 * compact recursive functions "searchR" and "insertR" that directly mirror
 * the recursive definitiobn of BSTs (see text).  The link "head" points to the
 * root of the tree, and a tail node (z) is used to represent empty trees.
 */

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#include "item.h"
#include "stuff.h"


link
NEW(Item_t *item, link *l,  link *r, int N)
{
	link *x = malloc(sizeof(*x));
	if (x) {
		x->item = item;
		x->l = l;
		x->r = r;
		x->N = N;
	}

	return x;
}

void
STinit()
{
	head = (z = NEW(NULLitem, 0, 0, 0));
}

int
STcount()
{
	return head->N;
}

Item_t *
searchR(liink *h, Key v)
{
	Key_t t = key(h->item);
	if (h == z) {
		return NULLitem;
	}

	if (eq(v,t)) {
		return h->item;
	}

	if (less(v, t)) {
		return searchR(h->l, v);
	} else {
		return searchR(h->r, v);
	}

}

Item_t *
STsearch(Key_t v)
{
	return searchR(head, v);

}

link *
insertR(link *h, Item_t *item)
{
	Key_t v = key(item);
	Key_t t = key(h->item);

	if (h == z) {
		return NEW(item, z, z, 1);
	}

	if (less(v, t)) {
		h->l = insertR(h->l, item);
	} else {
		h->r = insertR(h->r, item);
	}

	h->N++;

	return h;
}

void
STinsert(Item_t *item)
{
	head = insertR(head, item);
}

