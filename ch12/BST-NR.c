

static link *head;


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



/*
 * Problem 12.73
 *     Immplement a nonrecursive BST root insertion function (see Program 12.12).
 */
void
STinsert(Item_t *item)
{
	Key_t v = key(item);
	link *p = head;
	link *x = p;

	if (head == NULL) {
		head = NEW(item, NULL, NULL, 1);
		return;
	}

	/*
	 * Find the insertion point:
	 */
	x = head;
	while (x != NULL) {
		x->N++;
		p = x;
		x = less(v, key(x->item)) ? x->l : x->r;
	}

	x = NEW(item, NULL, NULL, 1);
	if (less(v, key(p->item))) {
		p->l = x;
	} else {
		p->r = x;
	}

	/*
	 * Use rotation to move the node to the root.
	 */
	while (!STACKempty()) {
		x = STACKpop();
	}

}


/*
 * Problem 12.75
 *        Implment a non-recursive BST select function (see Program 12.13).
 */
Item_t *
STselect(link *h, int k)
{
	int t;

	if (h == z) {
		return NULLitem;
	}

	while (h->l) {
		t = (h->l == NULL) ? 0 : h->l->N;
		if (t > k) {
			h = h->l;
			continue;
		}
		if (t < k) {
			k = k - t - 1;
			h = h->r;
			continue;
		}
		break;
	}

	if (h == NULLitem) {
		return NULLitem;
	}

	return h->item;
}

