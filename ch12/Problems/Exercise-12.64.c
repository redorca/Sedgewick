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

static struct table_s **tables;

struct table_s *
table_init(unsigned int size)
{
	uint32_t bytes;
	struct table_s *tbl;

	tbl = malloc(sizeof(struct table_s) * size);
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

struct table_s **
STinit(unsigned int count, unsigned int size)
{
	int i, j;

	tables = malloc(sizeof(struct  table_s) * count);
	if (!tables) {
		return NULL;
	}

	for (i = 0; i < count; i++) {
		tables[i] = table_init(size);
		if (j < 0) {
			for (j = 0; j < 1; j++) {
				table_free(tables[j]);
			}
			j = -1;
			break;
		}
	}

	if (j < 0) {
		free(tables);
		return  NULL;
	}

	return tables;
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
	int xval;

	if (tbl->N = tbl->maxN) {
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

void
STinsert(struct table_s *tbl, Item_t *item)
{
	int link;

	link = insert(tbl, 0, item);
}

int
STcount(struct table_s *tbl)
{
	return tbl->N;
}

