/*
 *
 */
#if !defined(__TREE_H__)
#define __TREE_H__

struct node_s {
	struct node_s *right;
	struct node_s *left;
	struct Item_s item;
};

int BSTreeInit(struct node_s **tree, size_t size, uint seed);


#define	ISSET(a)	(map[a >> 8] & (1 << (a % 8)))
#define	SET(a)		(map[a >> 8] |= (1 << (a % 8)))
#define PRINTSET(size)	{int i; \
				printf("\t");	\
				for (i = 0; i < size; i++) {\
					printf("%02x ", map[i]);	\
				} 		\
				printf("\n");	\
			}
#endif

