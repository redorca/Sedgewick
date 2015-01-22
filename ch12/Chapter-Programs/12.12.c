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

void
STinsert(Item_t *item)
{
	head = insertT(head, item);
}


