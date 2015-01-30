/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/time.h>
#include <getopt.h>
#include "item.h"
#include "tree.h"

/*
 * Driver to exercise search solutions, such as BSTs, using a well known interface
 * defined by Program 12.1 on up.
 */

char options[] = "z:"; 
int trees[5];
int
main(int argc, char *argv[])
{
	unsigned int myopt, size = 0;
	unsigned int i, j;
	Item_t *items[3];

	while ((myopt = getopt(argc, argv, options)) != -1) {
		switch(myopt) {
		case 'z':
			size = strtoul(optarg, NULL, 0);
			break;
		default:
			printf("Error:  No such option supported (%c)\n", myopt);
			exit(-1);
			break;
		}
	}

	if (size == 0) {
		printf("No size specified.\n");
		exit(-1);
	}

	i = 0;
	for (i = 0; i < size; i++) {
		trees[i] = STinit(size);
	}

	for (j = 0; j < 3; j++) {
		items[j] = malloc(sizeof(Item_t));
		items[j]->val = j + 1;
	}

	STinsert(trees[0], items[0]);
	STinsert(trees[0], items[1]);
	STinsert(trees[0], items[2]);
	STprint(trees[0]);
	STclear(trees[0]);

	exit(0);
}

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

