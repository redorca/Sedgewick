/*
 * Key handling for search handling.
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "item.h"

/*
 * Return an integer representation of the key.
 */
int
key(Item_t *item)
{
	if (item == NULL) {
		return -1;
	}

	return item->val;
}

/*
 * Initialize the item's key and value.
 */
Item_t *
keyInit(int val, char *key)
{
	Item_t *item;

	item = (Item_t *)malloc(sizeof(*item));
	if (item) {
		item->keylen = DEFAULT_ITEM_KEYLEN;
		item->val = val;
		memcpy(item->key, key, item->keylen);
	}

	return item;
}

void
keyRelease(Item_t *item)
{
	if (item) {
		free(item);
	}
}
