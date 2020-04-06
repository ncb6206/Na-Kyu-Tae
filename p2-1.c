#include<stdio.h>

#define MAX_SIZE 100 //MAX_SIZE의 값은 100으로 정의

float sum(float [], int); //배열의 원소의 합을 구하는 함수 sum 선언
//전역변수 선언
float input[MAX_SIZE], answer;
int i; 

void main(void)
{
    //input[0]~input[99]배열에 각각 0~99씩 차례대로 대입
    for(i=0; i < MAX_SIZE; i++)
        input[i] = i;

    printf("[----- [NA KYU TAE] [2017038073] -----]\n"); //이름과 학번 출력
    /* for checking call by reference */
    printf("address of input = %p\n", input); //input의 주소 출력

    answer = sum(input, MAX_SIZE); //input 배열의 전체 합을 answer에 대입
    printf("The sum is: %f\n", answer); //input 배열의 전체 합 출력
}

//list 배열 안에 있는 모든 원소들의 합을 구하는 함수 sum
float sum(float list[], int n)
{
    printf("value of list = %p\n", list); //list의 값 출력
    printf("address of list = %p\n\n", &list); //list의 주소값 출력

    int i; //지역변수 i 선언
    float tempsum = 0; //초기화
    //tempsum에 list배열의 전체 합 대입
    for(i=0; i < n; i++) 
        tempsum += list[i];
    return tempsum;
}