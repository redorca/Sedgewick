/*
 * 12.6 Binary search (for array-based symbol table)
 *
 *     This implementation of STsearch uses a recursive binary search pro-
 * cedure.  To find whether a given key, v, is in an ordered array, it first
 * compares v with the element at the middle position.  If v is smaller, then
 * it must be in the first half of the array; if v is greater, then it must be in
 * the second half of the array.
 *
 *     The array must be in sorted order.  This function could replace
 * STsearch in Program 12.4 which maintains the order dynamically
 * during insertion; or we could include a construct function that uses a
 * standard sort routine
 */

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

Item *
search(int l, int r, Key_t *v)
{
	int m = (l + r)/2;

	if (l > r) {
		return NULLitem;
	}

	if (eq(v, key(st[m]))) {
		return st[m];
	}

	if (l == r) {
		return NULLitem;
	}

	if (less(v, key(st[m]))) {
		return search(l, m - 1, v);
	} else {
		return search(m + 1, r, v);
	}

}

Item_t *
STsearch(Key_t *v)
{
	return search(0, N - 1, v);
}

