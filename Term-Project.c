#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20   /* you can change value 20 */ 
#define FALSE 0
#define TRUE 1

typedef struct Vertex{
    int num;    /* vertex number */
    struct Vertex* link; /* link to a next adjacent vertex*/
}Vertex;

typedef struct VertexHead{
    Vertex* head; /* linked list of all adjacent vertices */
}VertexHead;

typedef struct Graph{
    VertexHead* vlist; /* list of all vertices : vlist[MAX_VERTEX] */
}Graph;

int visited[MAX_VERTEX]; //vertex를 방문했는지 확인을 위한 visited[MAX_VERTEX]선언

/* for stack */
Vertex* stack[MAX_VERTEX]; //Vertex형을 저장할 stack[MAX_VERTEX]선언
int top = -1;

int pop(); //stack에 top에 있는 vertex의 num값 리턴
int push(Vertex* aVertex); //stack에 aVertex 삽입
int stack_isFull(); //stack이 꽉 찼는지 확인
int stack_isEmpty(); //stack이 꽉 찼는지 확인

/* for queue */
Vertex* queue[MAX_VERTEX]; //Vertex형을 저장할 queue[MAX_VERTEX]선언
int front = -1;
int rear = -1;

int deQueue(); //Queue에 있는 Vertex pop
int enQueue(Vertex* aVertex); //Queue에 aVertex 삽입
int queue_isFull(); //queue가 가득 찼는지 확인
int queue_isEmpty(); //queue가 비었는지 확인

int createGraph(Graph** g);  /* 비어있는 그래프 생성 */
void destroyGraph(Graph* g); /* 모든 할당된 메모리 삭제 */
int insertVertex(Graph* g,int key); /* vertex 삽입 */
int deleteVertex(Graph* g,int key); /* vertex 삭제 */
Vertex* returnVertex(int key); //key값을 가지고 가리키는 link의 값이 NULL인 Vertex형 포인터 newVertex리턴
int insertEdge(Graph* g,int from, int to); /* 두 개의 vertex 사이에 새로운 edge 생성 */
int deleteEdge(Graph* g,int from, int to); /* edge 삭제 */
int depthFS(Graph* g,int key); /* stack을 사용한 깊이 우선 탐색 */
int breadthFS(Graph* g,int key); /* queue를 사용한 너비 우선 탐색 */
void printGraph(Graph* g); /* vertices and edges가 있는 그래프 출력 */

int main()
{
	char command;
	int key,from,to;
	Graph* graph = NULL; //Graph형 포인터 구조체 Graph선언

     printf("------[Na Kyu Tae]-----[2017038073]------"); //이름과 학번 출력
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Term Project                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph         = z                                       \n");
		printf(" Insert Vertex        = v      Print Graph                  = p \n");
		printf(" Insert Edge          = i      Delete Vertex                = d \n");
        printf(" DepthFS (Stack)      = t      Delete Edge                  = E \n");
		printf(" BreadthFS (Queue)    = b      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //원하는 명령 입력

		switch(command) {
		//z나 Z가 입력될 경우 graph에 직접 메모리 할당
		case 'z': case 'Z':
			createGraph(&graph);
			break;
		//q나 Q가 입력될 경우 모든 그래프에 할당된 모든 메모리 해제
		case 'q': case 'Q':
			destroyGraph(graph);
			break;
		//v나 V가 입력될 경우 graph가 NULL이 아닐경우 key의 값을 갖는 Vertex삽입 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'v': case 'V':
			if(graph!=NULL)
			{
				printf("Your Key = ");
				scanf("%d", &key);
				insertVertex(graph,key);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
		//i나 I가 입력될 경우 graph가 NULL이 from과 to 두 Vertex 사이에 새로운 edge생성 아닐경우 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'i': case 'I':
			if(graph!=NULL)
			{
				printf("Your from = ");
				scanf("%d",&from);
				printf("Your to = ");
				scanf("%d",&to);
				insertEdge(graph,from,to);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
		//t나 T이 입력될 경우 graph가 NULL이 아닐경우 스택을 사용한 key값에 대한 깊이 우선 탐색 실시 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 't': case 'T':
			if(graph!=NULL)
			{
				printf("Your Key = ");
				scanf("%d", &key);
				depthFS(graph,key);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
		//b나 B가 입력될 경우 graph가 NULL이 아닐경우 큐를 사용한 key값에 대한 너비 우선 탐색 실시 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'b': case 'B':
			if(graph!=NULL)
			{
				printf("Your Key = ");
				scanf("%d", &key);
				breadthFS(graph,key);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
		//p나 P가 입력될 경우 graph가 NULL이 아닐경우 graph 출력 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'p': case 'P':
			if(graph!=NULL)
				printGraph(graph);
			else
				printf("please input 'z'or'Z' first!");
			break;
        //d나 D가 입력될 경우 graph가 NULL이 아닐경우 key값을 갖는 vertex 삭제 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'd': case 'D':
			if(graph!=NULL)
			{
				printf("Your Key = ");
				scanf("%d", &key);
				deleteVertex(graph,key);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
        //e나 E가 입력될 경우 graph가 NULL이 아닐경우 from과 to 두 Vertex 사이에 연결된 edge삭제 NULL일 경우 z나Z를 입력하라는 문장 출력
		case 'e': case 'E':
			if(graph!=NULL)
			{
				printf("Your from = ");
				scanf("%d",&from);
				printf("Your to = ");
				scanf("%d",&to);
				deleteEdge(graph,from,to);
			}
			else
				printf("please input 'z'or'Z' first!");
			break;
		//그 이외의 값이 입력 될 경우 집중하라는 문장 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

/* 비어있는 그래프 생성 */
int createGraph(Graph** g)
{
	//만약 그래프가 비워있지 않으면, 그래프에 할당된 모든 헤드와 링크들 삭제(해제)
	if(*g != NULL) 
		destroyGraph(*g);

	*g=(Graph*)malloc(sizeof(Graph)); //그래프에 메모리 할당
	
	(*g)->vlist=(VertexHead*)malloc(MAX_VERTEX*sizeof(VertexHead)); //그래프의 vlist에 MAX_VERTEX만큼의 메모리 할당

	for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복
		(*g)->vlist[i].head=NULL; //그래프의 vlist[i]의 head값 초기화

	return 1;
}

 /* 모든 할당된 메모리 삭제 */
void destroyGraph(Graph* g)
{
	if(g!=NULL) //g가 NULL이 아닐 경우
	{
		if(g->vlist!=NULL) //g의 vlist가 NULL이 아닐 경우
		{
			for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복 
			{
				Vertex* ptr = g->vlist[i].head; // ptr에 g의 vlist[i]의 head를 대입
				while(ptr!=NULL) //ptr의 값이 NULL이 될때까지 반복
				{
					Vertex* temp = ptr; //temp에 ptr의 값 대입
					ptr = ptr->link; //ptr에 ptr의 link가 가리키는 값 대입
					free(temp); //temp 메모리 해제
				}
			}
			free(g->vlist); //g->vlist의 메모리 해제
		}
		free(g); //g의 메모리 해제
	}
}

/* vertex 삽입 */
int insertVertex(Graph* g,int key)
{
	Vertex* newVertex=(Vertex*)malloc(sizeof(Vertex)); //Vertex형 포인터 newVertex에 메모리 할당
	
	newVertex->num=key; //newVertex의 num에 key값 대입
	newVertex->link=NULL; //newVertex의 link에 NULL 대입
	
	if(key>MAX_VERTEX||key<=0) //key의 값이 0이하이거나 MAX_VERTEX의 값보다 클경우 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복
	{
		if((i+1)==key) //만약 i+1의 값이 key와 같을 경우 
		{
			if(g->vlist[i].head==NULL) //만약 g의 vlist[i]의 head에 값이 없을경우
			{
				g->vlist[i].head=newVertex; //g의 vlist[i]의 head에 newVertex대입
				return 1;
			}

			else //g의 vlist[i]의 head에 값이 있으면 무시
				return 1;
		}
	}
}

/* vertex 삭제 */
int deleteVertex(Graph* g,int key)
{
	Vertex* agovertex = NULL; //Vertex형 포인터 agovertex에 NULL 대입
	Vertex* ptr = NULL; //Vertex형 포인터 ptr에 NULL 대입
	Vertex* temp = NULL; //Vertex형 포인터 temp에 NULL 대입

	if(key>MAX_VERTEX||key<=0) //key의 값이 0이하이거나 MAX_VERTEX의 값보다 크면 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	else if(g->vlist[key-1].head!=NULL) //g의 vlist[key-1]의 head에 값이 존재할 경우
	{
		for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복
		{
			if(i==key-1) //i의 값이 key-1와 같을 경우
			{
				ptr = g->vlist[key-1].head; //ptr에 g의 vlist[key-1]의 head값 대입

				while(ptr!=NULL) //ptr의 값이 존재하지 않을때까지 반복
				{
					temp = ptr; //temp에 ptr 대입
					ptr = ptr->link; //ptr에 ptr의 link가 가리키는 값 대입
					free(temp); //temp 메모리 해제
				}

				g->vlist[key-1].head=NULL; //g의 vlist[key-1]의 head값에 NULL대입
			}

			else //i의 값이 key-1와 같지 않을 경우
			{
				if(g->vlist[i].head!=NULL) //g의 vlist[i]의 head에 값이 존재할 경우
				{
					agovertex = g->vlist[i].head; //agovertex에 g의 vlist[i]의 head값 대입
					ptr = g->vlist[i].head->link; //ptr에 g의 vlist[i]의 head의 link가 가리키는 값 대입
					while(ptr!=NULL) //ptr의 값이 NULL이 될때까지 반복
					{
						temp = ptr; //temp에 ptr값 대입
						ptr = ptr->link; //ptr에 ptr의 link가 가리키는 값 대입

						if(temp->num==key) //temp의 num이 key와 같을 경우
						{
							if(ptr==NULL) //ptr의 값이 NULL일 경우
							{
								free(temp); //temp 메모리 해제
								agovertex->link=NULL; //agovertex의 link가 가리키는 값에 NULL대입
								break; //반복종료
							}
							else //ptr의 값이 NULL이 아닐 경우
							{
								agovertex->link=ptr; //agovertex의 link가 가리키는 값에 ptr 대입
								free(temp); //temp 메모리 해제
								break; //반복종료
							}
						}

						else //temp의 num이 key와 같지 않을 경우
							agovertex=agovertex->link; //agovertex에 agovertex의 link가 가리키는 값 대입
					}
				}
			}
		}
		return 1;
	}
	else //그 외에 경우 key값을 가진 vertex가 존재하지 않는다는 문장 출력
	{
		printf("%d vertex not exist",key);
		return 0;
	}
}

//key값을 가지고 가리키는 link의 값이 NULL인 Vertex형 포인터 newVertex리턴
Vertex* returnVertex(int key)
{
	Vertex* newVertex=(Vertex*)malloc(sizeof(Vertex));  //Vertex형 포인터 newVertex에 메모리 할당
	
	if(!newVertex) //newVertex에 메모리 할당이 안됐을 경우 메모리 할당이 안된다는 문장 출력 
		printf("Unable to allocate memory for new Vertex");
	
	newVertex->num=key; //newVertex의 num에 key대입
	newVertex->link=NULL; //newVertex의 link가 가리키는 값에 NULL대입
	
	return newVertex; //newVertex 리턴
}

/* 두 개의 vertex 사이에 새로운 edge 생성 */
int insertEdge(Graph* g,int from, int to)
{
    Vertex* newVertex=NULL; //Vertex형 포인터 newVertex에 NULL대입
	Vertex* ptr=NULL; //Vertex형 포인터 ptr에 NULL대입
	
	if(from>MAX_VERTEX||from<=0||to>MAX_VERTEX||to<=0) //from의 값이 0이하이거나 MAX_VERTEX보다 크거나 to의 값이 0이하이거나 MAX_VERTEX보다 크면 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	else if(g->vlist[from-1].head!=NULL&&g->vlist[to-1].head!=NULL) //g의 vlist[from-1]의 head의 값과 g의 vlist[to-1]의 head의 값이 존재할 경우
	{
		newVertex = returnVertex(to); //newVertex에 returnVertex함수의 인자에 to값을 넣고 리턴된 값 대입
		ptr = g->vlist[from-1].head; //ptr에 g의 vlist[from-1]의 head의 값 대입

		if(ptr->link==NULL) //ptr의 link가 가리키는 값이 NULL일 경우
			ptr->link = newVertex; //ptr의 link가 가리키는 값에 newVertex 대입

		else if(ptr->link!=NULL) //ptr의 link가 가리키는 값이 NULL이 아닐 경우
		{
			while(1) //break가 나올때까지 반복
			{
				ptr=ptr->link; //ptr에 ptr의 link가 가리키는 값 대입

				if(ptr->num==to) //ptr의 num값이 to와 같을 경우
					break; //반복 종료

				else if(ptr->link==NULL) //ptr의 link가 가리키는값이 NULL일 경우
				{
					ptr->link = newVertex; //ptr의 link가 가리키는 값에 newVertex 대입
					break; //반복 종료
				}
			}
		}

		newVertex = returnVertex(from); //newVertex에 returnVertex함수의 인자에 from값을 넣고 리턴된 값 대입
		ptr = g->vlist[to-1].head; //ptr에 g의 vlist[to-1]의 head의 값 대입

		if(ptr->link==NULL) //ptr의 link가 가리키는 값이 NULL일 경우
			ptr->link = newVertex; //ptr의 link가 가리키는 값에 newVertex 대입

		else if(ptr->link!=NULL) //ptr의 link가 가리키는 값이 NULL이 아닐 경우
		{
			while(1) //break가 나올때까지 반복
			{
				ptr=ptr->link; //ptr에 ptr의 link가 가리키는 값 대입

				if(ptr->num==from) //ptr의 num값이 from와 같을 경우
					break; //반복 종료

				else if(ptr->link==NULL) //ptr의 link가 가리키는값이 NULL일 경우
				{
					ptr->link = newVertex; //ptr의 link가 가리키는 값에 newVertex 대입
					break; //반복 종료
				}
			}
		}
	}

	else //그 외에 경우 from이나 to값을 가진 vertex가 존재하지 않는다는 문장 출력
	{
		printf("%d or %d vertex not exist",from,to);
		return 0;
	}
}

/* edge 삭제 */
int deleteEdge(Graph* g,int from, int to)
{
	Vertex* agovertex = NULL; //Vertex형 포인터 agovertex에 NULL 대입
	Vertex* ptr = NULL; //Vertex형 포인터 ptr에 NULL 대입
	Vertex* temp = NULL; //Vertex형 포인터 temp에 NULL 대입
	
	if(from>MAX_VERTEX||from<=0||to>MAX_VERTEX||to<=0) //from의 값이 0이하이거나 MAX_VERTEX보다 크거나 to의 값이 0이하이거나 MAX_VERTEX보다 크면 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	else if(g->vlist[from-1].head!=NULL&&g->vlist[to-1].head!=NULL) //g의 vlist[from-1]의 head의 값과 g의 vlist[to-1]의 head의 값이 존재할 경우
	{
		agovertex = g->vlist[from-1].head; //agovertex에 g의 vlist[from-1]의 head값 대입
		ptr = g->vlist[from-1].head->link; //ptr에 g의 vlist[from-1]의 head의 link가 가리키는 값 대입

		while(ptr!=NULL) //ptr의 값이 NULL일때까지 반복
		{
			temp = ptr; //temp에 ptr값 대입
			ptr = ptr->link; //ptr에 ptr의 link가 가리키는 값 대입

			if(temp->num==to) //temp의 num의 값이 to와 같을 경우
			{
				if(ptr==NULL) //ptr의 값이 NULL일 경우
				{
					free(temp); //temp 메모리 해제
					agovertex->link=NULL; //agovertex의 link가 가리키는 값에 NULL 대입
					break; //반복종료
				}

				else //그 외에 경우
				{
					agovertex->link=ptr; //agovertex의 link가 가리키는 값에 ptr 대입
					free(temp); //temp 메모리 해제
					break; //반복종료
				}
			}

			else //temp의 num의 값이 to와 같지 않을 경우
				agovertex=agovertex->link; //agovertex에 agovertex의 link가 가리키는 값 대입
		}

		agovertex = g->vlist[to-1].head; //agovertex에 g의 vlist[to-1]의 head값 대입
		ptr = g->vlist[to-1].head->link; //ptr에 g의 vlist[to-1]의 head의 link가 가리키는 값 대입
		
		while(ptr!=NULL) //ptr의 값이 NULL일때까지 반복
		{
			temp = ptr; //temp에 ptr값 대입
			ptr = ptr->link; //ptr에 ptr의 link가 가리키는 값 대입

			if(temp->num==from) //temp의 num의 값이 from과 같을 경우
			{
				if(ptr==NULL) //ptr의 값이 NULL일 경우
				{
					free(temp); //temp 메모리 해제
					agovertex->link=NULL; //agovertex의 link가 가리키는 값에 NULL 대입
					break; //반복종료
				}
				else //그 외에 경우
				{
					agovertex->link=ptr; //agovertex의 link가 가리키는 값에 ptr 대입
					free(temp); //temp 메모리 해제
					break; //반복종료
				}
			}

			else //temp의 num의 값이 from과 같지 않을 경우
				agovertex=agovertex->link; //agovertex에 agovertex의 link가 가리키는 값 대입
		}
		return 1;
	}

	else //그 외에 경우 0 리턴
		return 0;
}

/* stack을 사용한 깊이 우선 탐색 */
int depthFS(Graph* g,int key)
{
	Vertex* w; //Vertex형 포인터 w 선언

	for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복 
		visited[i]=FALSE; //visited[i]에 FALSE대입

	if(key>MAX_VERTEX||key<=0) //key의 값이 0이하이거나 MAX_VERTEX의 값보다 클경우 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	else if(g->vlist[key-1].head!=NULL) //g의 vlist[key-1]의 head값이 NULL이 아닐 경우
	{
		printf("%5d",key); //key의 값 출력
		visited[key-1]=TRUE; //visited[key-1]에 TRUE 대입
		push(g->vlist[key-1].head); //g의 vlist[key-1]의 head를 인수로 받는 push함수 실행

		while(stack_isEmpty()==1) //top의 값이 -1이 될때까지 반복
		{
			w=g->vlist[key-1].head; //w에 g의 vlist[key-1]의 head값 대입

			while(w) //w값이 NULL일 때까지 반복
			{
				if(!visited[(w->num)-1]) //visited[(w->num)-1]의 값이 FALSE일 경우
				{
					push(w); //w를 인수로 받는 push함수 실행
					visited[(w->num)-1]=TRUE; //visited[(w->num)-1]의 값에 TRUE대입
					printf("%5d",w->num);  //w의 num값 출력
					key=w->num; //key에 w의 num값 대입
					w=g->vlist[key-1].head; //w에 g의 vlist[key-1]의 head값 대입
				}
				else //visited[(w->num)-1]의 값이 TRUE일 경우
					w=w->link; //w에 w의 link가 가리키는 값 대입
			}
			key=pop(); //key에 pop함수가 리턴하는 값 대입
		}
		return 1;
	}

	else //그 외에 경우 key값을 가진 vertex가 존재하지 않는다는 문장 출력
	{
		printf("%d vertex not exist",key);
		return 0;
	}
}

//stack에 top에 있는 vertex의 num값 리턴
int pop()
{
	Vertex* element = NULL; //Vertex형 포인터 element에 NULL 대입

	if (stack_isEmpty() == 0) //스택이 비었을 경우 리턴
	{
		return 0;
	}

	stack[top--] = NULL; //stack[top]에 NULL대입 후 top값에 -1

	if(top==-1) //top값이 -1일경우 리턴
		return 0;

	else //그 외에 경우
	{
		element = stack[top]; //element에 stack[top]값 대입
		return element->num; //element의 num값 리턴
	}
}

//stack에 aVertex 삽입
int push(Vertex* aVertex)
{
	if (stack_isFull() == 0) //stack이 꽉 찼을 경우 리턴
	{
		return 0;
	}

	stack[++top] = aVertex; //stack[++top]에 aVertex대입

	return 1;
}

//stack이 꽉 찼는지 확인
int stack_isFull() {

	if (top >= (MAX_VERTEX - 1)) //top이 MAX_VERTEX-1값 이상일 경우 0리턴
	{
		return 0;
	}

	return 1; //1리턴
}

//stack이 비었는지 확인
int stack_isEmpty() {

	if (top < 0) //top의 값이 0미만일 경우 0리턴
	{
		return 0;
	}

	return 1; //1리턴
}

/* queue를 사용한 너비 우선 탐색 */
int breadthFS(Graph* g,int key)
{
	Vertex* w; //Vertex형 포인터 w 선언
	
	for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복 
		visited[i]=FALSE; //visited[i]에 FALSE대입

	if(key>MAX_VERTEX||key<=0) //key의 값이 0이하이거나 MAX_VERTEX의 값보다 클경우 1~MAX_VERTEX사이에 양의정수를 입력하라는 문장 출력
	{
		printf("please input positive integer between 1~%d",MAX_VERTEX);
		return 0;
	}	

	else if(g->vlist[key-1].head!=NULL) //g의 vlist[key-1]의 head값이 NULL이 아닐 경우
	{
		printf("%5d",key); //key의 값 출력
		visited[key-1]=TRUE; //visited[key-1]에 TRUE 대입
		enQueue(g->vlist[key-1].head); //g의 vlist[key-1]의 head를 인수로 받는 enQueue함수 실행

		while(queue_isEmpty()==1) //queue가 비었을때까지 반복
		{
			key=deQueue(); //key에 deQueue함수가 리턴한 값 대입
			for(w=g->vlist[key-1].head;w;w=w->link) //
			{
				if(!visited[(w->num)-1]) //visited[(w->num)-1]의 값이 FALSE일 경우
				{
					printf("%5d",w->num); //w의 num값 출력
					enQueue(w); //w를 인수로 받는 enQueue함수 실행
					visited[(w->num)-1]=TRUE; //visited[(w->num)-1]의 값에 TRUE대입
				}
			}
		}

	}

	else //그 외에 경우 key값을 가진 vertex가 존재하지 않는다는 문장 출력
	{
		printf("%d vertex not exist",key);
		return 0;
	}
}

//Queue에 있는 Vertex pop
int deQueue()
{
	Vertex* element = NULL; //Vertex형 포인터 element에 NULL대입

	if (queue_isEmpty() == 0) //queue가 비었을 경우 0 리턴
	{
		return 0;
	}

	front = (front + 1) % MAX_VERTEX; //front에 (front+1) % MAX_VERTEX한 값 대입
	element = queue[front]; //element에 queue[front] 값 대입
	queue[front] = NULL; //queue[front]에 NULL대입

	return element->num; //element의 num값 리턴
}

//Queue에 aVertex 삽입
int enQueue(Vertex* aVertex)
{
	if (queue_isFull() == 0)  //queue가 꽉 찾을 경우 0리턴
	{
		return 0;
	}

	rear = (rear + 1) % MAX_VERTEX; //rear에 (rear+1) % MAX_VERTEX한 값 대입

	queue[rear] = aVertex; //queue[rear]에 aVertex 대입

	return 1;
}

//queue가 가득 찼는지 확인
int queue_isFull() 
{
	if (front == ((rear + 1) % MAX_VERTEX)) //front값이 (rear+1) % MAX_VERTEX와 같을 경우 0 리턴
	{
		return 0;
	}

	return 1; //1 리턴
}

//queue가 비었는지 확인
int queue_isEmpty() {

	if (front == rear) //front와 rear값이 같을 경우
	{
		return 0;
	}

	return 1; //1 리턴
}

/* vertices and edges가 있는 그래프 출력 */
void printGraph(Graph* g)
{
	for(int i=0;i<MAX_VERTEX;i++) //i를 0부터 20이상이 될 때까지 1을 더하며 반복
	{
		Vertex* ptr = g->vlist[i].head; //Vertex형 포인터 ptr에 g의 vlist[i]의 head값 대입
		while(ptr) //ptr값이 NULL일때까지 반복
		{
			printf("\n [%d] : -> ", ptr->num); //ptr의 num값 출력
			while(ptr) //ptr값이 NULL일때까지 반복
			{
				ptr=ptr->link; //ptr에 ptr의 link가 가리키는 값 대입
				if(ptr==NULL) //ptr의 값이 NULL일 경우 NULL문장 출력
				{
					printf("NULL\n");
				}
				else //그 외에 경우 ptr의 num값 출력
					printf("[%d] -> ",ptr->num);
			}
		}
	}
}