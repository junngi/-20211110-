#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    char str[MAX];
    char *stack;
    int top = -1;

    printf("문자열 입력 : ");
    fgets(str, sizeof(str), stdin);
    
    // 개행문자 제거
    str[strcspn(str, "\n")] = '\0';

    int len = strlen(str);
    stack = (char *)malloc(sizeof(char) * len);

    if (stack == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    // push
    for (int i = 0; i < len; i++) {
        stack[++top] = str[i];
    }

    printf("거꾸로 출력 : ");
    // pop
    while (top != -1) {
        printf("%c", stack[top--]);
    }
    printf("\n");

    free(stack);  // 메모리 해제
    return 0;
}
