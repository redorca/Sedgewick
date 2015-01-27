/*
 *
 */
#if !defined(__TREE_H__)
#define __TREE_H__

struct node_s {
	uint32_t count;
	struct node_s *right;
	struct node_s *left;
	struct Item_s item;
};

int STcount(void *tbl);
int STinsert(void *tbl, Item_t *item);
Item_t *STsearch(void *tbl, Key_t key);
void STclear(void *tbl);
void *STinit(unsigned int size);


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

