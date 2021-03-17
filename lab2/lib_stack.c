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
int fill_stack_list(stack_list* stack, int iter);
void stack_list_delete(stack_list* stack);
int check_char(char c, int* was_sing, int* were_two_nums);
int stack_list_pick_out_num(stack_list* stack);
int stack_list_count_prefix(stack_list* stack);
int stack_list_menu();

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
//---------------------------------------------------------

int check_char(char ch, int* was_sing, int* were_two_nums)
{
    if(ch == 42 || ch == 43 || ch == 47 || ch == 45){
        *was_sing = 1;
        return 1;
    }
    if(ch >= 48 && ch <= 57){
        (*were_two_nums)++;
        return 1;
    }
    if(ch == ' ')
        return 1;
    printf("Error: invalid input");
    return 0;
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

int fill_stack_list(stack_list* stack, int iter)
{ //0 - код ошибки, 1 - всё хорошо 
    char inp;
    int was_sing = 0, were_two_nums = 0;
    while(1){
        scanf("%c", &inp);
        if(inp == '\n'){
            break;
        }
        if(check_char(inp, &was_sing, &were_two_nums) == 0)
            return 0;
        stack_list_push(stack, inp, 0);
    }
    if(was_sing != 1 || were_two_nums < 2){
        printf("Error: invalid input (expected polish notation)");
        return 0;
    }
    return 1;
}

int work_with_stack(stack_list* stack, char command){
    if(stack->head == NULL)
        return-100000000;
    int num1 = stack_list_peek_int(stack);
    int ch1 = stack_list_pop(stack);
    if(stack->head == NULL)
        return-100000000;
    int num2 = stack_list_peek_int(stack);
    int ch2 = stack_list_pop(stack);
    if(ch1 == 0 || ch2 == 0){
        printf("Error: not prefix notation\n");
        return -100000000;
    }
    int res;
    if(command == '+'){
        res = num1 + num2;
    }else if(command == '-'){
        res = num1 - num2;
    }else if(command == '*'){
        res = num1 * num2;
    }else if(command == '/'){
        if(num2 == 0){
            printf("Ты идиот на 0 делить?\n");
            return -100000000;
        }
        res = num1 / num2;
    }
}

int stack_list_count_prefix(stack_list* stack)//-100000000 - error code
{
    stack_list tmp = init_stack_list();
    while(stack->head != NULL){
        if(stack_list_peek_char(stack) >= 48 && stack_list_peek_char(stack) <= 57){
            int num = stack_list_pick_out_num(stack);
            stack_list_push(&tmp, ' ', num);
        }
        if(stack_list_peek_char(stack) == '+' || stack_list_peek_char(stack) == '-' || stack_list_peek_char(stack) == '*' ||stack_list_peek_char(stack) == '/' ){
            int res = work_with_stack(&tmp, stack_list_peek_char(stack));
            if(res <= -100000000){
                printf("Error: expected prefix notation\n");
                return -100000000;
            }
            stack_list_push(&tmp, ' ', res);
            stack_list_pop(stack);
        }
        if(stack->head == NULL)
            break;
        if(stack_list_peek_char(stack) == ' '){
            stack_list_pop(stack);
        }
    }
    if(tmp.head->next != 0){
        printf("Error: expected prefix notation\n");
        return -100000000;
    }
    int result = stack_list_peek_int(&tmp);
    stack_list_delete(&tmp);
    return result;
}

int stack_list_pick_out_num(stack_list* stack){
    int num = 0, mult = 1;
    //printf("%c\n", stack_list_peek(stack));
    while(stack_list_peek_char(stack) >= 48 && stack_list_peek_char(stack) <= 57){
        num += (stack_list_peek_char(stack) - 48)*mult;
        mult *= 10;
        stack_list_pop(stack);
        if(stack->head == NULL)
            break;
    }
    return num;
}

int stack_list_menu()
{
    int iter = 1;
    while(1){
        printf("Enter expression:\n");
        stack_list stack = init_stack_list();
        int result = fill_stack_list(&stack, iter);
        if(result == 0){
            continue;
        }
        int res = stack_list_count_prefix(&stack);
        if(res == -100000000){
            printf("Another round? y/n\n");
        }else{
            printf("Result: %d\n", res);
            printf("Another round? y/n\n");
        }
        stack_list_delete(&stack);
        char ch;
        scanf("%c", &ch);
        if(ch == 'n')
            break;
        iter++;
    }
}



