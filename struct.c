#include<stdio.h>

//student1 구조체 선언
struct student1 {
    char lastName; //이름
    int studentId; //학번
    char grade; //성적
};
//student2 구조체 선언(typedef사용)
typedef struct {
    char lastName; //이름
    int studentId; //학번
    char grade; //성적
} student2;

int main()
{
    struct student1 st1 = {'A', 100, 'A'}; //student1형의 변수 st1에 대한 초기화

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    printf("st1.lastName = %c\n", st1.lastName); //st1의 이름 출력
    printf("st1.studentId = %d\n", st1.studentId); //st1의 학번 출력
    printf("st1.grade = %c\n", st1.grade); //st1의 성적 출력

    student2 st2 = {'B', 200, 'B'}; //student2형의 변수 st2에 대한 초기화

    printf("\nst2.lastName = %c\n", st2.lastName); //st2의 이름 출력
    printf("st2.studentId = %d\n", st2.studentId); //st2의 학번 출력
    printf("st2.grade = %c\n", st2.grade); //st2의 성적 출력

    student2 st3; //student2형의 변수 st3 선언

    st3 = st2; //st3에 st2 대입

    printf("\nst3.lastName = %c\n", st3.lastName); //st3의 이름 출력
    printf("st3.studentId = %d\n", st3.studentId); //st3의 학번 출력
    printf("st3.grade = %c\n", st3.grade); //st3의 성적 출력

    /* 동일한 값인지에 대한 여부 확인
    if(st3 == st2) //st3와 st2의 값이 같으면
        printf("equal\n"); //같다 출력
    else //다르면
        printf("not equal\n"); //같지 않다 출력
    */
    return 0;    
}
