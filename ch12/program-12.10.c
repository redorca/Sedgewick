/*
 * Program 12.10  Example of indexing a text string.
 *
 *     This program assumes that Item.h defines keyType and itemType to
 *     be3 char *; and also defines less and eq for string keys using strcmp
 *     (see text).  The #include directives are the same as in Program 12.2
 *     (plus <string.h>) and are omitted.  The main program reads a text
 *     string from a specified file and uses a symbol table to build an index
 *     from the strings dsefined by starting at each character in the text string.
 *     Then, it reads query str4ings from the standard input, and prints the position
 *     where the querrys found in the text (or prints not found).  With a BST
 *     symbol table implementation, the search is fast, even for huge strings.
 */

#define null(A) (eq(key(A), key(NULLitem)))

static char text[maxN];

main(int argc, char *argv[])
{
	int i, t, N = 0;
	char query[maxQ];
	char *v;
	FILE *corpus = fopen(*++argv, "r");
	while ((t = getc(corpus)) != EOF) {
		if (N < maxN - 1) {
			text[N++] = t;
		} else {
			break;
		}
	}
	text[N] = '\0';

	STinit(maxN);

	for (i = 0; i < N; i__) {
		STinsert(&text[i]);
	}

	while (gets(query) != NULL) {
		if (!null(v = STsearch(query))) {
			/* N.B.  I don't know where 'v-text' comes from or what it means. */
			printf("%11d %s\n", v-text, query);
		} else {
			printf("(not found) %s\n", query);
		}
	}

}

