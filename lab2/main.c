#include <stdio.h>
#include "lib_stack.h"

int main()
{
    stack_list stack;
    stack = init_stack_list();
    print_stack_list(&stack);
    stack_list_push(&stack, 'a');
    print_stack_list(&stack);
    stack_list_push(&stack, 'b');
    print_stack_list(&stack);
    stack_list_pop(&stack);
    print_stack_list(&stack);
    for(int i = 0;i < 10; i++){
        stack_list_push(&stack, i+50);
    }
    print_stack_list(&stack);
    for(int i = 0;i < 5; i++){
        stack_list_pop(&stack);
    }
    print_stack_list(&stack);
    return 0;
}
