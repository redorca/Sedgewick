

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <stack.h>
#include <random.h>

#define OPTIONS "lahd:z:"

enum stack_tech_e {
	E_ARRAY,
	E_LIST,
	E_END,
};
void
usage(void)
{
	printf("stkchk:\n");
	printf("\t-a\tUse an array for holding the stack.\n");
	printf("\t-l\tUse a list to hold the stack.\n");
	printf("\t-d\tSet the stack depth if an array is used.\n");
	printf("\t-z\tSet the size of the stack to test.\n");
	printf("\n");
}

int
main(int argc, char  *argv[])
{
	uint8_t stacki;
	uint64_t value, size;
	uint32_t depth = 0;
	int i, c;
	enum stack_tech_e stech;

	while((c = getopt(argc, argv, OPTIONS)) != -1) {
		switch(c) {
			case 'z':
				size = strtoul(optarg, NULL, 0);
				break;
			case 'd':
				depth = strtoul(optarg, NULL, 0);
				break;
			case 'a':
				stech = E_ARRAY;
				push  = stk_push;
				pop   = stk_pop;
				empty = stk_empty;
				examine = stk_examine;
				stack_init = stk_init;
				break;
			case 'l':
				stech = E_LIST;
				push  = lpush;
				pop   = lpop;
				empty = lempty;
				examine = lexamine;
				stack_init = lstk_init;
				break;
			case 'h':
			default:
				usage();
				exit(0);
				break;
		}
	}

	if ((stech == E_ARRAY) && (depth == 0)) {
		printf("No depth specfied.\n");
		usage();
		exit(-1);
	}

	if (stack_init == NULL) {
		printf("Failed to specify a stack tech.\n");
		usage();
		exit(-1);
	}

	stacki = stack_init(depth);
	if (stacki < 0) {
		printf("Failed to  initialize a stack.\n");
		exit(stacki);
	}

	random_init();

	for (i = 0; i < size; i++) {
		uint64_t rand = random();

		rand = rand % 2048;
		push(stacki, rand);
	}

	push(stacki, 8);
	push(stacki, 9);
	push(stacki, 7);
	push(stacki, 2);

	value = pop(stacki);
	printf("Popped %ld\n", value);
	examine(stacki);

	if (empty(stacki)) {
		printf("=== stack %d is empty\n", stacki);
	}

	for (i = 0; !empty(stacki); i++) {
		value = pop(stacki);
		printf("=== pop %4lu\n", value);
	}
	printf("Popped %d times\n", i);
	examine(stacki);

}

