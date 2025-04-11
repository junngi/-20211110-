#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    char str[MAX];
    char *stack;
    int top = -1;

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);

    stack = (char *)malloc(sizeof(char) * MAX);
    if (stack == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            stack[++top] = str[i];  // push
        } else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (top == -1) {  // 스택이 비어있으면 오류
                printf("유효하지 않은 괄호\n");
                free(stack);
                return 0;
            }
            char open = stack[top--];  // pop
            if ((str[i] == ')' && open != '(') ||
                (str[i] == '}' && open != '{') ||
                (str[i] == ']' && open != '[')) {
                printf("유효하지 않은 괄호\n");
                free(stack);
                return 0;
            }
        }
    }

    if (top == -1)
        printf("유효한 괄호\n");
    else
        printf("유효하지 않은 괄호\n");

    free(stack);
    return 0;
}
