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