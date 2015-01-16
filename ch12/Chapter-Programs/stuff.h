
#if !defined(__STUFF_H__)
#define __STUFF_H__

#define	less(a, b)	(a < b)
#define eq(a, b)	(a == b)

typedef struct STnode_s link;
struct STnode_s {
		Item_t *item;
		link *l;
		link *r;
		int N;
};

link *NEW(Item_t *item, link *l,  link *r, int N);


static link *head, *z;

#endif
