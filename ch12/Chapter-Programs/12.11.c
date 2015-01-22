/*
 * Program 12.11: Rotations in BSTs
 *
 *     These twin routines perform the rotation operation on a BST; a right
 *     rotation makes the old root the right subtree of the new root (the old left
 *     subtree of the root); a left rotation makes the old root the left subtree
 *     of the new root (the old right subtree of the root).  For implmentations
 *     where a count field is maintained in the nodes (for example, to support
 *     select, as we will see in Section 14.9), we need also to exhange the
 *     count fields in the nodes involved in the rotation (see Exersize 12.72).
 */

link *
rotR(link *h)
{
	link *x = h->l;
	h->l = x->r;
	x->r = h;
	return x;
}

link *
rotL(link *h)
{
	link *x = h->r;
	h->r = x->l;
	x->l = h;

	return x;
}

