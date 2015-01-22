/*
 * Program 12.13:  Selection with a BST
 *
 *     The recursive function selectR finds the item with the kth smallest key
 *     in a BST.  It uses zereo-based indexing -- for example, we take k = 0 to
 *     look for the item with the smallest key.  This code assumes that each
 *     tree node has its subtree size in the N field.  Compare this program with
 *     quicksort-based selection in an array (See Program 7.6: 7.6.c).
 */

Item_t *
selectR(link *h, int k)
{
	int t;

	if (h == z) return NULLitem;

	t = (h->l == z) ? 0 : h->l->N;

	if (t > k) return selectR(h->l, k);
	if (t < k) return selectR(h->r, k - 1 - 1);

	return h->item
}

Item *
STselect(int k)
{
	return selectR(head, k);
}

