#include <stdio.h>
#include <stdlib.h>

//정수들의 이진 탐색 트리 생성을 위한 구조체
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); //headNode h에 직접 메모리 할당

void inorderTraversal(Node* ptr);	  /* recursive방식의 중위순회 */
void preorderTraversal(Node* ptr);    /* recursive방식의 전위순회 */
void postorderTraversal(Node* ptr);	  /* recursive방식의 후위순회 */
int insert(Node* head, int key);  /* tree에 노드 하나를 추가한다 */
int deleteLeafNode(Node* head, int key);  /* key값을 가지는 leaf 노드를 삭제한다 */
Node* searchRecursive(Node* ptr, int key);  /* Recursive방식으로 key값을 가지는 노드를 찾는다 */
Node* searchIterative(Node* head, int key);  /* Iterative방식으로 key값을 가지는 노드를 찾는다 */
int freeBST(Node* head); //트리로부터 할당된 모든 노드들의 메모리 제거


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* 찾은 노드의 주소를 저장하는 Node형 구조체포인터 ptr 선언 */

    printf("------[Na Kyu Tae]-----[2017038073]------"); //이름과 학번 출력
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		//n이나 N이 입력될 경우 사용자가 key를 입력한 후 tree에 key에 대한 노드하나를 추가
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		//d나 D가 입력될 경우 사용자가 key를 입력한 후 key값을 가지는 leaf 노드를 삭제
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		//f나 F가 입력될 경우 사용자가 key를 입력한 후 Iterative방식으로 key값을 가지는 노드를 찾는다
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL) //키값을 가진 노드가 있으면 그 노드의 주소 출력
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else //키값을 가진 노드가 없으면 키값을 가진 노드를 찾을수 없다는 문장 출력
				printf("\n Cannot find the node [%d]\n", key);
			break;
		//s나 S이 입력될 경우 사용자가 key를 입력한 후 Recursive방식으로 key값을 가지는 노드를 찾는다
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL) //키값을 가진 노드가 있으면 그 노드의 주소 출력
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else //키값을 가진 노드가 없으면 키값을 가진 노드를 찾을수 없다는 문장 출력
				printf("\n Cannot find the node [%d]\n", key);
			break;
		//i이나 I이 입력될 경우 recursive방식의 중위순회 실시
		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		//p나 P이 입력될 경우 recursive방식의 전위순회 실시
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		//t이나 T이 입력될 경우 recursive방식의 후위순회 실시
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		//그 이외의 값이 입력 될 경우 집중하라는 문구 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

int initializeBST(Node** h) {

	/* 만약 tree가 비어있지 않으면, 트리로부터 할당된 모든 노드들의 메모린 제거*/
	if(*h != NULL)
		freeBST(*h);

	/* head node를 만든다 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


/* recursive방식의 중위순회 */
void inorderTraversal(Node* ptr)
{
	if(ptr!=NULL) //ptr이 NULL이 아닐경우
	{
		inorderTraversal(ptr->left); //ptr의 left가 가리키는 값을 매개변수로 받는 inorderTraversal함수 실행
		printf("[%d]  ", ptr->key); //ptr의 key값을 출력
		inorderTraversal(ptr->right); //ptr의 right가 가리키는 값을 매개변수로 받는 inorderTraversal함수 실행
	}
}

/* recursive방식의 전위순회 */
void preorderTraversal(Node* ptr)
{
	if(ptr!=NULL) //ptr이 NULL이 아닐경우
	{
		printf("[%d]  ",ptr->key); //ptr의 key값을 출력
		preorderTraversal(ptr->left); //ptr의 left가 가리키는 값을 매개변수로 받는 preorderTraversal함수 실행
		preorderTraversal(ptr->right); //ptr의 right가 가리키는 값을 매개변수로 받는 preorderTraversal함수 실행
	}
}

/* recursive방식의 후위순회 */
void postorderTraversal(Node* ptr)
{
	if(ptr!=NULL) //ptr이 NULL이 아닐경우
	{
		postorderTraversal(ptr->left); //ptr의 left가 가리키는 값을 매개변수로 받는 postorderTraversal함수 실행
		postorderTraversal(ptr->right); //ptr의 right가 가리키는 값을 매개변수로 받는 postorderTraversal함수 실행
		printf("[%d]  ",ptr->key); //ptr의 key값을 출력
	}
}

// tree에 key값을 가지는 노드 하나를 추가한다. 만약, 같은 key값을 가진 노드가 존재하면 무시
int insert(Node* head, int key)
{
	Node* temp=(Node*)malloc(sizeof(Node)); //Node형 포인터 temp에 주소 할당
	Node* p=head; //Node형 포인터 p에 head 대입
	temp->key=key; //temp의 key값에 key 대입
	temp->left=temp->right=NULL; //temp의 left와 temp의 right가 가리키는 값에 NULL 대입

	if(head->left ==NULL) //트리의 루트가 없을경우 루트에 temp 대입
	{
		head->left=temp; 
		return 1;
	}

	p=p->left; //p에 p의 left가 가리키는 값 대입

	while(1)
	{
		if(p->key>temp->key) //p의 key값이 temp의 key값보다 클 경우
		{
			if(p->left==NULL) //p의 left값이 NULL일 경우 p의 left에 temp 대입 후 break
			{
				p->left=temp;
				break;
			}

			else //그 외에 경우 p에 p의 left값 대입
				p=p->left;
		}

		else if(p->key<temp->key) //p의 key값이 temp의 key값보다 작을 경우
		{
			if(p->right==NULL) //p의 right값이 NULL일 경우 p의 right에 temp 대입 후 break
			{
				p->right=temp;
				break;
			}

			else //그 외에 경우 p에 p의 right값 대입
				p=p->right;
		}

		else if(p->key==temp->key) //p의 key값이 temp의 key값이 같을 경우 아무것도 실행안하고 break
			break;
	}
}

/* key값을 가지는 leaf 노드를 삭제한다 */
int deleteLeafNode(Node* head, int key)
{
	Node* temp=(Node*)malloc(sizeof(Node)); //Node형 포인터 temp에 주소 할당
	Node* p=head; //Node형 포인터 p에 head 대입
	Node* prev=NULL; //Node형 포인터 prev에 NULL 대입

	if(head->left ==NULL) //트리의 루트가 없을경우 leaf 노드에 찾는 key값이 없다는 문장 출력
	{
		printf("the node [%d] is exist", key);
		return 1;
	}

	p=p->left; //p에 p의 left가 가리키는 값 대입

	while(1)
	{
		if(p->key>key) //p의 key 값이 입력받은 key값보다 클 경우
		{
			if(p->left==NULL) //p의 left가 가리키는 값이 NULL일 경우
			{
					printf("the node [%d] is not exist", key); //leaf노드에 찾는 key값이 없다는 문장 출력후 break
					break;
			}

			else //그 외에 경우
			{
				prev=p; //prev에 p대입
				p=p->left; //p에 p의 left가 가리키는 값 대입
			}
		}

		else if(p->key<key) //p의 key 값이 입력받은 key값보다 클 경우
		{
			if(p->right==NULL) //p의 right가 가리키는 값이 NULL일 경우
			{
				printf("the node [%d] is not exist", key); //leaf노드에 찾는 key값이 없다는 문장 출력후 break
				break;
			}

			else //그 외에 경우
			{
				prev=p; //prev에 p대입
				p=p->right; //p에 p의 right가 가리키는 값 대입
			} 
		}

		else if(p->key==key) //p의 key 값이 입력받은 key값보다 같을 경우
		{
			temp=p; //temp에 p 대입

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

			else //그 외에 경우 leaf노드에 찾는 key값이 없다는 문장 출력후 break
			{
				printf("the node [%d] is not a leaf", key);
				break;
			}

		}
	}
	return 0;
}

/* Recursive방식으로 key값을 가지는 노드를 찾는다 */
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr!=NULL) //ptr이 NULL이 아닐경우
	{
		if(ptr->key>key) //ptr의 key값이 입력받은 key값보다 클 경우
			searchRecursive(ptr->left,key); //ptr의 left가 가리키는 값과 key를 매개변수로 받는 searchRecursive함수 실행
		else if(ptr->key<key) //ptr의 key값이 입력받은 key값보다 작을 경우
			searchRecursive(ptr->right,key); //ptr의 right가 가리키는 값과 key를 매개변수로 받는 searchRecursive함수 실행
		else if(ptr->key==key) //ptr의 key값이 입력받은 key값보다 같을 경우
			return ptr; //ptr값 리턴
	}

	else //그 외에 경우 NULL을 리턴 
		return NULL;
}

/* Iterative방식으로 key값을 가지는 노드를 찾는다 */
Node* searchIterative(Node* head, int key)
{
	Node* p=head; //Node형 포인터 p에 head 대입

	if(head->left ==NULL) //트리의 루트가 없으면 NULL 리턴
		return NULL;

	p=p->left; //p에 p의 left가 가리키는 값 대입

	while(1)
	{
		if(p->key>key) //p의 key값이 입력받은 key보다 클 경우
		{
			if(p->left==NULL) //p의 left가 가리키는 값이 NULL일 경우 NULL을 리턴한 후 break
			{
				return NULL; 
				break;
			}
			else //그 외에 경우 p에 p의 left가 가리키는 값 대입
				p=p->left;
		}

		else if(p->key<key) //p의 key값이 입력받은 key보다 작을 경우
		{
			if(p->right==NULL) //p의 right가 가리키는 값이 NULL일 경우 NULL을 리턴한 후 break
			{
				return NULL;
				break;
			}
			else //그 외에 경우 p에 p의 right가 가리키는 값 대입
				p=p->right;
		}

		else if(p->key==key) //p의 key값이 입력받은 key보다 같을 경우 p를 리턴 후 break
		{
			return p;
			break;
		}
	}
}

//트리로부터 할당된 모든 노드들의 메모리 제거
int freeBST(Node* head)
{
    free(head);
}





