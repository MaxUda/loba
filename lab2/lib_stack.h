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

typedef struct
{
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
