/*
 *
 * Program 12.9  Insertion in BSTs (nonrecursive)
 *
 *     Inserting an item into a BST is equivalent to doing an unsuccessful search
 *     for it, then attaching a new node for the item in place of the null link
 *     where the search terminates.  Attaching the new node requires that we keep
 *     track of the parent p of x as we proceed down the tree.  When we reach the
 *     bottom of the tree, p points to the node whose link we must change to point
 *     to the new node inserted.
 */



void STinsert(Item item)
{
	Key v = key(item);
	link p = head, x = p;

	if (head == NULL) {
		head = NEW(item, NULL, NULL, 1);
		return;
	}

	while (x != NULL) {
		p = x;
		x->N++;
		x = less(v, key(x->item)) ? x->l : x->;
	}

	x = NEW(item, NULL, NULL,, 1);
	if (less(v, key(p->item))) {
		p->l = x;
	} else {
		p->r = x;
	}
}
