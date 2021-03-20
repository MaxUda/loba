#include <stdio.h>
#include <stdlib.h>
#include "lib_stack.h"

int stack_list_pick_out_num(stack_list* stack);

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
    printf("Error: invalid input\n");
    return 0;
}

int fill_stack_list(stack_list* stack, int iter)//-------------s
{ //0 - код ошибки, 1 - всё хорошо 
    char c = ' ', *input = calloc(0, sizeof(int)), t;
    int length = 0;
    int was_sing = 0, were_two_nums = 0;
        while(c != EOF && c != '\n'){
            c = getchar();
            if(c == EOF || c == '\n'){
                break;
            }else{
                length++;
                input = realloc(input, sizeof(int)*length);
                input[length - 1] = c;
                if(check_char(c, &was_sing, &were_two_nums) == 0){
                    free(input);
                    return 0;
                }
            }
        }
        if(was_sing != 1 || were_two_nums < 2){
            printf("Error: invalid input (expected polish notation)\n");
            free(input);
        return 0;
        }
        init_stack_list(stack, length);
    for(int i = 0;i < length;i++){
        stack_list_push(stack, input[i], 0);
    }
    free(input);
    return length;
}

int work_with_stack(stack_list* stack, char command){//-------------s
    if(check_if_empty(stack) == 1)
        return-100000000;
    int num1 = stack_list_peek_int(stack);//-------------s
    int ch1 = stack_list_pop(stack);//-------------s
    if(check_if_empty(stack) == 1)
        return-100000000;
    int num2 = stack_list_peek_int(stack);//-------------s
    int ch2 = stack_list_pop(stack);//-------------s
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
            printf("Не подвергайся искушению!\n");
            return -100000000;
        }
        res = num1 / num2;
    }
    return res;
}

int stack_list_count_prefix(stack_list* stack, int size)//-100000000 - error code//-------------s
{
    stack_list tmp;
    init_stack_list(&tmp, size);//-------------s
    while(check_if_empty(stack) == 0){
        if(stack_list_peek_char(stack) >= 48 && stack_list_peek_char(stack) <= 57){//-------------s
            int num = stack_list_pick_out_num(stack);//-------------s
            stack_list_push(&tmp, ' ', num);//-------------s
        }
        if(stack_list_peek_char(stack) == '+' || stack_list_peek_char(stack) == '-' || stack_list_peek_char(stack) == '*' ||stack_list_peek_char(stack) == '/' ){
            int res = work_with_stack(&tmp, stack_list_peek_char(stack));//-------------s
    if(res <= -100000000){
                printf("Error: expected prefix notation\n");
        stack_list_delete(&tmp);
                return -100000000;
            }
            stack_list_push(&tmp, ' ', res);//-------------s
            stack_list_pop(stack);//-------------s
        }
        if(check_if_empty(stack) == 1)
            break;
        if(stack_list_peek_char(stack) == ' '){//-------------s
            stack_list_pop(stack);//-------------s
        }
    }
    int result = stack_list_peek_int(&tmp);
    stack_list_pop(&tmp);
    if(check_if_empty(&tmp) == 0 || check_if_empty(stack) == 0){
        printf("Error: expected prefix notation\n");
    stack_list_delete(&tmp);
        return -100000000;
    }
    stack_list_delete(&tmp);//-------------s
    return result;
}

int stack_list_pick_out_num(stack_list* stack){//-------------s
    int num = 0, mult = 1;
    //printf("%c\n", stack_list_peek(stack));
    while(stack_list_peek_char(stack) >= 48 && stack_list_peek_char(stack) <= 57){//-------------s
        num += (stack_list_peek_char(stack) - 48)*mult;//-------------s
        mult *= 10;
        stack_list_pop(stack);//-------------s
        if(check_if_empty(stack) == 1)
            break;
    }
    return num;
}

int stack_list_menu()
{
    int iter = 1;
    while(1){
        printf("Enter expression:\n");
        //stack_list stack = init_stack_list();//-------------s
        stack_list stack;
        int result = fill_stack_list(&stack, iter);//-------------s
        if(result == 0){
            continue;
        }
        int res = stack_list_count_prefix(&stack, result);//-------------s
        if(res == -100000000){
            printf("Another round? y/n\n");
        }else{
            printf("Result: %d\n", res);
            printf("Another round? y/n\n");
        }
        stack_list_delete(&stack);//-------------s
        char command;
        while(scanf(" %c", &command) != 1 || (command != 'y' && command != 'n')){
            printf("Error:invalid input, try again\n");
        }
        if(command == 'n')
            break;
        iter++;
    }
}

int main()
{
    stack_list_menu();
    return 0;
}