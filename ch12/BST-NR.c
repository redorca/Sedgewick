/*
 * Problem 12.52
 *
 *     The nonrecursive insertion procedure in Program 12.9 uses a redundant
 *     comparison to determine which link of p to replace with the new node.
 *     Give an implmentation that uses pointers to links to avoid this compar-
 *     ison.
 */

void STinsert(Item item)
{
	Key v = key(item);
	link **p = &head, *x = *p;

	if (head == NULL) {
		head = NEW(item, NULL, NULL, 1);
		return;
	}

	while (x != NULL) {
		x->N++;
		p = less(v, key(x->item)) ? &x->l : &x->r;
		x = *p;
	}

	x = NEW(item, NULL, NULL, 1);
	*p = x;
}


