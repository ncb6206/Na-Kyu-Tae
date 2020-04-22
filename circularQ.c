#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //queue의 크기를 4로 정의

typedef char element; //char형을 element로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; //QueueType 구조체 정의


QueueType* createQueue(); //원형큐를 동적할당하여 생성하는 함수
int isEmpty(QueueType* cQ); //원형큐가 비었다는 것을 확인하는 함수
int isFull(QueueType* cQ); //원형큐가 가득 찼다는 것을 확인하는 함수
void enQueue(QueueType* cQ, element item); //원형큐에 사용자에게 입력받은 문자를 넣는 함수
void deQueue(QueueType* cQ, element* item); //원형큐에 있는 문자를 먼저 입력받은 순서대로 빼버리는 함수 
void printQ(QueueType* cQ); //원형큐를 출력하는 함수
void debugQ(QueueType* cQ); //원형큐에 들어있는 값에 대한 정보와 front와 rear위치를 출력해주는 함수

element getElement();  //사용자에게서 문자를 입력받는 함수

int freeQueue(QueueType* cQ) //원형큐에 한 동적할당을 해제하는 함수
{
	if(cQ==NULL) //원형큐cQ에 아무것도 존재하지 않을경우 1리턴
		return 1;
	free(cQ); //원형큐cQ의 동적할당 메모리 해제

	return 1;
}

int main(void)
{
	QueueType* cQ = createQueue(); //QueueType 구조체 포인터 cQ에 동적할당한 원형큐 생성
	element data; //element형 data변수 선언

	char command; //사용자에게 입력받을 command변수 선언

	printf("[-----[Na Kyu Tae]   [2017038073]-----]\n"); //이름과 학번 출력
	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 command를 입력받음

		switch (command) {
		case 'i': case 'I': //i,I를 입력했을 경우 data에 입력받은 문자를 대입하고 원형큐에 삽입
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //d,D를 입력했을 경우 원형큐에 있는 먼저 입력받은 문자 삭제
			deQueue(cQ, &data);
			break;
		case 'p': case 'P': //p,P를 입력했을 경우 원형큐cQ 출력
			printQ(cQ);
			break;
		case 'b': case 'B': //b,B를 입력했을 경우 원형큐cQ를 디버그한 정보 출력
			debugQ(cQ);
			break;
		case 'q': case 'Q': //q,Q를 입력했을 경우 원형큐cQ를 동적할당 해제한 다음 프로그램 종료
			freeQueue(cQ);
			break;
		default: //이외에 문자를 입력했을경우 집중하라는 문자 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); //q,Q가 나올때까지 반복


	return 1;
}

//원형큐를 동적할당하여 생성하는 함수
QueueType* createQueue()
{
	QueueType* cQ; //QueueType형 구조체 포인터 cQ선언
	cQ = (QueueType*)malloc(sizeof(QueueType)); //cQ를 QueueType만큼 동적할당
	cQ->front = 0; 
	cQ->rear = 0;
	return cQ; //cQ 리턴
}

//사용자에게서 문자를 입력받는 함수
element getElement()
{
	element item; //element형 변수 item 선언
	printf("Input element = ");
	scanf(" %c", &item); //queue에 넣을 문자 입력
	return item; //item 리턴
}

//원형큐가 비었다는 것을 확인하는 함수
int isEmpty(QueueType* cQ)
{
	//cQ의 front와 rear의 값이 같을경우 원형큐가 비었다는 문장 출력후 1리턴
	if (cQ->front == cQ->rear) 
	{
		printf("circular queue is empty\n");
		return 1; 
	}
	else //그외의 경우 0리턴
		return 0;	
}

//원형큐가 가득 찼다는 것을 확인하는 함수
int isFull(QueueType* cQ)
{
	int rear; //가득 찼다는 것을 확인할 rear변수 선언

	rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //modulo연산을 사용해 rear에 대입
	//rear의 값과 cQ의 front값이 같을경우 원형큐가 가득 찼다는 문장 출력후 1리턴
	if ( rear == cQ->front) 
	{
		printf("circular queue is full\n");
		return 1;
	}
	else //그외의 경우 0리턴
		return 0;	
}

//원형큐에 사용자에게 입력받은 문자를 넣는 함수
void enQueue(QueueType* cQ, element item)
{
	if (isFull(cQ)==0) //원형큐cQ가 가득 차지 않았다면
	{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; ////modulo연산을 사용해 원형큐cQ의 rear에 대입
		cQ->queue[cQ->rear] = item; //원형큐cQ의 rear자리에 입력받은 문자를 삽입
	}
}

//원형큐에 있는 문자를 먼저 입력받은 순서대로 빼버리는 함수 
void deQueue(QueueType* cQ, element* item)
{
	if (isEmpty(cQ)==0) //원형큐cQ가 비어있지 않았다면
	{
		cQ->queue[cQ->front] = '\0'; //원형큐cQ의 front자리에 있는 값을 NULL로 만들어준다.
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //modulo연산을 사용해 원형큐cQ의 front에 대입
	}
}

//원형큐를 출력하는 함수
void printQ(QueueType* cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //modulo연산을 사용해 first에 대입
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //modulo연산을 사용해 last에 대입

	printf("Circular Queue : [");

	i = first; //i에 first대입
	while (i != last) //i가 last의 값과 같을때까지 원형큐에 들어있는 값을 출력
	{
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

//원형큐에 들어있는 값에 대한 정보와 front와 rear위치를 출력해주는 함수
void debugQ(QueueType* cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //i를 0부터 3까지 1씩 증가시킨다
	{
		//i의 값과 원형큐cQ의 front값이 같을경우 원형큐cQ의 i자리는 front라 출력후 계속 진행
		if (i == cQ->front) 
		{
			printf("  [%d] = front\n", i); 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //원형큐cQ의 i자리에 있는 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //원형큐cQ의 front와 rear위치 출력
}

