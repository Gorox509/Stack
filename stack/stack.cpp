#include "stack.hpp"

#define GET_CANARY(ptr) (0xDEFEC8ED^((size_t) ptr))
#define GET_DATA_CANARY(type, ptr) ((type) (0xDEFEC8ED^((size_t) ptr)))


ssize_t stack_error(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(
    if (stk->nigger1 != GET_CANARY(&stk->nigger1)) {
        stk->error = STACK_WRONG_LEFT_CANARY;
        stk->err_name = "STACK_WRONG_LEFT_CANARY";
        stack_dump(stk);
        return STACK_WRONG_LEFT_CANARY;
    }

    if (stk->nigger2 != GET_CANARY(&stk->nigger2)) {
        stk->error = STACK_WRONG_RIGHT_CANARY;
        stk->err_name = "STACK_WRONG_RIGHT_CANARY";
        stack_dump(stk);
        return STACK_WRONG_RIGHT_CANARY;
    }

    if (stk->data_allocated && stk->data == NULL && (stk->size != 0 || stk->capacity != 0)) {
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

    if (stk->size == (size_t) -1) {
        stk->error = STACK_UNDERFLOW;
        stk->err_name = "STACK_UNDERFLOW";
        stack_dump(stk);
        return STACK_UNDERFLOW;
    }

    if (stk->data_allocated && !doubles_equal(stk->data[0], GET_DATA_CANARY(stack_elem_t, &stk->data[0]))) {
        stk->error = STACK_WRONG_DATA_LEFT_CANARY;
        stk->err_name = "STACK_WRONG_DATA_LEFT_CANARY";
        stack_dump(stk);
        return STACK_WRONG_DATA_LEFT_CANARY;
    }

    if (stk->data_allocated && !doubles_equal(stk->data[stk->capacity + 1], GET_DATA_CANARY(stack_elem_t, &stk->data[stk->capacity + 1]))) {
        stk->error = STACK_WRONG_DATA_RIGHT_CANARY;
        stk->err_name = "STACK_WRONG_DATA_RIGHT_CANARY";
        stack_dump(stk);
        return STACK_WRONG_DATA_RIGHT_CANARY;
    }

    stk->error = STACK_OK;
    stk->err_name = "STACK_OK";
    )
    return STACK_OK;
}


ssize_t stack_assign_data_canaries(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    assert(stack_error(stk) == STACK_OK);
    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    ON_DEBUG(stk->data[0] = GET_DATA_CANARY(stack_elem_t, &stk->data[0]);)
    ON_DEBUG(stk->data[stk->capacity + 1] = GET_DATA_CANARY(stack_elem_t, &stk->data[stk->capacity + 1]);)

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    return err;
}


ssize_t stack_constructor(struct stack *stk, size_t initial_size
    ON_DEBUG(, const char *filename, size_t line, const char *var_name))
{
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ON_DEBUG(stk->nigger1 = GET_CANARY(&stk->nigger1);)
    ON_DEBUG(stk->nigger2 = GET_CANARY(&stk->nigger2);)

    ssize_t err = STACK_OK;

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    if (err != STACK_OK)
        return err;

    stk->data = (stack_elem_t *) calloc(initial_size ON_DEBUG(+2), sizeof(stack_elem_t));

    stk->size = 0;
    stk->capacity = initial_size;

    ON_DEBUG(
    if ((err = stack_assign_data_canaries(stk)) != STACK_OK)
        return err;
    )
    ON_DEBUG(stk->data_allocated = 1;)

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
    ON_DEBUG(stk->data_allocated = 0;)

    assert(stack_error(stk) == STACK_OK);
    err = stack_error(stk);

    return err;
}


ssize_t stack_extend(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    ON_DEBUG(stk->data_allocated = 0;)

    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    stk->capacity *= 2;
    stk->data = (stack_elem_t *) realloc((void *) stk->data, (stk->capacity ON_DEBUG(+2)) * sizeof(stack_elem_t));

    ON_DEBUG(
    if ((err = stack_assign_data_canaries(stk)) != STACK_OK)
        return err;
    )

    ON_DEBUG(stk->data_allocated = 1;)

    assert(stack_error(stk) == STACK_OK);
    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    return err;
}


ssize_t stack_shrink(struct stack *stk) {
    assert(stk != NULL);
    ON_DEBUG(stk->last_called = __func__;)

    ssize_t err = STACK_OK;

    ON_DEBUG(stk->data_allocated = 0;)

    if ((err = stack_error(stk)) != STACK_OK)
        return err;

    size_t new_capacity = stk->capacity / 2 + stk->capacity % 2;

    stk->data = (stack_elem_t *) realloc(stk->data, (new_capacity ON_DEBUG(+2)) * sizeof(stack_elem_t));
    stk->capacity = new_capacity;

    ON_DEBUG(
    if ((err = stack_assign_data_canaries(stk)) != STACK_OK)
        return err;
    )

    ON_DEBUG(stk->data_allocated = 1;)

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

    stk->data[stk->size++ ON_DEBUG(+1)] = elem;

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

    *out = stk->data[--stk->size ON_DEBUG(+1)];

    while (stk->capacity > 1 && stk->size * 4 < stk->capacity) {
        if ((*err = stack_shrink(stk)) != STACK_OK)
            return;
    }

    assert(stack_error(stk) == STACK_OK);
    *err = stack_error(stk);

    return;
}


void stack_dump(struct stack *stk) {
    assert(stk != NULL);


    ON_DEBUG(fprintf(stderr, "\nVariable \"%s\" of type stack at [%p] created in %s:%lu called from function \"%s\":\n",
                    stk->var_name, stk->ptr, stk->origin_filename, stk->line, stk->last_called);)
    ON_DEBUG(if (stk->error != STACK_OK) fprintf(stderr, "Error code %d: %s\n",
                                                stk->error, stk->err_name);)

    ON_DEBUG(fprintf(stderr, "\tleft  canary value: %lu\n", stk->nigger1);)
    ON_DEBUG(fprintf(stderr, "\tright canary value: %lu\n", stk->nigger2);)

    fprintf(stderr, "\tsize: %lu\n"
                    "\tcapacity: %lu\n"
                    "\tdata: [%p]\n"
    , stk->size, stk->capacity, stk->data
    );
    ON_DEBUG(fprintf(stderr, "\t\t  data[%lu] = % lf\n", 0LU, stk->data[0]);)
    for (size_t i = 0 ON_DEBUG(+1); i < stk->size ON_DEBUG(+1) && i < stk->capacity ON_DEBUG(+1); ++i) { // min(size, cap)
        fprintf(stderr, "\t\t* data[%lu] = % lf\n", i, stk->data[i]);
    }

    for (size_t i = stk->size ON_DEBUG(+1); i < stk->capacity ON_DEBUG(+2) || i < stk->size ON_DEBUG(+2); ++i) { // max(size, cap)
        fprintf(stderr, "\t\t  data[%lu] = % lf\n", i, stk->data[i]);
    }

    fprintf(stderr, "\n\n");
}


bool doubles_equal(long double x, long double y) {
    return (abs(x) - abs(y) < 10e-6);
}
