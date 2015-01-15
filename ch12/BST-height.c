/*
 * 12.53 (Pp. 510)
 * Write a recursive program that commputes the maximum number of
 * comparisons required by any search in a given BST (the height of the tree).
 *
 * 12.54 (Pp 511)
 * Write a recursive program that computes the average number of comparisons
 * required by a search hit in a given BST (The internal path length of the tree
 * divided by N);
 */


/*
 * Compute the internal path length of the tree.
 */
int
plengthR(BTree *bt, Item_t item, int level)
{
	int x, y;

	if (bt->left) {
		x = plengthR(bt, item, level + 1);
	}
	if (bt->right) {
		y = plengthR(bt, item, level + 1);
	}

	return level + x + y;
}

