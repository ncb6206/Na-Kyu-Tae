#include<stdio.h>

//padding을 증명하기 위한 student 구조체 선언
struct student {
    char lastName[13];  /* 13 bytes의 공간 차지 */
    int studentId;      /* 4 bytes의 공간 차지 */
    short grade;        /* 2 bytes의 공간 차지 */
};

int main()
{

    struct student pst; //student형 구조체 변수 pst 선언
    
    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    printf("size of student = %ld\n", sizeof(struct student)); //student 구조체의 사이즈 값 출력
    printf("size of int = %ld\n", sizeof(int)); //int의 사이즈값 출력
    printf("size of short = %ld\n", sizeof(short)); //short의 사이즈값 출력

    return 0;
}