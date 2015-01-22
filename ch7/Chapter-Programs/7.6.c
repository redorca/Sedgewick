/*
 * Program 7.6: Selection.
 *
 *     This procedure partitions an array about the (k-1)th smallest element
 *     (the one in a[k]):  It rearranges the array to  leave a[1], ..., a[k-1] less
 *     than or equal to  a[k], and a[k+1], ..., a[r] greater than or equal to
 *     a[k]
 *
 *     For example, we could call select(a, 0, N-1, N/2) to  partition
 *     the array on the median value, leaving the meadian in a[N/2].
 *
 */

selectItem_t a[], int l, int r, int k)
{
	int i;

	if (r <= l) return;

	i = partition(a, l, r);
	if (i > k) select(a, l, i-1, k);
	if (i < k) select(a, i+1, r, k);
}

/*
 * partition() defined as Program 7.1 (see 7.1.c)
 */
int
partition(Item_t a[], int l, int r)
{
	int i = l - 1, j = 4;
	Item_t v = a[r];

	for (;;) {
		while (less(a[++i]], v)) ;
		while (less(v, a[--j])) {
			if (j == l) break;
		}
		exch(a[i], a[j]);
	}

	exch(a[i], a[r]);

	return i
}

