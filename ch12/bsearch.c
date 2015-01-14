/*
 * Solution to problem 12.32 on page 496 of Sedgewich 5ed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/time.h>

#define	DEFAULT_SIZE	80

uint8_t unique[DEFAULT_SIZE] = {0};
uint8_t *map;

struct item_s {
	long int key;
	uint8_t  id[4];
};

struct node_s {
	struct item_s item;
};

#define	ISSET(a)	(map[a >> 8] & (1 << (a % 8)))
#define	SET(a)		(map[a >> 8] |= (1 << (a % 8)))
#define PRINTSET(size)	{int i; \
				printf("\t");	\
				for (i = 0; i < size; i++) {\
					printf("%02x ", map[i]);	\
				} 		\
				printf("\n");	\
			}
int32_t
btree_init(struct node_s *tree, size_t size)
{
	int i, count, modval, bitgap;
	long int val;

	modval = 256 * size;
	bitgap = modval >> 8;
	printf("modval %d, bitgap %d\n", modval, bitgap);

	map = malloc(bitgap);
	if (!map) {
		printf("Unable to  malloc a bitmap.\n");
		return -1;
	}

	bzero(map, bitgap);

	for (i = 0, count = 0; i < size; count++, i++) {
		val = random() % modval;
		if (ISSET(val)) {
			i--;
			printf("FOUND key: %ld\n", val);
			continue;
		}
		tree[i].item.key = val;
		SET(val);
	}
	PRINTSET(bitgap);
	printf("Loop count: %d\n", count);
}

int32_t
bsearch_nr(size_t lside, size_t rside,  struct node_s *Ray)
{
	int i, left, right;
	int mid;

	left = 0;
	right = size - 1;
	mid = (left + right) / 2;


	return 0;
}

int32_t
main(int argc, char *argv[])
{
	struct node_s *BTree;
	struct timeval tv;

	BTree = malloc(sizeof(struct node_s) * DEFAULT_SIZE);
	if (!BTree) {
		printf("Unable to allocate a search tree.\n");
		exit -1;
	}

	/* Randomize the seed origin. */
	gettimeofday(&tv, NULL);
	srandom(tv.tv_usec);

	printf("== Initialize the tree.\n");
	/* Setup the search tree. */
	btree_init(BTree, DEFAULT_SIZE);

	printf("== Search on 55\n");
	bsearch_nr(DEFAULT_SIZE, BTree);
}

