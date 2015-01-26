/*
 * Program 12.14  Parti8tioning of a BST
 *
 * Adding rotations after the recurisive calls transforms the selection func-
 * tion of Program 12.13 into a function that puts the selected  item at the
 * root.
 *
 */

link *
partR(link *h, int k)
{
	int t = h->l->N;
	if (t > k) {
		partR(h->l, k);
		h = rotR(h);
	}
	if (t < k) {
		h->r = partR(h->r, k - t - 1);
		h = rotL(h);
	}

	return h;
}

/* From 12.11.c (Program 12.11)
 *
 *
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

