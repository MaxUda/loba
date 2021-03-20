#include <stdio.h>
#include <stdlib.h>

typedef struct list list;
struct list{
    list* next;
    char value;
    int num;
};

#ifdef LIST

typedef struct{
    list* head;
}stack_list;

void init_stack_list(stack_list* stack, int size);
char stack_list_peek_char(stack_list* stack);
int stack_list_peek_int(stack_list* stack);
void stack_list_push(stack_list* stack, char value, int num);
int stack_list_pop(stack_list* stack);
void print_stack_list(stack_list* stack);
void stack_list_delete(stack_list* stack);
int check_if_empty(stack_list* stack);

void init_stack_list(stack_list* stack, int size)
{
    stack->head = NULL;
}

int check_if_empty(stack_list* stack)
{
    if(stack->head == NULL)
        return 1;
    else
        return 0;
}

char stack_list_peek_char(stack_list* stack)
{
    return stack->head->value;
}

int stack_list_peek_int(stack_list* stack)
{
    return stack->head->num;
}

void stack_list_push(stack_list* stack, char value, int num)
{
    list* new_element = calloc(1, sizeof(list));
    new_element->value = value;
    new_element->num = num;
    new_element->next = stack->head;
    stack->head = new_element;
}

int stack_list_pop(stack_list* stack)// 0 - error
{
    if(stack->head == NULL){
        return 0;
    }
    list* popped_element = stack->head;
    stack->head = popped_element->next;
    free(popped_element);
    return 1;
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

void stack_list_delete(stack_list* stack)
{
    list* ptr = stack->head;
    while(ptr != NULL){
        list* tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }//delete stack later
}

#elif VECTOR

typedef struct{
    int top, size;
    int* nums;
    char* chars;
}stack_list;

void init_stack_list(stack_list* stack, int size);
char stack_list_peek_char(stack_list* stack);
int stack_list_peek_int(stack_list* stack);
void stack_list_push(stack_list* stack, char value, int num);
int stack_list_pop(stack_list* stack);
void print_stack_list(stack_list* stack);
void stack_list_delete(stack_list* stack);
int check_if_empty(stack_list* stack);

void init_stack_list(stack_list* stack, int size){
    stack->top = 0;
    stack->size = size;
    stack->nums = calloc(size, sizeof(int));
    stack->chars = calloc(size, sizeof(char));
}

int check_if_empty(stack_list* stack){
        if(stack->top == 0)
                return 1;
        else
                return 0;
}


int stack_list_peek_int(stack_list* stack)
{
    if(stack->top == 0){
        printf("Error: can not read from empty stack\n");
        //return;
    }
    return stack->nums[stack->top-1];
}

char stack_list_peek_char(stack_list* stack)
{
    if(stack->top == 0){
        printf("Error: can not read from empty stack\n");
        //return;
    }
    return stack->chars[stack->top-1];
}

void stack_list_push(stack_list* stack, char value, int num)
{
    if(stack->top == stack->size){
        printf("Error: stack overflow\n");
        return;
    }
    stack->nums[stack->top] = num;
    stack->chars[stack->top] = value;
    stack->top++;
}

int stack_list_pop(stack_list* stack)
{
    if(stack->top == 0){
        printf("Error: cannot pop an empty stack\n");
    }
    stack->top--;
}

void stack_list_delete(stack_list* stack)
{
    free(stack->nums);
    free(stack->chars);
}
#endif