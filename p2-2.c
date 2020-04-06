#include<stdio.h>

void print1 (int *ptr, int rows); //print1 함수 선언

int main()
{
    int one[] = {0, 1, 2, 3, 4}; //one 배열의 원소의 값 대입

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    
    printf("one     = %p\n", one); //one의 값 출력
    printf("&one    = %p\n", &one); //one의 주소값 출력
    printf("&one[0] = %p\n", &one[0]); //one[0]의 주소값 출력
    printf("\n");

    print1(&one[0], 5); //one[0]~one[4]까지의 주소값과 값 출력

    return 0;
}

void print1 (int *ptr, int rows)
{/* ptr이 가리키는 주소의 포인터 배열의 0~rows-1 까지의 주소와 주소가 가리키는 포인터 값 출력 */

    int i; //지역변수 i 선언
    printf ("Address \t Contents\n"); //Address Contents 출력
    for(i = 0; i < rows; i++)
        printf("%p \t  %5d\n", ptr + i, *(ptr + i)); 
    printf("\n");
}