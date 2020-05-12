#include<stdio.h>
#include<stdlib.h>

//정수들의 이중 연결 리스트 생성을 위한 구조체
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); //listNode h에 직접 메모리 할당
int freeList(listNode* h); //listNode포인터 h 메모리 해제
int insertLast(listNode* h, int key); //list에 key에 대한 노드하나를 추가
int deleteLast(listNode* h); //list의 마지막 노드 삭제
int insertFirst(listNode* h, int key); //list 처음에 key에 대한 노드하나를 추가
int deleteFirst(listNode* h); //list의 첫번째 노드 삭제
int invertList(listNode* h); //리스트의 링크를 역순으로 재 배치

int insertNode(listNode* h, int key); //리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
int deleteNode(listNode* h, int key); //list의 key에 대한 노드 삭제

void printList(listNode* h); //리스트의 노드들을 출력


int main()
{
	char command;
	int key;
	listNode* headnode=NULL; //listNode형 포인터 구조체 headnode선언

    printf("------[Na Kyu Tae]-----[2017038073]------\n"); //이름과 학번 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
		//z나 Z가 입력될 경우 headnode에 직접 메모리 할당
		case 'z': case 'Z':
			initialize(&headnode);
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
		//q나 Q가 입력될 경우 headnode 메모리 해제
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


//listNode h에 직접 메모리 할당
int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	
	free(h); //listNode포인터 h에 저장되어있는 메모리 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//헤더노드에 들어있는 값이 없으면 프린트 할 것이 아무것도 없습니다란 문장 출력
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p에 헤더노드의 rlink가 가리키는 값 대입

	//원형 linked list에 들어있는 key의 내용 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* 주소 출력 */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink; //p에 헤더노드의 rlink가 가리키는 값 대입
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key = key; //입력받은 key를 node의 key에 대입
	node->rlink=NULL; //node의 rlink가 가리키는 값에 NULL대입
    node->llink=NULL; //node의 llink가 가리키는 값에 NULL대입
	
	node->rlink = h; //node의 rlink가 가리키는 값에 헤더노드 대입
	node->llink=h->llink; //node의 llink가 가리키는 값에 헤더노드의 llink가 가리키는 값 대입
	h->llink->rlink=node; //헤더노드의 llink가 가리키는 값의 rlink가 가리키는 값에 node 대입
	h->llink=node; //헤더노드의 llink가 가리키는 값에 node 대입

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h; //listnode형 포인터 p에 헤더노드 대입

	if(h->llink==h) //헤더노드의 llink가 가리키는 값이 헤더노드이면 지울게 없다는 문장 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	temp=p->llink; //temp에 p의 llink가 가리키는 값 대입
	p=p->llink; //p에 p의 llink가 가리키는 값 대입

	p->llink->rlink=h; //p의 llink가 가리키는 값의 rlink가 가리키는 값에 헤더노드 대입
	h->llink=p->llink; //헤더노드의 llink가 가리키는 값에 p의 llink가 가리키는 값 대입

	free(temp); //p의 llink가 가리키는 값이 대입된 temp 메모리 해제(삭제)
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key = key; //입력받은 key를 node의 key에 대입
    node->rlink=NULL; //node의 rlink가 가리키는 값에 NULL대입
    node->llink=NULL; //node의 llink가 가리키는 값에 NULL대입

	node->rlink=h->rlink; //node의 rlink가 가리키는 값에 헤더노드의 rlink가 가리키는값 대입
	node->llink=h; //node의 llink가 가리키는값에 헤더노드 대입
	h->rlink->llink=node; //헤더노드의 rlink가 가리키는 값의 llink가 가리키는 값에 node 대입
	h->rlink=node; //헤더노드의 rlink가 가리키는 값에 node대입
	
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
 	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h; //listnode형 포인터 p에 헤더노드 대입

	if(h->rlink==h) //헤더노드의 rlink가 가리키는 값이 헤더노드면 지울게 없다는 문장 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	temp=p->rlink; //temp에 p의 rlink가 가리키는 값 대입
	p=p->rlink; //p에 p의 rlink가 가리키는 값 대입

	p->rlink->llink=h; //p의 rlink가 가리키는 값의 llink가 가리키는 값에 헤더노드 대입
	h->rlink=p->rlink; //헤더노드의 rlink가 가리키는 값에 p의 rlink가 가리키는 값 대입

	free(temp); //첫번째 노드의 값이 들어있는 temp 메모리 해제(삭제)

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* p = h; //listnode형 포인터 p에 헤더노드 대입
	listNode* trail = NULL; //listnode형 포인터 trail에 NULL 대입
	listNode* middle = NULL; //listnode형 포인터 middle에 NULL 대입

	if(h->rlink==h) //헤더노드의 rlink가 가리키는 값이 헤더노드이면 역순할게 없다는 문장 출력
	{
		printf("nothing to invert...\n");
		return 0;
	}

	while(1) //break가 나올때까지 반복
	{
		trail=middle; //trail에 middle값 대입
		middle = p; //middle에 p값 대입
		p = p->rlink; //p에 p의 rlink가 가리키는 값 대입
		middle->llink = p; //middle의 llink가 가리키는 값에 p대입
		middle->rlink=trail; //middle의 rlink가 가리키는 값에 trail대입
		if(p==h) //p가 헤더노드 이면 p의 rlink가 가리키는 값에 middle값을 대입한 후 break
		{
			p->rlink=middle;
			break;
		}
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode형 포인터 node 메모리 할당
	node->key=key; //입력받은 key를 node의 key에 대입
	node->rlink=NULL; //node의 rlink가 가리키는 값에 NULL대입
    node->llink=NULL; //node의 llink가 가리키는 값에 NULL대입

	listNode* p=h; //listnode형 포인터 p에 헤더노드 대입

	while(1) //break를 만날때까지 무한반복
	{
		p=p->rlink; //p에 p의 rlink가 가리키는 값 대입

		if(p==h) //p가 헤더노드일 경우
		{
			node->rlink=h; //node의 rlink가 가리키는 값에 헤더노드 대입
			node->llink=h; //node의 llink가 가리키는 값에 헤더노드 대입
			h->llink=node; //헤더노드의 llink가 가리키는 값에 node대입
			h->rlink=node; //헤더노드의 rlink가 가리키는 값에 node대입 후 break
			break;
		}

		else if(p->key >= node->key) //p의 키값이 node의 키값보다 크거나 같을경우
		{
			node->rlink=p; //node의 rlink가 가리키는 값에 p대입
			node->llink=p->llink; //node의 llink가 가리키는 값에 p의 llink가 가리키는 값 대입
			p->llink->rlink=node; //p의 llink가 가리키는 값의 rlink가 가리키는 값에 node 대입
			p->llink=node; //p의 llink가 가리키는 값에 node 대입 후 break
			break;
		}

		else if(p->rlink==h) //p의 rlink가 가리키는 값이 헤더노드라면
		{
			node->llink=p; //node의 llink가 가리키는 값에 p대입
			node->rlink=p->rlink; //node의 rlink가 가리키는 값에 p의 rlink가 가리키는 값 대입
			p->rlink->llink=node; //p의 rlink가 가리키는 값의 llink가 가리키는 값에 node 대입
			p->rlink=node; //p의 rlink가 가리키는 값에 node 대입 후 break
			break;
		}
	}

	return 0;
}


/**
 * list의 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* temp=(listNode*)malloc(sizeof(listNode)); //listnode형 포인터 temp 메모리 할당
	listNode* p = h; //listnode형 포인터 p에 헤더노드 대입

	if(h->rlink==h) //헤더노드의 rlink가 가리키는 값이 헤더노드이면
	{
		printf("cannot find the node for key = %d \n",key); //키를 찾을수 없다는 문장 출력
		return 1;
	}


	while(1) //break가 나올때까지 무한반복
	{
		p=p->rlink; //p에 p의 rlink가 가리키는 값 대입

		if(p->key==key) //p의 key값이 입력한 key의 값과 같을 경우
		{
			temp=p; //temp에 p값 대입
			p->llink->rlink=p->rlink; //p의 llink가 가리키는 값의 rlink가 가리키는 값에 p의 rlink가 가리키는 값 대입
			p->rlink->llink=p->llink; //p의 rlink가 가리키는 값의 llink가 가리키는 값에 p의 llink가 가리키는 값 대입

			free(temp); //p의 값이 대입된 temp의 메모리 해제(삭제) 후 break

            break;
		}

		else if(p->rlink==h) //p의 rlink가 가리키는 값이 헤더노드일경우
		{
			printf("cannot find the node for key = %d \n",key); //키를 찾을수 없다는 문장 출력후 break
			break;
		}
		

	}

	return 0;
}