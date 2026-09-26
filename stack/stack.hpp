typedef double stack_elem_t;

#ifdef STACK_DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif

#ifndef STACK_H

#define STACK_H

#include <stdlib.h>
#include <assert.h>

enum STACK_ERRORS {
    STACK_OK = 0,
    STACK_OVERFLOW = 1,
    STACK_UNDERFLOW = 2,
    STACK_WRONG_DATA_PTR = 3,
    STACK_WRONG_CAPACITY = 4,
    stack_errors_amount,
};


struct stack {
    size_t size = 0;
    size_t capacity = 0;
    stack_elem_t *data = NULL;

    ON_DEBUG(const char *origin_filename;)
    ON_DEBUG(void *ptr;)
    ON_DEBUG(const char *var_name;)
    ON_DEBUG(size_t line;)
    ON_DEBUG(const char *last_called;)
    ON_DEBUG(int error;)
    ON_DEBUG(const char *err_name;)
};


ssize_t stack_error(struct stack *stk);
ssize_t stack_constructor(struct stack *stk, size_t initial_size
                ON_DEBUG(, const char *filename, size_t line, const char *var_name));

ssize_t stack_destructor(struct stack *stk);
ssize_t stack_extend(struct stack *stk);
ssize_t stack_shrink(struct stack *stk);
void stack_push(struct stack *stk, stack_elem_t elem, ssize_t *err);
void stack_pop(struct stack *stk, stack_elem_t *out, ssize_t *err);
void stack_dump(struct stack *stk);


#endif
