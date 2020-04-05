#include<stdio.h>
#include<stdlib.h>

void main()
{
    int list[5]; //list문자열 배열 선언
    int *plist[5]; //plist 포인터 문자열 배열 선언

    list[0] = 10; //list[0]에 10 대입
    list[1] = 11; //list[1]에 11 대입

    plist[0] = (int*)malloc(sizeof(int)); //plist[0]에 4bytes의 메모리 할당

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    printf("list[0] \t= %d\n", list[0]); //list[0]의 값 출력
    printf("address of list \t= %p\n",list); //list의 주소값 출력
    printf("address of list[0] \t= %p\n", &list[0]); //list[0]의 주소값 출력
    printf("address of list + 0 \t= %p\n", list+0); //list+0의 주소값 출력
    printf("address of list + 1 \t= %p\n", list+1); //list+1의 주소값 출력
    printf("address of list + 2 \t= %p\n", list+2); //list+2의 주소값 출력
    printf("address of list + 3 \t= %p\n", list+3); //list+3의 주소값 출력
    printf("address of list + 4 \t= %p\n", list+4); //list+4의 주소값 출력
    printf("address of list[4] \t= %p\n", &list[4]); //list[4]의 주소값 출력

    free(plist[0]); //plist[0] 메모리 할당 해제
}