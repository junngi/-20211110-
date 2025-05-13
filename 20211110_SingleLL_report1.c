#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 노드 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 리스트 출력 함수 (실습 1-4)
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 특정 값의 위치 찾기 (실습 1-5 - searchValue1)
int searchValue1(Node* head, int val) {
    int pos = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data == val) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

// 특정 값 앞뒤 노드 출력 (실습 1-5 - searchValue2)
void searchValue2(Node* head, int val) {
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (current->data == val) {
            if (prev != NULL) {
                printf("앞 노드 값: %d\n", prev->data);
            } else {
                printf("앞 노드 없음\n");
            }

            if (current->next != NULL) {
                printf("뒤 노드 값: %d\n", current->next->data);
            } else {
                printf("뒤 노드 없음\n");
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("값 %d을(를) 찾을 수 없습니다.\n", val);
}

// 메모리 해제 함수 (실습 1-5 - freeList)
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 테스트용 main 함수
int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    Node* second = (Node*)malloc(sizeof(Node));
    Node* third = (Node*)malloc(sizeof(Node));
    Node* fourth = (Node*)malloc(sizeof(Node));

    head->data = 10;
    head->next = second;
    second->data = 20;
    second->next = third;
    third->data = 30;
    third->next = fourth;
    fourth->data = 40;
    fourth->next = NULL;

    printf("리스트 출력:\n");
    printList(head);

    int val = 30;
    int pos = searchValue1(head, val);
    printf("%d의 위치는 %d번째\n", val, pos);

    printf("%d의 앞뒤 노드:\n", val);
    searchValue2(head, val);

    freeList(head);
    return 0;
}
