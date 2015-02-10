
#if !defined(__STACK_H__)
#define __STACK_H__

int8_t (*stack_init)(uint32_t depth);
int (*push)(int8_t ident, uint64_t entry);
uint64_t (*pop)(int8_t ident);
bool (*empty)(int8_t ident);
void (*examine)(int8_t index);

int8_t stk_init(uint32_t deep);
int stk_push(int8_t ident, uint64_t entry);
uint64_t stk_pop(int8_t ident);
bool stk_empty(int8_t ident);
void stk_examine(int8_t ident);

int8_t lstk_init(uint32_t dummy);
int lpush(int8_t index, uint64_t value);
uint64_t lpop(int8_t index);
bool lempty(int8_t index);
void lexamine(int8_t index);

#endif
