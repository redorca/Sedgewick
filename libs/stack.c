#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACKS_COUNT 16

typedef struct stack_entry_s {
	uint64_t entry;
} stack_entry_t;

typedef struct stack_s {
	uint64_t *entries;
	uint8_t depth;
	uint8_t length;
} stack_t;

static uint8_t stk_index = 0;
static stack_t *stk_table[STACKS_COUNT];

int8_t
stk_init(uint32_t deep)
{
	int8_t tmp;

	if (stk_index >= STACKS_COUNT) {
		return -1;
	}
	stk_table[stk_index] = malloc(sizeof(stack_t));
	if (stk_table[stk_index] == NULL) {
		return -1;
	}

	stk_table[stk_index]->length = deep;
	stk_table[stk_index]->depth  = 0;

	stk_table[stk_index]->entries = malloc(sizeof(void **) * stk_table[stk_index]->length);
	if (stk_table[stk_index]->entries == NULL) {
		return -1;
	}

	tmp = (int8_t) stk_index;
	stk_index++;

	return tmp;
}

void
stk_release(int8_t ident)
{
	stack_t *stk = stk_table[ident];

	free(stk->entries);
}

int
push(int8_t ident, uint64_t entry)
{
	stack_t *stk;

	if (ident > (STACKS_COUNT - 1)) {
		return -1;
	}
	stk = stk_table[ident];
	if (!(stk->depth < stk->length)) {
		return -1;
	}
	stk = stk_table[ident];
	stk->entries[stk->depth] = entry;
	stk->depth++;

	return 0;
}

uint64_t
pop(int8_t ident)
{
	stack_t *stk;
	uint64_t entry;

	stk = stk_table[ident];
	stk->depth--;
	entry = stk->entries[stk->depth];

	return entry;
}

bool
empty(int8_t ident)
{
	return (stk_table[ident]->depth == 0);
}

void
xamine(int8_t ident)
{
	int i;
	stack_t *stk;

	stk = stk_table[ident];

	printf("Stack id %d,  depth %d\n", ident, stk->depth);
	for  (i = stk->depth - 1; i > -1; i--) {
		printf("=== stk entry %d :: %ld\n", i, stk->entries[i]);
	}

}

