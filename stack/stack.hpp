typedef double stack_elem_t;

#define STACK_DEBUG
#define NDEBUG

#ifdef STACK_DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif

#ifndef STACK_DEPENDENCIES
#define STACK_DEPENDENCIES
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#endif

#ifndef STACK_H

#define STACK_H


enum STACK_ERRORS {
    STACK_OK = 0,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    STACK_WRONG_DATA_PTR,
    STACK_WRONG_CAPACITY,
    STACK_WRONG_LEFT_CANARY,
    STACK_WRONG_RIGHT_CANARY,
    STACK_WRONG_DATA_LEFT_CANARY,
    STACK_WRONG_DATA_RIGHT_CANARY,
};


struct stack {
    ON_DEBUG(size_t nigger1 = 0;)

    size_t size = 0;
    size_t capacity = 0;
    stack_elem_t *data = NULL;

    ON_DEBUG(bool data_allocated = 0;)

    ON_DEBUG(const char *origin_filename;)
    ON_DEBUG(void *ptr;)
    ON_DEBUG(const char *var_name;)
    ON_DEBUG(size_t line;)
    ON_DEBUG(const char *last_called;)
    ON_DEBUG(int error;)
    ON_DEBUG(const char *err_name;)

    ON_DEBUG(size_t nigger2 = 0;)
};


ssize_t stack_error         (struct  stack *stk);
ssize_t stack_assign_data_canaries
                            (struct  stack *stk);
ssize_t stack_constructor   (struct  stack *stk,       size_t       initial_size
                ON_DEBUG    (,const  char  *filename,  size_t       line,        const char *var_name));

ssize_t stack_destructor    (struct  stack *stk);
ssize_t stack_extend        (struct  stack *stk);
ssize_t stack_shrink        (struct  stack *stk);
void    stack_push          (struct  stack *stk,       stack_elem_t elem,        ssize_t    *err);
void    stack_pop           (struct  stack *stk,       stack_elem_t *out,        ssize_t    *err);
void    stack_dump          (struct  stack *stk);

bool    doubles_equal       (long double x,             long double y);

#endif
