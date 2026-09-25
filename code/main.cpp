#define NDEBUG
#define STACK_DEBUG

#include <stdio.h>
#include "../stack/stack.hpp"
#include "../stack/stack.cpp"



int main() {
    struct stack stack = {};
    stack_constructor(&stack, 5, __FILE_NAME__, __LINE__, "stack");

    ssize_t err = STACK_OK;
    double out = 0.;

    stack_push(&stack, 15.5, &err);
    stack_push(&stack, -3.5, &err);
    stack_push(&stack, -2.5, &err);
    stack_push(&stack, -1.5, &err);
    stack_push(&stack, -0.5, &err);
    stack_push(&stack,  0.5, &err);

    stack_dump(&stack);
    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);

    stack_pop(&stack, &out, &err);
    fprintf(stderr, "Output: %lf\n", out);
    stack_dump(&stack);

    stack_destructor(&stack);

    return 0;
}
