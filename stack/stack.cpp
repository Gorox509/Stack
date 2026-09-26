#include "stack.hpp"


ssize_t stack_error(struct stack *stk) {
    assert(stk != NULL);

    if (stk->data == NULL && (stk->size != 0 || stk->capacity != 0)) {
        stk->error = STACK_WRONG_DATA_PTR;
        stk->err_name = "STACK_WRONG_DATA_PTR";
        stack_dump(stk);
        return STACK_WRONG_DATA_PTR;
    }

    if (stk->size > stk->capacity) {
        stk->error = STACK_OVERFLOW;
        stk->err_name = "STACK_OVERFLOW";
        stack_dump(stk);
        return STACK_OVERFLOW;
    }

    if (stk->capacity == 0 && stk->data != NULL) {
        stk->error = STACK_WRONG_CAPACITY;
        stk->err_name = "STACK_WRONG_CAPACITY";
        stack_dump(stk);
        return STACK_WRONG_CAPACITY;
    }

    stk->error = STACK_OK;
    stk->err_name = "STACK_OK";
    return STACK_OK;
}


ssize_t stack_constructor(struct stack *stk, size_t initial_size
    ON_DEBUG(, const char *filename, size_t line, const char *var_name))
{
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    if (err != STACK_OK)
        return err;

    stk->data = (stack_elem_t *) calloc(initial_size, sizeof(stack_elem_t));
    stk->size = 0;
    stk->capacity = initial_size;

    ON_DEBUG(stk->origin_filename = filename;)
    ON_DEBUG(stk->ptr = (void *) stk;)
    ON_DEBUG(stk->var_name = var_name;)
    ON_DEBUG(stk->line = line;)

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    return err;
}


ssize_t stack_destructor(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    assert(stack_error(stk) == STACK_OK);
    ssize_t err = stack_error(stk);

    if (err != STACK_OK)
        return err;

    free(stk->data);

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    return err;
}


ssize_t stack_extend(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    stk->data = (stack_elem_t *) realloc((void *) stk->data, (stk->capacity *= 2) * sizeof(stack_elem_t));

    assert(stack_error(stk) == STACK_OK);
    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    return err;
}


ssize_t stack_shrink(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    stk->data = (stack_elem_t *) realloc(stk->data, (stk->capacity / 2 + stk->capacity % 2) * sizeof(stack_elem_t));
    stk->capacity /= 2;

    assert(stack_error(stk) == STACK_OK);
    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    return err;
}


void stack_push(struct stack *stk, stack_elem_t elem, ssize_t *err) {
    assert(stk != NULL);
    assert(err != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    assert((*err = stack_error(stk)) == STACK_OK);
    if ((*err = stack_error(stk)) != STACK_OK)
        return;

    if (stk->size == stk->capacity) {
        if ((*err = stack_extend(stk)) != STACK_OK)
            return;
    }

    stk->data[stk->size++] = elem;

    assert(stack_error(stk) == STACK_OK);
    *err = stack_error(stk);

    return;
}


void stack_pop(struct stack *stk, stack_elem_t *out, ssize_t *err) {
    assert(stk != NULL);
    assert(err != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    assert((*err = stack_error(stk)) == STACK_OK);
    if ((*err = stack_error(stk)) != STACK_OK)
        return;

    if (stk->size != 0 && stk->size * 2 < stk->capacity) {
        if ((*err = stack_shrink(stk)) != STACK_OK)
            return;
    }
    *out = stk->data[--stk->size];

    assert(stack_error(stk) == STACK_OK);
    *err = stack_error(stk);

    return;
}


void stack_dump(struct stack *stk) {
    assert(stk != NULL);


    ON_DEBUG(fprintf(stderr, "\nVariable \"%s\" of type stack at [%p] created in %s:%lu called from function \"%s\":\n",
                    stk->var_name, stk->ptr, stk->origin_filename, stk->line, stk->last_called);)
    ON_DEBUG(if (stk->error != STACK_OK) fprintf(stderr, "Error code %d: %s",
                                                stk->error, stk->err_name);)

    fprintf(stderr, "\tsize: %lu\n"
                    "\tcapacity: %lu\n"
                    "\tdata: [%p]\n"
    , stk->size, stk->capacity, stk->data
    );

    for (size_t i = 0; i < stk->size; ++i) {
        fprintf(stderr, "\t\t* data[%lu] = %lf\n", i, stk->data[i]);
    }

    for (size_t i = stk->size; i < stk->capacity; ++i) {
        fprintf(stderr, "\t\t  data[%lu] = %lf\n", i, stk->data[i]);
    }

    fprintf(stderr, "\n\n");
}
