#include <stdio.h>
#include <stdlib.h>

//정수들의 이진 탐색 트리 생성을 위한 구조체
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* stack에 이용되는 정의 */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop(); //stack에 top에 있는 노드 pop
void push(Node* aNode); //stack에 aNode 삽입

/* queue에 이용되는 정의 */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue(); //Queue에 있는 노드 pop
void enQueue(Node* aNode); //Queue에 aNode 삽입


int initializeBST(Node** h); //헤드 노드 생성 및 트리에 값이 존재할시 트리에 할당된 모든 노드들 삭제

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursiv방식으로 중위 순회 */
void iterativeInorder(Node* ptr);     /* iterative방식으로 중위 순회 */
void levelOrder(Node* ptr);	          /* 레벨 순서 순회 */
int insert(Node* head, int key);      /* 트리에 노드 삽입 */
int deleteNode(Node* head, int key);  /* 트리에 있는 key 값을 가진 노드 삭제 */
int freeBST(Node* head); /* 트리에 할당된 전체 메모리 해제 */




int main()
{
	char command;
	int key;
	Node* head = NULL; //Node형 포인터 구조체 head선언

     printf("------[Na Kyu Tae]-----[2017038073]------"); //이름과 학번 출력
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //원하는 명령 입력

		switch(command) {
		//z나 Z가 입력될 경우 headnode에 직접 메모리 할당
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		//q나 Q가 입력될 경우 트리로부터 할당된 모든 노드들을 제거
		case 'q': case 'Q':
			freeBST(head);
			break;
		//i나 I가 입력될 경우 사용자가 key를 입력한 후 tree에 key에 대한 노드하나를 추가
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		//d나 D가 입력될 경우 사용자가 key를 입력한 후 key값을 가지는 노드를 삭제
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		//r이나 R이 입력될 경우 recursive방식의 중위순회 실시
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		//t이나 T가 입력될 경우 Iterative방식의 중위순회 실시
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		//l이나 L이 입력될 경우 레벨 순서 순회 실시
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		//그 이외의 값이 입력 될 경우 집중하라는 문구 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

//헤드 노드 생성 및 트리에 값이 존재할시 트리에 할당된 모든 노드들 삭제
int initializeBST(Node** h) {

	/* 만약에 트리가 비어있지 않을 경우, 트리에 할당된 모든 노드들 삭제(해제)*/
	if(*h != NULL)
		freeBST(*h);

	/* 헤드 노드 생성 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


/* recursive방식의 중위순회 */
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left); //ptr의 left가 가리키는 값을 매개변수로 받는 recursiveInorder함수 실행
		printf(" [%d] ", ptr->key); //ptr의 key값을 출력
		recursiveInorder(ptr->right); //ptr의 right가 가리키는 값을 매개변수로 받는 recursiveInorder함수 실행
	}
}

/* iterative방식으로 중위 순회 */
void iterativeInorder(Node* node)
{
	if(node==NULL) //루트가 존재하지 않으면 그냥 리턴
		return;
		
	while(1)
	{
		while(1)
		{
			if(node==NULL) //node의 값이 없으면 break
				break;
			
			push(node); //node를 스택에 삽입
			node=node->left; //node에 node의 left가 가리키는 노드 삽입
		}

		if(top!=-1) //top의 값이 -1이 아니면 node에 pop함수가 리턴한 값 대입
			node = pop();

		if(node==NULL) //모든 값을 다 출력했을경우 break
			break;

		printf(" [%d] ", node->key); //node의 키 값 출력
		node=node->right; //node에 node의 right가 가리키는 노드 삽입
	}
}

//stack에 top에 있는 노드 pop
Node* pop()
{
	Node* temp=stack[top]; //temp에 스택의 탑 위치에 있는 노드 대입
	top--; //top값에 1을 빼줌
	return temp; //temp 리턴
}

//stack에 aNode 삽입
void push(Node* aNode)
{
	++top; //top값에 1을 더함
	stack[top]=aNode; //스택의 탑 위치에 aNode 삽입
}

/* 레벨 순서 순회 */
void levelOrder(Node* ptr)
{
	if(ptr==NULL) //루트가 존재하지 않으면 그냥 리턴
		return;

	front=rear=0; //queue에서 사용할 front와 rear 변수 0으로 선언

	enQueue(ptr); //Queue에 ptr 삽입

	while(1)
	{
		ptr = deQueue(); //ptr에 queue의 front 자리에 있는 노드 대입

		if(ptr!=NULL) //ptr이 NULL이 아닐경우
		{
			printf(" [%d] ", ptr->key); //ptr의 키값 출력
			if(ptr->left!=NULL) //ptr의 left가 가리키는 곳에 노드가 있을경우 
				enQueue(ptr->left); //queue에 ptr의 left가 가리키는 노드 삽입
			if(ptr->right!=NULL) //ptr의 right가 가리키는 곳에 노드가 있을경우
				enQueue(ptr->right); //queue에 ptr의 right가 가리키는 노드 삽입
		}

		else //모든값을 출력했을 경우 break
			break;
	}
}

//Queue에 있는 노드 pop
Node* deQueue() 
{
	queue[front]=NULL; //queue의 front의 자리에 NULL 대입
	front+=1; //front에 1을 더함
	front=front%20; ///front의 값에 20 나눠준 값을 front에 대입
	return queue[front]; //queue의 front 자리에 있는 노드를 리턴
}

//Queue에 aNode 삽입
void enQueue(Node* aNode)
{
	rear+=1; //rear에 1을 더함
	rear=rear%20; //rear의 값에 20 나눠준 값을 rear에 대입
	queue[rear]=aNode; //queue의 rear의 자리에 aNode 대입
}

/* 트리에 노드 삽입 */
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left는 root다 */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* 원래있던 노드의 키값과 같은 키값이 입력되면 단지 리턴한다 */
		if(ptr->key == key) return 1;

		/* 자식노드로 계속 이동하면서, 부모노드를 사용해 부모를 계속 추적한다 */
		parentNode = ptr;

		/* key를 비교해, 현재 노드의 키보다 입력된 키의 값이 클경우
		 * 새로운 노드는 오른쪽 서브트리로 들어간다
		 * 작을경우는 왼쪽 서브트리로 들어간다
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* 새로운 노드를 부모노드와 연결시켜준다 */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/* 트리에 있는 key 값을 가진 노드 삭제 */
int deleteNode(Node* head, int key)
{
	Node* temp=(Node*)malloc(sizeof(Node)); //Node형 포인터 temp에 주소 할당
	Node* p=head; //Node형 포인터 p에 head 대입
	Node* prev=NULL; //Node형 포인터 prev에 NULL 대입
	Node* prev3=NULL; //Node형 포인터 prev3에 NULL 대입

	if(head->left ==NULL) //트리의 루트가 없을경우 key값을 가진 노드가 없다는 문장 출력
	{
		printf("the node [%d] is exist", key);
		return 1;
	}

	p=p->left; //p에 p의 left가 가리키는 노드 대입

	while(1)
	{
		if(p->key>key) //p의 key 값이 입력받은 key값보다 클 경우
		{
			if(p->left==NULL) //p의 left가 가리키는 값이 NULL일 경우
			{
				printf("the node [%d] is not exist", key); //찾는 key값이 없다는 문장 출력후 break
				break;
			}

			else //그 외에 경우
			{
				prev=p; //prev에 p대입
				p=p->left; //p에 p의 left가 가리키는 노드 대입
			}
		}

		else if(p->key<key) //p의 key 값이 입력받은 key값보다 작을 경우
		{
			if(p->right==NULL) //p의 right가 가리키는 값이 NULL일 경우
			{
				printf("the node [%d] is not exist", key); //찾는 key값이 없다는 문장 출력후 break
				break;
			}

			else //그 외에 경우
			{
				prev=p; //prev에 p대입
				p=p->right; //p에 p의 right가 가리키는 노드 대입
			} 
		}

		else if(p->key==key) //p의 key 값이 입력받은 key값과 같을 경우
		{
			temp=p; //temp에 p 대입

			//case1
			if(p->left==NULL&&p->right==NULL) //p의 left가 가리키는 값과 p이 right가 가리키는 값이 모두 NULL일 경우
			{
				if(p==head->left) //p값이 트리의 루트와 같을 경우
				{
					free(temp); //temp값을 해제
					head->left=NULL; //트리의 루트 값에 NULL대입 후 break
					break;
				}
				
				else if(prev->key>p->key) //prev의 key 값이 p의 key값보다 클 경우
				{
						if(prev->left->key==key) //prev의 left가 가리키는 key의 값이 입력받은 key값과 같을 경우
						{
							free(temp); //temp값을 해제
							prev->left=NULL; //prev의 left가 가리키는 값에 NULL대입 후 break
							break;
						}
				}

				else if(prev->key<p->key) //prev의 key 값이 p의 key값보다 작을 경우
				{
						if(prev->right->key==key) //prev의 right가 가리키는 key의 값이 입력받은 key값과 같을 경우
						{
							free(temp); //temp값을 해제
							prev->right=NULL; //prev의 right가 가리키는 값에 NULL대입 후 break
							break; 
						}
				}
			}
			
			//case2
			else if(p->left!=NULL&&p->right==NULL) //p의 left가 가리키는 값이 존재하고 p의 right가 가리키는 값이 존재하지 않을경우
			{
				if(p==head->left) //p가 루트일 경우
				{
					head->left=p->left; //루트에 p의 left가 가리키는 노드 대입
					free(temp); //temp값을 해제
					break;
				}

				if(prev->key>p->key) //prev의 key 값이 p의 key값보다 클 경우
				{
					prev->left=p->left; //prev의 left가 가리키는 값에 p의 left가 가리키는 값 대입
					free(temp); //temp값을 해제
					break; 
				}

				else if(prev->key<p->key) //prev의 key 값이 p의 key값보다 작을 경우
				{
					prev->right=p->left; //prev의 right가 가리키는 값에 p의 left가 가리키는 값 대입
					free(temp); //temp값을 해제
					break; 
				}
			}

			else if(p->left==NULL&&p->right!=NULL) //p의 right가 가리키는 값이 존재하고 p의 left가 가리키는 값이 존재하지 않을경우
			{
				if(p==head->left) //p의 값이 루트일 경우
				{
					head->left=p->right; //루트에 p의 right가 가리키는 노드 대입
					free(temp); //temp값을 해제
					break;
				}

				if(prev->key>p->key) //prev의 key 값이 p의 key값보다 클 경우
				{
					prev->left=p->right; //prev의 left가 가리키는 값에 p의 right가 가리키는 값 대입
					free(temp); //temp값을 해제
					break; 
				}

				else if(prev->key<p->key) //prev의 key 값이 p의 key값보다 작을 경우
				{
					prev->right=p->right; //prev의 right가 가리키는 값에 p의 right가 가리키는 값 대입
					free(temp); //temp값을 해제
					break; 
				}
			}

			//case3
			else if(p->left!=NULL&&p->right!=NULL) //p의 left가 가리키는 값과 p이 right가 가리키는 값이 모두 존재 할 경우
			{
				p=p->right; //p에 p의 right가 가리키는 값을 대입

				while(1)
				{
					if(p->left==NULL&&p->right==NULL) //p의 left가 가리키는 값과 p의 right가 가리키는 값이 둘다 NULL일 경우
					{
						if(temp==head->left) //temp의 값이 루트일 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=head->left->left; //p의 left가 가리키는 값에 루트의 left가 가리키는 값 대입
								head->left=p; //루트에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else //그 외에 경우
							{
								p->left=head->left->left; //p의 left가 가리키는 값에 루트의 left가 가리키는 값 대입
								p->right=head->left->right; //p의 right가 가리키는 값에 루트의 right가 가리키는 값 대입
								head->left=p; //루트값에 p 대입
								prev3->left=NULL; //prev3의 left가 가리키는 값에 NULL대입
								free(temp); //temp값 해제
								break;
							}
						}

						else if(prev->key>temp->key) //prev의 key값이 temp의 key값보다 클 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=prev->left->left; //p의 left가 가리키는 값에 prev의 left의 left가 가리키는 값 대입
								prev->left=p; //prev의 left가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else //그 외의 경우
							{
								p->left=prev->left->left; //p의 left가 가리키는 값에 prev의 left의 left가 가리키는 값 대입
								p->right=prev->left->right; //p의 right가 가리키는 값에 prev의 left의 right가 가리키는 값 대입
								prev3->left=NULL; //prev3의 left가 가리키는 값에 NULL대입
								prev->left=p; //prev의 left가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}
						}

						else if(prev->key<temp->key) //prev의 key값이 temp의 key값보다 작을 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=prev->right->left; //p의 left가 가리키는 값에 prev의 right의 right가 가리키는 값 대입
								prev->right=p; //prev의 right가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else //그 외의 경우
							{
								p->left=prev->right->left; //p의 left가 가리키는 값에 prev의 right의 left가 가리키는 값 대입
								p->right=prev->right->right; //p의 right가 가리키는 값에 prev의 right의 right가 가리키는 값 대입
								prev3->left=NULL; //prev3의 left가 가리키는 값에 NULL대입
								prev->right=p; //prev의 left가 가리키는 값에 p 대입
								free(temp); //temp값 해제
							}
							break;
						}
					}

					else if(p->left!=NULL&&p->right==NULL) //p의 left가 가리키는 값이 존재하고 p의 right가 가리키는 값이 존재하지 않을경우
					{			
						prev3=p; //prev3에 p 대입
						p=p->left; //p에 p의 left가 가리키는 값 대입
		
					}

					else if(p->left==NULL&&p->right!=NULL) //p의 right가 가리키는 값이 존재하고 p의 left가 가리키는 값이 존재하지 않을경우
					{
						if(temp==head->left) //temp값이 루트 일 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=head->left->left; //p의 left가 가리키는 값에 루트의 left가 가리키는 값 대입
								head->left=p; //루트 값에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else //그 외의 경우
							{
								p->left=head->left->left; //p의 left가 가리키는 값에 루트의 left가 가리키는 값 대입
								prev3->left=p->right; //prev3의 left가 가리키는 값에 p의 right가 가리키는 값 대입
								p->right=head->left->right; //p의 right가 가리키는 값에 루트의 right가 가리키는 값 대입
								head->left=p; //루트 값에 p 대입
								free(temp); //temp값 해제
								break;
							}
						}

						else if(prev->key>temp->key) //prev의 key값이 temp의 key값보다 클 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=prev->left->left; //p의 left가 가리키는 값에 prev의 left의 left가 가리키는 값 대입
								prev->left=p; //prev의 left가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else //그 외의 경우
							{
								p->left=prev->left->left; //p의 left가 가리키는 값에 prev의 left의 left가 가리키는 값 대입
								prev3->left=p->right; //prev3의 left가 가리키는 값에 p의 right가 가리키는 값 대입
								p->right=prev->left->right; //p의 right가 가리키는 값에 prev의 left의 right가 가리키는 값 대입
								prev->left=p; //prev의 left가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}
						}

						else if(prev->key<temp->key) //prev의 key값이 temp의 key값보다 작을 경우
						{
							if(prev3==NULL) //prev3의 값이 NULL일 경우
							{
								p->left=prev->right->left; //p의 left가 가리키는 값에 prev의 right의 left가 가리키는 값 대입
								prev->right=p; //prev의 right가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}

							else
							{							
								p->left=prev->right->left; //p의 left가 가리키는 값에 prev의 right의 left가 가리키는 값 대입
								prev3->left=p->right; //prev3의 left가 가리키는 값에 p의 right가 가리키는 값 대입
								p->right=prev->right->right; //p의 right가 가리키는 값에 prev의 right의 right가 가리키는 값 대입
								prev->right=p; //prev의 right가 가리키는 값에 p 대입
								free(temp); //temp값 해제
								break;
							}
						}
					}
					
					else if(p->left!=NULL&&p->right!=NULL) //p의 right가 가리키는 값과 p의 left가 가리키는 값이 둘 다 존재 할 경우
					{
						prev3=p; //prev3에 p 대입
						p=p->left; //p에 p의 left가 가리키는 값 대입
					}
				}
				break;
			}
		}
	}
	return 0;
}


//루트와 연결된 노드 삭제
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //ptr의 left가 가리키는 노드를 인자로 받는 freeNode함수 실행
		freeNode(ptr->right); //ptr의 right가 가리키는 노드를 인자로 받는 freeNode함수 실행
		free(ptr); //ptr 삭제
	}
}

 /* 트리에 할당된 전체 메모리 해제 */
int freeBST(Node* head)
{

	if(head->left == head) //head가 헤드노드일 경우 head 삭제
	{
		free(head);
		return 1;
	}

	Node* p = head->left; //p에 루트 대입

	freeNode(p); //freeNode함수를 이용해 루트와 연결된 노드 삭제

	free(head); //헤드노드 삭제
	return 1;
}
