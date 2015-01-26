/*
 * Program 12.15:  Deletion of a node with a given key in a BST
 *
 * This implementation of the delete operation removes the first node with
 * key v encountered in the BST.  Working top down, it makes recursive
 * calls for the appropriate subtree until the node to be deleted is at the
 * root.  Then, it replaces the node with the result of combining its two
 * subtrees -- the smallest node in the right subtree becomes the root, then
 * its left link is set to point to the left subtree.
 */

link *
joinLR(link *a, link *b)
{
	if (b == z) return a;

	b = partR(b, 0);
	b->l = a

	return b;
}

link *
deleteR(link *h, Key v)
{
	link *x;
	Key t = key(h->item);

	if (h == z) return z;
	if (less(v, t)) {
		h->l = deleteR(h->l, v);
	}
	if (less(t, v)) {
		h->r = deleteR(h->r, v);
	}

	if (eq(v, t)) {
		x = h;
		h = joinLR(h->l, h->r);
		free(x);
	}

	return h;
}

void
STdelete(Key v)
{
	head = deleteR(head, v);
}

