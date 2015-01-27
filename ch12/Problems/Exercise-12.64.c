/*
 * Problem 12.64
 *
 *     Modify our BST implementation (Program 12.7) to support a first-class
 *     symbol-table ADT with client item handles (see Exercises 12.4 and 12.5),
 *     using parallel arrays.  Comppare the performnace of your program with that
 *     of the standard implementation, using one of the drivers in Exercise 12.21 or
 *     Exercise 12.22.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../item.h"

struct table_s {
	unsigned int *keys, *left, *right;
	Item_t **items;
	unsigned int index, maxN, N;
};

/* Keep track of how big the tables table is. */
static unsigned int table_cnt = 0;

static struct table_s **tables;

struct table_s *
table_init(unsigned int size)
{
	uint32_t bytes = 0;
	struct table_s *tbl;

	bytes = sizeof(struct table_s) * size;
	tbl = malloc(bytes);
	if (!tbl) {
		return NULL;
	}

	tbl->left = malloc(bytes);
	if (tbl->left == NULL) {
		free(tbl);
		return NULL;
	}
	memset(tbl->left, 0, bytes);

	tbl->right = malloc(bytes);
	if (tbl->right == NULL) {
		free(tbl->left);
		free(tbl);
		return NULL;
	}
	memset(tbl->right, 0, bytes);

	tbl->items = malloc(bytes);
	if (tbl->items == NULL) {
		free(tbl->left);
		free(tbl->right);
		free(tbl);
		return NULL;
	}
	memset(tbl->items, 0, bytes);

	tbl->maxN = size;
	tbl->N = 0;

	return tbl;
}

void
table_free(struct table_s *tbl)
{
	if (tbl->items) {
		free(tbl->items);
	}

	if (tbl->left) {
		free(tbl->left);
	}

	if (tbl->right) {
		free(tbl->right);
	}

	tbl->maxN = 0;
	tbl->N = 0;
}

/*
 * STinit(unsigned int)
 *
 *     Create a new table/tree, adding it to the set
 *     already in known.
 */
struct table_s *
STinit(unsigned int size)
{
	int table_sz;

	table_sz = sizeof(struct table_s);
	tables = realloc(tables, (table_cnt + 1) * table_sz);
	if (!tables) {
		return NULL;
	}
	tables[table_cnt] = table_init(size);

	if (tables[table_cnt] == NULL) {
		table_free(tables[table_cnt]);
	}
	table_cnt++;

	return tables[table_cnt - 1];
}

/*
 * STclear(struct table_s *)
 *
 *     Remove a tree from the table, free it, and move
 *     the rest of the entries down by 1;
 */
void
STclear(struct table_s *tbl)
{
	int i;

	/* Find the table. If there isn't one then we're done. */
	for (i = 0; i < table_cnt; i++) {
		if (tables[i] == tbl) {
			break;
		}
	}

	if (i != table_cnt) {
		table_free(tables[i]);

		/*
		 * Decrement the table_cnt here so that the for loop will
		 * conclude just short of the end since there is now headroom
		 */
		table_cnt--;
		for (; i < table_cnt; i++) {
			tables[i] = tables[i + 1];
		}
		tables = realloc(tables, table_cnt * sizeof(struct table_s));
	}
}

Item_t *
search(struct table_s *tbl, int ndex, Key_t kval)
{
	Key_t tval;

	tval = key(tbl->items[ndex]);

	if (kval < tval) {
		return search(tbl, tbl->left[ndex], kval);
	} else if (tval < kval) {
		return search(tbl, tbl->right[ndex], kval);
	} else {
		return tbl->items[ndex];
	}

}

Item_t *
STsearch(struct table_s *tbl, Key_t key)
{
	return search(tbl, 0, key);
}

int
insert(struct table_s *tbl, int ndex, Item_t *item)
{
	Key_t v = key(item);
	Key_t t = key(tbl->items[ndex]);

	if (tbl->N == tbl->maxN) {
		return 0;
	}

	if (ndex == 0) {
		tbl->items[tbl->N] = item;
		tbl->N++;
		return tbl->N;
	}

	if (v < t) {
		tbl->left[ndex] = insert(tbl, tbl->left[ndex], item);
	} else if (t < v) {
		tbl->right[ndex] = insert(tbl, tbl->right[ndex], item);
	}

	return ndex;
}

int
STinsert(struct table_s *tbl, Item_t *item)
{
	int link;

	link = insert(tbl, 0, item);

	return link;
}

int
STcount(struct table_s *tbl)
{
	return tbl->N;
}

