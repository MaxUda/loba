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
int fill_stack_list(stack_list* stack);
void stack_list_delete(stack_list* stack);
int check_char(char c, int* was_sing, int* were_two_nums);
int stack_list_pick_out_num(stack_list* stack);
int stack_list_count_prefix(stack_list* stack);
int stack_list_menu();

