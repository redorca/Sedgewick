
#if !defined(__STACK_H__)
#define __STACK_H__


int8_t stk_init(uint32_t deep);
int push(int8_t ident, uint64_t entry);
uint64_t pop(int8_t ident);
bool empty(int8_t ident);
void xamine(int8_t ident);

#endif
