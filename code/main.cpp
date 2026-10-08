#include "../stack/stack.hpp"
#include <stdio.h>


int main() {
    struct stack stack = {};
    stack_constructor(&stack, 5 ON_DEBUG(, __FILE_NAME__, __LINE__, "stack"));

    ssize_t err = STACK_OK;
    stack_elem_t out = 0.;

    stack_push(&stack, 15.5, &err); stack_dump(&stack);
    stack_push(&stack, 777.5, &err); stack_dump(&stack);
    stack_push(&stack, -3.5, &err); stack_dump(&stack);
    stack_push(&stack, -2.5, &err); stack_dump(&stack);
    stack_push(&stack, -1.5, &err); stack_dump(&stack);
    stack_push(&stack, -0.5, &err); stack_dump(&stack);
    stack_push(&stack,  0.5, &err); stack_dump(&stack);
    //*((char *) stack.data + 18) = 3; stack_error(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out); stack_dump(&stack);
    //*((char *) stack.data + 11) = 3; stack_error(&stack);
    //*((char *) &stack + 33) = 5; stack_error(&stack);
    stack_destructor(&stack);

    return 0;
}
