/*
 *
 */

#if !defined(__ITEM_H__)
#define __ITEM_H__

#define	DEFAULT_ITEM_KEYLEN 16

typedef struct Item_s {
	int val;
	size_t keylen;
	char key[16];
} Item_t;

typedef int32_t Key_t;

Item_t * keyInit(int val, char *key);

#endif

