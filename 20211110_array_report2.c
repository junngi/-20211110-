#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);
void deleteStudent(int scores[], int *size, int studentNumber);

int main(){
    int *scores;
    int size = 30;
    int capacity = 30;
    int choice, studentNumber;

    scores = (int *)malloc(capacity * sizeof(int));
    if(!scores){
        printf("allocation error\n");
        return 1;
    }

    srand(time(0));
    for(int i = 0; i < size; i++){
        scores[i] = rand() % 101;
    }
    printf("초기 학생 성적 입력 완료\n");

    while(1){
        system("clear");
        printf("학생 성적 관리 프로그램 ---\n");
        printf("1. 학생정보 추가\n");
        printf("2. 학생정보 삭제\n");
        printf("3. 학생정보 검색\n");
        printf("4. 학생정보 출력(옵션: 0, 1, 2)\n");
        printf("5. 프로그램 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
   
        switch(choice){
            case 1: {
                int addCount;
                printf("추가할 학생 수 입력: ");
                scanf("%d", &addCount);
                if(capacity - size < addCount){
                    capacity += (addCount > 10 ? addCount : 10);
                    int *newScores = realloc(scores, capacity * sizeof(int));
                    if(newScores == NULL){
                        printf("allocation error\n");
                        break;
                    }
                    scores = newScores;
                }
                for(int i = 0; i < addCount; i++){
                    int newScore = rand() % 101;
                    scores[size] = newScore;
                    size++;
                    printf("새로운 학생 추가: 번호 - %d, 점수 - %d\n", size, newScore);
                }
                break;
            }
            case 2: {
                printf("삭제할 학생 번호 입력 (1 ~ %d): ", size);
                scanf("%d", &studentNumber);
                deleteStudent(scores, &size, studentNumber);
                break;
            }
            case 3: {
                printf("검색할 학생 번호 입력 (1 ~ %d): ", size);
                scanf("%d", &studentNumber);
                int score = getStudentScore(scores, size, studentNumber);
                if(score != -1)
                    printf("%d번 학생의 점수: %d\n", studentNumber, score);
                else
                    printf("해당 학생은 없는 학생입니다.\n");
                break;
            }
            case 4: {
                int option;
                printf("출력 옵션 입력 (0: 모든 학생, 1: 평균 이상, 2: 평균 미만): ");
                scanf("%d", &option);
                double average = calculateAverage(scores, size);
                printf("학급 평균 점수: %.2f\n", average);
                printScore(scores, size, average, option);
                break;
            }
            case 5:
                free(scores);
                printf("프로그램 종료\n");
                return 0;
            default:
                printf("잘못된 입력입니다.\n");
                break;
        }
        printf("계속하려면 엔터 키를 누르세요...");
        getchar();
        getchar();
    }
    return 0;
}

double calculateAverage(int scores[], int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += scores[i];
    }
    return (double)sum / size;
}

int getStudentScore(int scores[], int size, int studentNumber){
    if(studentNumber < 1 || studentNumber > size)
        return -1;
    return scores[studentNumber - 1];
}

void printScore(int scores[], int size, double average, int option){
    for(int i = 0; i < size; i++){
        if(option == 0){
            printf("%2d번 학생: %3d점\n", i+1, scores[i]);
        }
        else if(option == 1){
            if(scores[i] >= average)
                printf("%2d번 학생: %3d점\n", i+1, scores[i]);
        }
        else if(option == 2){
            if(scores[i] < average)
                printf("%2d번 학생: %3d점\n", i+1, scores[i]);
        }
        else{
            printf("잘못된 옵션입니다.\n");
            break;
        }
    }
}

void deleteStudent(int scores[], int *size, int studentNumber){
    if(studentNumber < 1 || studentNumber > *size){
        printf("학생 번호 오류\n");
        return;
    }
    for(int i = studentNumber - 1; i < *size - 1; i++){
        scores[i] = scores[i + 1];
    }
    (*size)--;
    printf("%d번 학생 삭제 완료\n", studentNumber);
}
