#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <stack.h>

#define STACKS_COUNT 16

typedef struct stack_entry_s {
	uint64_t entry;
} stack_entry_t;

typedef struct stack_s {
	uint64_t *entries;
	uint8_t depth;
	uint8_t length;
} stack_t;

typedef struct list_stack_s {
	struct  list_stack_s *next;
	uint64_t value;
} list_stack_t;

static uint8_t stk_index = 0;
static uint8_t lstk_index = 0;
static stack_t *stk_table[STACKS_COUNT];
static list_stack_t *lstack_table[STACKS_COUNT];

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
stk_push(int8_t ident, uint64_t entry)
{
	stack_t *stk;

	if (ident > (STACKS_COUNT - 1)) {
		return -1;
	}
	stk = stk_table[ident];
	if (!(stk->depth < stk->length)) {
		fprintf(stderr, "Pushing onto a full stack.\n");
		raise(SIGSTKFLT);
		return -1;
	}
	stk = stk_table[ident];
	stk->entries[stk->depth] = entry;
	stk->depth++;

	return 0;
}

uint64_t
stk_pop(int8_t ident)
{
	stack_t *stk;
	uint64_t entry;

	stk = stk_table[ident];
	stk->depth--;
	entry = stk->entries[stk->depth];

	return entry;
}

bool
stk_empty(int8_t ident)
{
	return (stk_table[ident]->depth == 0);
}

void
stk_examine(int8_t ident)
{
	int i;
	stack_t *stk;

	stk = stk_table[ident];

	printf("Stack id %d,  depth %d\n", ident, stk->depth);
	for  (i = stk->depth - 1; i > -1; i--) {
		printf("=== stk entry %d :: %ld\n", i, stk->entries[i]);
	}

}

int8_t
lstk_init(uint32_t dummy)
{
	uint64_t cur_index = lstk_index;

	if (!(lstk_index < STACKS_COUNT)) {
		return -1;
	}
	lstack_table[cur_index] = malloc(sizeof(list_stack_t));
	if (!lstack_table[cur_index]) {
		return -1;
	}
	lstack_table[cur_index]->next = NULL;
	lstk_index++;

	return cur_index;
}

int
lpush(int8_t index, uint64_t value)
{
	list_stack_t *stk, *tmp;

	stk = lstack_table[index];
	tmp = malloc(sizeof(list_stack_t));
	if (!tmp) {
		return -1;
	}
	tmp->value = value;

	tmp->next = stk->next;
	stk->next = tmp;

	return 0;
}

uint64_t
lpop(int8_t index)
{
	list_stack_t *tmp, *head;
	uint64_t val;

	head = lstack_table[index];
	tmp = head->next;
	head->next = head->next->next;
	val = tmp->value;

	free(tmp);

	return val;
}

bool
lempty(int8_t index)
{
	list_stack_t *head;

	head = lstack_table[index];

	return (head->next == NULL);
}

void
lexamine(int8_t index)
{
	list_stack_t *head;

	printf("Examine stack list %d\n", index);

	head = lstack_table[index];
	head = head->next;
	while (head) {
		printf("=== %d\n", head->value);
		head = head->next;
	}
}

