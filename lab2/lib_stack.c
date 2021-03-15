#include <stdio.h>
#include <stdlib.h>

typedef struct list list;
struct list{
    list* next;
    char value;
};

typedef struct{
    list* head;
}stack_list;

stack_list init_stack_list();
list* stack_list_peek(stack_list* stack);
void stack_list_push(stack_list* stack, char value);
void stack_list_pop(stack_list* stack);
void print_stack_list(stack_list* stack);

stack_list init_stack_list()
{
    stack_list new_stack = {.head = NULL};
    return new_stack;
}

list* stack_list_peek(stack_list* stack)
{
    return stack->head;
}

void stack_list_push(stack_list* stack, char value)
{
    list* new_element = calloc(1, sizeof(list));
    new_element->value = value;
    new_element->next = stack->head;
    stack->head = new_element;
}

void stack_list_pop(stack_list* stack)
{
    list* popped_element = stack->head;
    stack->head = popped_element->next;
    free(popped_element);
}

void print_stack_list(stack_list* stack)
{
    list* ptr = stack->head;
    if(ptr == NULL){
        printf("Empty\n");
        return;
    }
    printf("Stack: \n");
    while(ptr!= NULL){
        printf("Element: %c\n", ptr->value);
        ptr = ptr->next;
    }
}



