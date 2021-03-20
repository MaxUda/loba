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
#elif VECTOR
typedef struct
{
    int top, size;
    int* nums;
    char* chars;
}stack_list;
#endif

void init_stack_list(stack_list* stack, int size);
char stack_list_peek_char(stack_list* stack);
int stack_list_peek_int(stack_list* stack);
void stack_list_push(stack_list* stack, char value, int num);
int stack_list_pop(stack_list* stack);
void print_stack_list(stack_list* stack);
void stack_list_delete(stack_list* stack);
int check_if_empty(stack_list* stack);