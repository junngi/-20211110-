#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PHONE 20

typedef struct Contact {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    struct Contact* next;
} Contact;

// 새로운 노드 생성
Contact* createContact(const char* name, const char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;
    return newContact;
}

// 연락처 추가
void addContact(Contact** head, const char* name, const char* phone) {
    Contact* newContact = createContact(name, phone);
    newContact->next = *head;
    *head = newContact;
    printf("연락처 추가 완료: %s - %s\n", name, phone);
}

// 연락처 검색
void searchContact(Contact* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("검색 결과: %s - %s\n", head->name, head->phone);
            return;
        }
        head = head->next;
    }
    printf("'%s'의 연락처를 찾을 수 없습니다.\n", name);
}

// 연락처 삭제
void deleteContact(Contact** head, const char* name) {
    Contact* current = *head;
    Contact* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("'%s'의 연락처 삭제 완료.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s'의 연락처를 찾을 수 없습니다.\n", name);
}

// 전화번호부 전체 출력
void printContacts(Contact* head) {
    printf("현재 전화번호부:\n");
    while (head != NULL) {
        printf("%s - %s\n", head->name, head->phone);
        head = head->next;
    }
}

// 메모리 해제
void freeContacts(Contact* head) {
    Contact* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Contact* phoneBook = NULL;

    // 테스트 예시
    addContact(&phoneBook, "오해원", "010-1111-1234");
    addContact(&phoneBook, "김미연", "010-8765-4321");
    addContact(&phoneBook, "김준기", "010-5871-7410");

    printContacts(phoneBook);

    searchContact(phoneBook, "김미연");

    deleteContact(&phoneBook, "오해원");

    printContacts(phoneBook);

    freeContacts(phoneBook);
    return 0;
}
