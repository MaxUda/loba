#include <stdio.h>
#include <stdlib.h>

typedef struct list list;
struct list{
    list* next;
    char value;
    int num;
};

typedef struct{
    list* head;
}stack_list;

stack_list init_stack_list();
char stack_list_peek_char(stack_list* stack);
int stack_list_peek_int(stack_list* stack);
void stack_list_push(stack_list* stack, char value, int num);
int stack_list_pop(stack_list* stack);
void print_stack_list(stack_list* stack);
void stack_list_delete(stack_list* stack);

stack_list init_stack_list()
{
    stack_list new_stack = {.head = NULL};
    return new_stack;
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
//---------------------------------------------------------

typedef struct{
    int top, size;
    int* nums;
    char* chars;
}stack_vector;

stack_vector stack_vector_init(int size);
int stack_vector_peek_int(stack_vector* stack);
char stack_vector_peek_char(stack_vector* stack);
int stack_vector_push(stack_vector* stack,char ch, int num);
int stack_vector_pop(stack_vector* stack);
void stack_vector_delete(stack_vector* stack);

stack_vector stack_vector_init(int size){
    stack_vector new_stack = {.top = 0, .size = size, .nums = calloc(size, sizeof(int)), .chars = calloc(size, sizeof(char))};
    return new_stack;
}

int stack_vector_peek_int(stack_vector* stack)
{
    if(stack->top - 1 == 0){
        printf("Error: can not read from empty stack\n");
        //return -100000000;
    }
    return stack->nums[stack->top-1];
}

char stack_vector_peek_char(stack_vector* stack)
{
    if(stack->top - 1 == 0){
        printf("Error: can not read from empty stack\n");
        //return -100000000;
    }
    return stack->chars[stack->top-1];
}

int stack_vector_push(stack_vector* stack,char ch, int num)
{
    if(stack->top == stack->size){
        printf("Error: stack overflow\n");
        return 0;
    }
    stack->nums[stack->top] = num;
    stack->chars[stack->top] = num;
    stack->top++;
    return 1;
}

int stack_vector_pop(stack_vector* stack)
{
    if(stack->top == 0){
        printf("Error: cannot pop an empty stack\n");
    }
    stack->top--;
}

void stack_vector_delete(stack_vector* stack)
{
    free(stack->nums);
    free(stack->chars);
}


