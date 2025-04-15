#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 30  // 큐 크기 30

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} LinearQueue;

// 큐 초기화
void initQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;
}

// 큐 비었는지 확인
bool isEmpty(LinearQueue *q) {
    return q->rear < q->front;
}

// 큐 가득 찼는지 확인
bool isFull(LinearQueue *q) {
    return q->rear == SIZE - 1;
}

// 삽입
bool enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다.\n");
        return false;
    }
    q->data[++(q->rear)] = value;
    printf("%d 삽입 완료\n", value);
    return true;
}

// 삭제
int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있어 초기화합니다.\n");
        initQueue(q);
        return -1;
    }
    int value = q->data[q->front];
    q->front++;
    return value;
}

// 큐 상태 출력
void printQueue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("큐 상태: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    LinearQueue q;
    initQueue(&q);

    int choice, value;

    while (1) {
        printf("\n=== 메뉴 ===\n");
        printf("1. 삽입\n");
        printf("2. 삭제\n");
        printf("3. 큐 상태 출력\n");
        printf("4. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 값 입력: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                value = dequeue(&q);
                if (value != -1)
                    printf("삭제된 값: %d\n", value);
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                exit(0);
            default:
                printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}
