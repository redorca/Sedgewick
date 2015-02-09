/*
 * Problem 12.64
 *
 *     Modify our BST implementation (Program 12.7) to support a first-class
 *     symbol-table ADT with client item handles (see Exercises 12.4 and 12.5),
 *     using parallel arrays.  Comppare the performnace of your program with that
 *     of the standard implementation, using one of the drivers in Exercise 12.21 or
 *     Exercise 12.22.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../item.h"

struct table_s {
	unsigned int *keys, *left, *right;
	Item_t **items;
	unsigned int index, maxN, N;
};

/* Keep track of how big the tables table is. */
static unsigned int table_cnt = 0;

static struct table_s **tables;
int
index_check(int tblindex)
{

	if (tblindex >= table_cnt) {
		printf("=== tblindex is too great: %d :: %d\n", tblindex, table_cnt);
		return -1;
	}
	if (tables[tblindex] == NULL) {
		printf("=== There is no table for table %d.\n", tblindex);
		return -1;
	}

	return 0;
}

struct table_s *
table_init(int size)
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
int
STinit(unsigned int size)
{
	int table_sz;

	table_sz = sizeof(struct table_s);
	tables = realloc(tables, (table_cnt + 1) * table_sz);
	if (!tables) {
		printf("=== No tables allocated.\n");
		return -1;
	}
	tables[table_cnt] = table_init(size);

	if (tables[table_cnt] == NULL) {
		printf("Failed to init a table.\n");
		table_free(tables[table_cnt]);
	}
	table_cnt++;

	return table_cnt - 1;
}

/*
 * STclear(struct table_s *)
 *
 *     Remove a tree from the table, free it, and move
 *     the rest of the entries down by 1;
 */
void
STclear(int tblindex)
{
	int i;

	if (index_check(tblindex) < 0) {
		return;
	}

	table_free(tables[tblindex]);

	table_cnt--;
	for (i = tblindex; i < table_cnt; i++) {
		tables[i] = tables[i + 1];
	}
	tables = realloc(tables, table_cnt * sizeof(struct table_s));
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
STsearch(int tblindex, Key_t key)
{
	if (index_check(tblindex) < 0) {
		return  NULL;
	}

	return search(tables[tblindex], 0, key);
}

int
insert(struct  table_s *tbl, int ndex, Item_t *item)
{
	Key_t v = key(item);
	Key_t t;

	if (tbl->N >= tbl->maxN) {
		printf("=== Index too large: %d versus %d\n", tbl->N, tbl->maxN);
		return -1;
	}

	if (tbl->items[ndex] == 0) {
		tbl->items[tbl->N] = item;
		printf("=== %d Insert %p into tbl->items[tbl->N]%p\n", tbl->N, item, tbl->items[tbl->N]);
		tbl->N++;
		sleep(2);
		return tbl->N;
	}

	t = key(tbl->items[ndex]);

	if (v < t) {
		int cha;

printf("=== A::a %d\n", ndex);
return ndex;
		cha = insert(tbl, tbl->left[ndex], item);
		tbl->left[ndex] = cha;
		printf("=== cha %d, tbl->left[%d] %d\n", cha, ndex, tbl->left[ndex]);
	} else if (t < v) {
		int cha;

printf("=== A::b %d\n", ndex);
printf("=== tbl->N %d, tbl->items[0] %p\n", tbl->N, tbl->items[0]);
		sleep(2);
		if (tbl->right[ndex] == 0) {
			ndex = tbl->N;
			tbl->right[ndex] = tbl->N;
		}
		cha = insert(tbl, tbl->right[ndex], item);
		tbl->right[ndex] = cha;
		printf("=== cha %d, tbl->left[%d] %d\n", cha, ndex, tbl->right[ndex]);
	} else {
		printf("=== Keys are equal.\n");
	}

printf("=== A::c\n");
	return ndex;
}

int
STinsert(unsigned int  tblindex, Item_t *item)
{
	int link;

	if (index_check(tblindex) < 0) {
		return -1;
	}

	link = insert(tables[tblindex], 0, item);

	printf("======= Inserted @ %d into table %d\n", link, tblindex);
	return link;
}

int
STcount(int tblindex)
{

	if (index_check(tblindex) < 0) {
		return -1;
	}

	return tables[tblindex]->N;
}

int
STprint(int tblindex)
{
	int i, j;
	struct table_s *tbl;

	printf("=== tblindex %d\n", tblindex);
	if (index_check(tblindex) < 0) {
		return -1;
	}

	tbl = tables[tblindex];

	for (i = 0; i < tbl->N; i++) {
		printf("=== Left ::");
		for (j = 0; j < 16 && j < tbl->N; j++) {
			if (i + j >= tbl->N) {
				break;
			}
			printf("\t(%d) %d", j, tbl->left[j]);
		}
		printf("\n");
		printf("=== Right ::");
		for (j = 0; j < 16 && j < tbl->N; j++) {
			if (i + j >= tbl->N) {
				break;
			}
			printf("\t(%d) %d", j, tbl->right[j]);
		}
		printf("\n\n");
		i += j;
	}

	return 0;
}

