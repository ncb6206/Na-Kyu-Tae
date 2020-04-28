#include<stdio.h>
#include<stdlib.h>

//정수들의 연결 리스트 생성을 위한 구조체
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

//정수들의 연결 리스트의 헤더노드를 위한 구조체
typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //headNode에 메모리 할당
int freeList(headNode* h); //h와 연결된 listNode 와 headNode 메모리 해제

int insertFirst(headNode* h, int key); //list 처음에 key에 대한 노드하나를 추가
int insertNode(headNode* h, int key); //리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
int insertLast(headNode* h, int key); //list에 key에 대한 노드하나를 추가

int deleteFirst(headNode* h); //list의 첫번째 노드 삭제
int deleteNode(headNode* h, int key); //list의 key에 대한 노드 삭제
int deleteLast(headNode* h); //list의 마지막 노드 삭제
int invertList(headNode* h); //리스트의 링크를 역순으로 재 배치

void printList(headNode* h); //리스트의 노드들을 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL; //headNode형 포인터 구조체 headnode선언

	printf("------[Na Kyu Tae]-----[2017038073]------\n"); //이름과 학번 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //원하는 명령 입력

		switch(command) {
		//z나 Z가 입력될 경우 headnode에 메모리 할당
		case 'z': case 'Z': 
			headnode = initialize(headnode);
			break;
		//p나 P가 입력될 경우 리스트의 노드들을 출력
		case 'p': case 'P': 
			printList(headnode);
			break;
		//i나 I가 입력될 경우 사용자가 key를 입력한 후 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
		case 'i': case 'I': 
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		//d나 D가 입력될 경우 사용자가 key를 입력한 후 list의 key에 대한 노드 삭제
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		//n이나 N이 입력될 경우 사용자가 key를 입력한 후 list에 key에 대한 노드하나를 추가
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		//e나 E가 입력될 경우 list의 마지막 노드 삭제
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		//f나 F가 입력될 경우 사용자가 key를 입력한 후 list 처음에 key에 대한 노드하나를 추가
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		//t나 T가 입력될 경우 list의 첫번째 노드 삭제
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		//r이나 R이 입력될 경우 리스트의 링크를 역순으로 재 배치
		case 'r': case 'R':
			invertList(headnode);
			break;
		//q나 Q가 입력될 경우 h와 연결된 listNode 와 headNode 메모리 해제
		case 'q': case 'Q':
			freeList(headnode); 
			break;
		//그 이외의 값이 입력 될 경우 집중하라는 문구 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

//headNode에 메모리 할당
headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 전부 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//h와 연결된 listNode 와 headNode 메모리 해제
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key = key; //입력받은 key를 node의 key에 대입

	node->link = h->first; //node의 link가 가리키는 값에 헤더노드 대입
	h->first = node; //헤더노드에 node대입

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key=key; //입력받은 key를 node의 key에 대입
	node->link=NULL; //node의 link가 가리키는 값은 NULL

	listNode* p=h->first; //listnode형 포인터 p에 헤더노드 대입
	listNode* prev = NULL; //p의 값을 저장할 listnode형 포인터 prev 선언

	if(h->first==NULL) //헤더노드가 NULL일때  
	{
		node->link = h->first; //node의 link가 가리키는 값에 헤더노드 대입
		h->first = node; //헤더노드에 node 대입
		return 0;
	}

	else //헤더노드가 NULL이 아닐때
	{
		while(1) //break를 만날때까지 무한반복
		{
			prev=p; //prev에 p대입
			p=p->link; //p에 p의 link가 가리키는 값 대입

			if(prev->key >= node->key) //prev의 키값이 node의 키값보다 크거나 같을경우
			{
				node->link=h->first; //node의 link가 가리키는 값에 헤더노드 대입
				h->first=node; //헤더노드에 node 대입
				break;
			}

			else if(p==NULL) //p가 NULL일 경우
			{
				prev->link=node; //prev의 link가 가리키는 값에 node대입
				break;
			}

			else if(p->key >= node->key) //p의 키값이 node의 키값보다 크거나 같을경우
				{
					node->link=p; //node의 link가 가리키는 값에 p대입 
					prev->link=node; //prev의 link가 가리키는 값에 node대입
					break;
				}

		}
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key = key; //입력받은 key를 node의 key에 대입
	node->link = NULL; //node의 link가 가리키는 값은 NULL

	listNode* p = h->first; //listnode형 포인터 p에 헤더노드 대입

	if(h->first==NULL) //헤더노드가 NULL일때 
	{
		node->link = h->first; //node의 link가 가리키는 값에 헤더노드 대입
		h->first = node; //헤더노드에 node 대입
		return 0;
	}

	else //그 외에 경우
	{	
		while(p->link != NULL) //p의 link가 가리키는 값이 NULL이 될때까지 반복
		{
			p = p->link; //p에 p의 link가 가리키는 값 대입
		}
		p->link=node; //p의 link가 가리키는 값에 node 대입
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{
	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h->first; //listnode형 포인터 p에 헤더노드 대입

	temp=h->first; //temp에 헤더노드 대입
	p=p->link; //p에 p의 link가 가리키는 값 대입

	free(temp); //헤더노드가 대입된 temp 메모리 해제(삭제)
	h->first = p; //헤더노드에 p 대입

	return 0;
}

/**
 * list의 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h->first; //listnode형 포인터 p에 헤더노드 대입
	listNode* prev = NULL; //p의 값을 저장할 listnode형 포인터 prev 선언

	if(h->first==NULL) //헤더노드의 값이 NULL일때 키가 존재하지 않는다는 문장 출력
	{
		printf("key is not exist\n");
		return 0;
	}

	while(1) //break가 나올때까지 무한반복
	{
		prev=p; //prev에 p대입
		p=p->link; //p에 p의 link가 가리키는 값 대입

		if(prev->key == key) //prev의 key가 입력한 key의 값과 같을 경우
		{
			temp=prev; //temp에 prev대입
			free(temp); //prev의 값을 가지고 있는 temp 메모리 해제(삭제)
			h->first=p; //헤더노드에 p 대입
			break;
		}

		else if(prev->link==NULL) //prev의 link가 가리키는 값이 NULL일경우
		{
			printf("key is not exist\n"); //키가 존재하지 않는다는 문장 출력
			break;
		}

		else if(p->key==key) //p의 key값이 입력한 key의 값과 같을 경우
		{
			prev->link=p->link; //prev의 link가 가리키는 값에 p의 link가 가리키는 값 대입
			temp=p; //temp에 p 대입
			free(temp); //p의 값을 가지고 있는 temp 메모리 해제(삭제)
			break;
		}

		else if(p->link==NULL) //p의 link가 가리키는 값이 NULL일경우
		{
			printf("key is not exist\n"); //키가 존재하지 않는다는 문장 출력
			break;
		}
		

	}


	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h->first; //listnode형 포인터 p에 헤더노드 대입
	listNode* prev = NULL; //p의 값을 저장할 listnode형 포인터 prev 선언

	while(p->link!=NULL) //p의 link가 가리키는 값이 NULL이 될때까지 반복
	{
		prev=p; //prev에 p 대입
		p=p->link; //p에 p의 link가 가리키는 값 대입
	}

	temp=p; //temp에 p 대입
	free(temp); //p가 대입된 temp 메모리 해제(삭제)
	prev->link=NULL; //prev의 link가 가리키는 값을 NULL로 대입

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	
	listNode* p=h->first; //listnode형 포인터 p에 헤더노드 대입
	listNode* middle=NULL; //p의 값을 받을 listnode형 포인터 middle 선언
	listNode* trail=NULL; //middle의 값을 받을 listnode형 포인터 trail 선언

	while(p!=NULL) //p값이 NULL이 될때까지 반복
	{
		trail=middle; //trail에 middle대입
		middle=p; //middle에 p대입
		p=p->link; //p에 p의link가 가리키는 값 대입
		middle->link=trail; //middle의link가 가리키는 값에 trail 대입
	}
	h->first=middle; //헤더노드에 middle 대입

	return 0;
}

//리스트의 노드들을 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//headNode h에 들어있는 값이 없으면 프린트 할 것이 아무것도 없습니다란 문장 출력
	if(h == NULL) { 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //listNode *p에 h->first값 대입

	//p->key의 값을 출력한 뒤 p를 p->link값으로 변경하는 것을 p의 값이 NULL이 될 때까지 반복
	while(p != NULL) { 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}