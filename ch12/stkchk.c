

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stack.h>


int
main(int argc, char  *argv[])
{
	uint8_t stacki;
	uint64_t value;
	uint32_t depth;
	int i;

	depth = 128;
	stacki = stk_init(depth);
	if (stacki < 0) {
		printf("Failed to  initialize a stack.\n");
		exit(stacki);
	}

	for (i = 0; i < depth; i++) {
		push(stacki, i);
	}

	push(stacki, 8);
	push(stacki, 9);
	push(stacki, 7);
	push(stacki, 2);

	value = pop(stacki);
	printf("Popped %ld\n", value);
	xamine(stacki);

	if (empty(stacki)) {
		printf("=== stack %d is empty\n", stacki);
	}

	for (i = 0; !empty(stacki); i++) {
		pop(stacki);
	}
	printf("Popped %d times\n", i);
	xamine(stacki);

}

