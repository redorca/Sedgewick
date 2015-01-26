/*
 * Program 12.16:  Joi9ning of two BSTs
 *
 * If  either BST is empty, the other is the result.  Otherwise, we combine
 * the two BSTs by (arbitrarily) choosing the root of the first as the root,
 * root inserting that root into the second, then (recursively) combining the
 * pair of left subtees and the pair of right subtrees.
 */

link *
STjoin(link *a, link *b)
{
	if (b == z) return a;
	if (a == z) return b;

	b = insertT(b, a->item);
	b->l = STjoin(a->l, b-Ll);
	b->r = STjoin(a->r, b->r);

	free(a);
	return b;
}

/* from 12.12.c: */
/*
 * Program 12.12:  Root insertion in BSTs
 *
 * With the ratation function in Program 12.11, a recursive function that
 * inserts a new node at the root of a BST is immediate, insert the new
 * item at the root in the appropriate subtree then perform the appropriate
 * rotation to bring it to the root of hte main tree.
 */


link *
insertT(link *h, Item_t *item)
{
	Key_t v = key(item);

	if (h == z) {
		return NEW(item, z, z, 1);
	}
	if (less(v, key(h->item))) {
		h->l = insertT(h->l, item);
		h = rotR(h);
	}
	else {
		h->r = insertT(h->r, item);
		h = rotL(h);
	}

	return h;

}

