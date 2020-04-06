#include<stdio.h>
#include<stdlib.h>

void main()
{
    int list[5]; //문자열 배열 list 선언
    int *plist[5] = {NULL,}; //포인터 문자열 배열 plist 선언

    plist[0] = (int *)malloc(sizeof(int)); //plist[0]에 4bytes 메모리 할당

    list[0] = 1; //list[0]에 1 대입
    list[1] = 100; //list[1]에 100 대입

    *plist[0] = 200; //plist[0]이 가리키는 주소의 포인터 값에 200 대입

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    printf("value of list[0] = %d\n", list[0]); //list[0]의 값 출력
    printf("address of list[0]     = %p\n", &list[0]); //list[0]의 주소 출력
    printf("value of list          = %p\n", list); //list의 값 출력
    printf("address of list (&list)= %p\n", &list); //list의 주소 출력

    printf("------------------------------------\n\n"); 
    printf("value of list[i]   = %d\n",list[1]); //list[1]의 값 출력
    printf("address of list[1] = %p\n", &list[1]); //list[1]의 주소값 출력
    printf("value of *(list+1) = %d\n", *(list + 1)); //list+1이 가리키는 주소의 포인터값 출력
    printf("address of list+1 = %p\n", list+1); //list+1의 주소값 출력

    printf("------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]이 가리키는 주소의 포인터값 출력
    printf("&plist[0]          = %p\n", &plist[0]); //plist[0]의 주소값 출력
    printf("&plist             = %p\n", &plist); //plist의 주소값 출력
    printf("plist              = %p\n", plist); //plist의 값 출력
    printf("plist[0]           = %p\n", plist[0]); //plist[0]의 값 출력
    printf("plist[1]           = %p\n", plist[1]); //plist[1]의 값 출력
    printf("plist[2]           = %p\n", plist[2]); //plist[2]의 값 출력
    printf("plist[3]           = %p\n", plist[3]); //plist[3]의 값 출력
    printf("plist[4]           = %p\n", plist[4]); //plist[4]의 값 출력

}