#include<stdio.h>
#include<stdlib.h>

void main()
{
    int **x; //이중포인터 변수 x 선언(int형)

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    printf("sizeof(x) = %lu\n",sizeof(x)); //x의 사이즈 값 출력
    printf("sizeof(*x) = %lu\n",sizeof(*x)); //*x의 사이즈 값 출력
    printf("sizeof(**x) = %lu\n",sizeof(**x)); //**x의 사이즈 값 출력

}
