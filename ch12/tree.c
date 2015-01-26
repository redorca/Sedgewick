/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/time.h>
#include "item.h"
#include "tree.h"

/*
 * tree_create()
 *
 *     Provide a BST filled with unique random values
 *     based either on a seed value provided or on the
 *     number of microseconds since the last second
 *     of the current time (seed = 0).
 */
int
tree_create(struct node_s **tree, size_t size, uint seed)
{
	int i, count, modval, bitgap;
	long int val;
	struct timeval tv;
	uint8_t *map;

	if (tree == NULL) {
		printf("No tree pointer passed in.\b");
		return -1;
	}

	/*
	 * If the RNG seed value is 0 then spend a bit of effort
	 * to randomize a seed and avoid repeatable tree gneration.
	 */
	if (seed == 0) {
		gettimeofday(&tv, NULL);
		seed = tv.tv_usec;
	}

	/*
	 * Set the range of random values used in the tree to be
	 * larger than the size of the tree so that guaranteeing
	 * a tree of unique values is easier.
	 */
	modval = size * 10;
	/* Size the bitmap by byte/bits */
	bitgap = modval >> 8;
	map = malloc(bitgap);
	if (!map) {
		printf("Unable to  malloc a bitmap.\n");
		return -1;
	}
	bzero(map, bitgap);

	*tree = (struct node_s *) malloc(sizeof(struct node_s) * size);
	if (*tree == NULL) {
		free(map);
		printf("Unable to allocate a search tree.\n");
		return -1;
	}

	srandom(seed);
	for (i = 0, count = 0; i < size; count++, i++) {
		val = random() % modval;
		/* See if this value is already mapped. */
		if (ISSET(val)) {
			i--;
			continue;
		}
		(*tree)->item.val = val;
		(*tree)++;
		SET(val);
	}

	free(map);

	return 0;
}

