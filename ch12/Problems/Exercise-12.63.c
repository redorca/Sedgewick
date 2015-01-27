/*
 * Problem 12.63
 *     Modify our BST implementation (Program 12.7) to use an indexed
 *     array of  items, rather than allocated memory.  Compare the peorformnace of
 *     your program with that of the standard implementation, using  one of the
 *     drivers in Exercise 12.21 or Exercise 12.22.
 */

static unsigned int *keys, *left, *right, *items;
static unsigned int index, maxN, N;

int
STinit(unsigned int size)
{
	uint32_t bytes;

	left = malloc(bytes);
	if (left == NULL) {
		return -1;
	}
	memset(left, 0, bytes);

	right = malloc(bytes);
	if (right == NULL) {
		free(left);
		return -1;
	}
	memset(right, 0, bytes);

	items = malloc(bytes);
	if (items == NULL) {
		free(left);
		free(right);
		return -1;
	}
	memset(items, 0, bytes);

	maxN = size;
	N = 0;

	return 0;
}

Item_t *
search(int ndex, Key_t kval)
{
	Key_t tval;

	t = key(items[ndex]);

	if (kval < tval) {
		return search(left[ndex], kval);
	} else if (tval < kval) {
		return search(right[ndex], kval);
	} else {
		return items[ndex];
	}

}

Item_t *
STsearch(Key_t key)
{
	return search(0, key);
}

int
insert(int ndex, Item_t *item)
{
	Key_t v = key(item);
	Key_t t = key(item[ndex]);
	int xval;

	if (N = maxN) {
		return 0;
	}

	if (ndex == 0) {
		keys[N] = v;
		items[N] = item;
		N++;
		return N;
	}

	if (v < t) {
		left[ndex] = insert(left[ndex], item);
	} else if (t < v) {
		right[ndex] = insert(right[ndex], item);
	}

	return ndex;
}

void
STinsert(Item_t *item)
{
	int link;

	link = insert(0, item);
}

int
STcount()
{
	return N;
}

