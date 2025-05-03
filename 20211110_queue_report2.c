#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10  // 큐의 최대 크기

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

// 초기화
void initQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
}

// 비었는지 확인
bool isEmpty(PrintQueue *q) {
    return q->front == q->rear;
}

// 가득 찼는지 확인
bool isFull(PrintQueue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

// 작업 추가
bool enqueue(PrintQueue *q, const char *documentName, int numPages) {
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다.\n");
        return false;
    }
    if (numPages > 50) {
        printf("페이지 수가 50장을 초과하여 작업이 거부되었습니다.\n");
        return false;
    }

    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 삭제
PrintJob dequeue(PrintQueue *q) {
    PrintJob job = {"", 0};
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return job;
    }
    job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 특정 문서 삭제 (cancelJob)
bool cancelJob(PrintQueue *q, const char *name) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return false;
    }

    int i = q->front;
    int found = -1;
    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, name) == 0) {
            found = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return false;
    }

    // 한 칸씩 앞으로 이동
    while (found != q->rear) {
        int next = (found + 1) % SIZE;
        if (next == q->rear) break;
        q->queue[found] = q->queue[next];
        found = next;
    }
    q->rear = (q->rear - 1 + SIZE) % SIZE;
    printf("문서 '%s'가 대기열에서 취소되었습니다.\n", name);
    return true;
}

// 전체 초기화 (clearQueue)
void clearQueue(PrintQueue *q) {
    initQueue(q);
    printf("대기열 초기화 완료.\n");
}

// 현재 대기열 출력
void printQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업 목록:\n");
    int i = q->front;
    while (i != q->rear) {
        printf(" - %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char name[50];
    int pages;

    while (true) {
        printf("\n--- 프린터 대기열 메뉴 ---\n");
        printf("1. 작업 추가\n2. 작업 처리\n3. 특정 작업 취소\n4. 대기열 보기\n5. 전체 초기화\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                scanf("%s", name);
                printf("페이지 수: ");
                scanf("%d", &pages);
                enqueue(&q, name, pages);
                break;
            case 2: {
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지) 출력 중...\n", job.documentName, job.numPages);
                }
                break;
            }
            case 3:
                printf("취소할 문서 이름: ");
                scanf("%s", name);
                cancelJob(&q, name);
                break;
            case 4:
                printQueue(&q);
                break;
            case 5:
                clearQueue(&q);
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}
