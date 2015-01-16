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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <getopt.h>
#include <item.h>

#define null(A) (eq(key(A), key(NULLitem)))

static	uint wboundry;
static	uint match_cnt;

static	char optstr[] = "wcz:";
static	struct option the_args[] = {
	{ "word-boundries", no_argument, &wboundry, 0x1},
	{ "count-matches", no_argument, &match_cnt, 0x1},
	{ "tree-size", required_argument, NULL, 'z'},
	{ 0 }
};

static uint maxN = 0;
static char *text;

main(int argc, char *argv[])
{
	int i, t, N = 0, ndx = 0;
	char query[maxN];
	char *v;
	FILE *corpus = fopen(*++argv, "r");
	while ((i = getopt_long(argc, argv, optstr, the_args, &ndx)) != -1) {
		switch(i) {
		case 'w':
			wboundry |= 0x1;
			break;
		case 'c':
			match_cnt |= 0x1;
			break;
		case 'm':
			text = optarg;
			N = strlen(text);
			maxN = N;
			break;
		case 'z':
			maxN = strtoul(optarg, &v, 0);
			if (*v == '\0') {
				printf("Unable to interpret the capacity value: %s\n", optarg);
				exit(-1);
			}
			break;
		}
	}

	if (maxN == 0) {
		printf("No tree size has been specified.  Please use '-z' or '--tree-size' and provide a capacity value.\n");
		exit(-1);
	}

	/* Check for any text strings to search for. */
	if (optind < argc) {
		while (optind < argc) {
			if (N == maxN) {
				break;
			}
			text[N++] = argv[optind++];
		}
	}
	text[N] = '\0';

	STinit(maxN);

	for (i = 0; i < N; i++) {
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

