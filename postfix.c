#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //stack의 크기를 10으로 정의
#define MAX_EXPRESSION_SIZE 20 //expression의 크기를 20으로 정의

/* stack 내에서 우선순위, lparen =0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

precedence getToken(char symbol) //symbol에 값에 따라 리턴값이 달라지는 함수
{
	switch(symbol) 
	{ 
	case '(' : return lparen; // ( 왼쪽 괄호일 경우 lparen 리턴 
	case ')' : return rparen; // ) 오른쪽 괄호일 경우 rparen 리턴 
	case '+' : return plus; // + 덧셈일 경우 plus 리턴
	case '-' : return minus; // - 뺄셈일 경우 minus 리턴
	case '/' : return divide; /* / 나눗셈일 경우 divide리턴 */ 
	case '*' : return times; // * 곱셈일 경우 times 리턴
	default : return operand; // 피연사자일 경우 operand 리턴
	}

}

precedence getPriority(char x) //사용자가 입력한 연산자와 숫자를 geToken함수에 인자로 넣어주는 함수
{
	return getToken(x);
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

//연산자를 입력받아 postfixStack의 ++Top에 넣어주는 함수
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

//postfixStack의 Top에 있는 문자를 리턴하는 하는 함수
char postfixPop()
{
    char x;
    if(postfixStackTop == -1) //Top값이 -1일때 NULL 반환
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; //x에 postfixStack의 Top에 있는값 대입후 Top--
    }
    return x;
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp에 아무것도 없을경우 문자하나를 postfixExp에 복사
		strncpy(postfixExp, c, 1);
	else //그외에 경우 문자하나를 postfixExp 뒤에 붙임
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 연결된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	char *exp = infixExp; /* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char x,a; /*문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') //infixExp의 문자열이 끝날때까지 반복
	{
		x = *exp; //x에 infixExp의 문자하나 대입

		if(getPriority(x)==operand) //x가 피연산자일 경우
			charCat(&x); //x를 postfixExp에 넣음

		else if(getPriority(x)==times||getPriority(x)==plus) //x가 * 나 + 일경우
		{
			if(postfixStackTop==-1) //postfixStackTop값이 -1일 경우
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌

			//x가 *이고 postfixStack의 Top에 들어있는 값이 /인 경우
			else if(getPriority(x)==times&&getPriority(postfixStack[postfixStackTop])==divide)
			{
				a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
				charCat(&a); //a를 postfixExp에 넣음
				postfixPush(x);	 //x를 postfixStack의 ++Top에 넣어줌
			}

			//x가 +이고 postfixStack의 Top에 들어있는 값이 -인 경우
			else if(getPriority(x)==plus&&getPriority(postfixStack[postfixStackTop])==minus){
				a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
				charCat(&a); //a를 postfixExp에 넣음
				postfixPush(x);	//x를 postfixStack의 ++Top에 넣어줌
			}

			//x의 값이 postfixStack의 Top에 들어있는 값보다 우선순위가 클경우
			else if(getPriority(x)> getPriority(postfixStack[postfixStackTop]))
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌

			else //그외에 모든경우
			{
				//x의 값이 postfixStack의 Top에 들어있는 값보다 우선순위가 클때까지 반복
				while(getPriority(x) <= getPriority(postfixStack[postfixStackTop]))
				{
					a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
					charCat(&a); //a를 postfixExp에 넣음
				}
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌
			}
		}

		else if(getPriority(x)==divide||getPriority(x)==minus) //x가 / 나 - 일경우
		{
			if(postfixStackTop==-1) //postfixStackTop값이 -1일 경우
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌
			else if(getPriority(x)> getPriority(postfixStack[postfixStackTop]))
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌
			else  //그외에 모든경우
			{
				//x의 값이 postfixStack의 Top에 들어있는 값보다 우선순위가 작거나 같을때까지 반복
				while(getPriority(x) <= getPriority(postfixStack[postfixStackTop]))
				{
					a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
					charCat(&a); //a를 postfixExp에 넣음
				}
				postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌
			}
		}
		
		else if(getPriority(x)==rparen) //x의 값이 )일 경우
		{
			//postfixStack의 Top에 들어있는 값이 (이 될때까지 반복
			while(getPriority(postfixStack[postfixStackTop])!=lparen)
			{
				a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
				charCat(&a); //a를 postfixExp에 넣음
			}

			//postfixStack의 Top에 들어있는 값이 (인 경우
			if(getPriority(postfixStack[postfixStackTop])==lparen)
				postfixPop(); //postfixStack의 Top에 있는값 대입후 Top--
		}

		else if(getPriority(x)==lparen) //x의 값이 (일 경우
		{
			postfixPush(x); //x를 postfixStack의 ++Top에 넣어줌
		}
		
		exp++; //exp를 증가 시켜 다음문자로 이동
	}
	//postfixStackTop의 값이 -1이 될때까지 
	while(postfixStackTop!=-1) 
	{
		a=postfixPop(); //a에 postfixStack의 Top에 있는값 대입후 Top-- 
		charCat(&a); //a를 postfixExp에 넣음
	}
}

//infixExp,postfixExp,evalResult의 값을 출력하고 postfixStack에 남아있는 값을 전부 출력하는 함수
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

//모든값을 처음상태로 초기화 시켜주는 함수
void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

//evalStack의 ++Top자리에 x를 삽입하는 함수
void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

//evalStack의 Top이 -1일 경우 종료하고 아닐 경우 Top의자리에 있는 값을 리턴하고 Top--를 하는 함수
int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp; /* postfixExp의 문자 하나씩을 읽기위한 포인터 */
	char x; /*문자하나를 임시로 저장하기 위한 변수 */
	int num1,num2; //evalStack에 있는 피연산자를 대입할 변수

	while (*exp != '\0') //postfixExp의 문자열이 끝날때까지 반복
	{
		x = *exp; //x에 postfixExp의 문자하나 대입
		
		if (getPriority(x) == operand) //문자가 피연산자일때
			evalPush(x-'0'); //evalStack의 ++Top에 x-'0'값을 넣어줌
		else 
		{
			num2 = evalPop(); //evalStack의 Top에 있는 값을 num2에 대입 후 Top--
			num1 = evalPop(); //evalStack의 Top에 있는 값을 num1에 대입 후 Top--
			switch (getPriority(x))
			{
			case plus: //문자가 +일때
				evalPush(num1 + num2); //evalStack의 ++Top에 num1+num2의 값을 넣어줌
				break;
			case minus:
				evalPush(num1 - num2); //evalStack의 ++Top에 num1-num2의 값을 넣어줌
				break;
			case times:
				evalPush(num1 * num2); //evalStack의 ++Top에 num1*num2의 값을 넣어줌
				break;
			case divide:
				evalPush(num1 / num2); //evalStack의 ++Top에 num1/num2의 값을 넣어줌
				break;
			}
		}
		exp++; //exp를 증가시켜 다음 문자로 이동
	}
	evalResult = evalStack[0]; //모든 연산을 완료한 evalStack[0]에 들어있는 값을 evalResult에 대입
}

int main()
{
	char command; //명령을 입력받을 char형 command변수 선언

	printf("[-----[Na Kyu Tae]   [2017038073]-----]\n"); //이름과 학번 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 명령을 입력받음

		switch(command) {
		//i,I를 입력했을 경우 infix expression을 입력받고 infixExp에 입력된 값을 저장
		case 'i': case 'I': 
			getInfix();
			break;
		//p,P를 입력했을 경우 infixExp에 입력된 값을 후위표기로 변환한 후 postfixExp에 저장
		case 'p': case 'P': 
			toPostfix();
			break;
		//e,E를 입력했을 경우 postfixExp에 입력된 값을 후위표기식의 연산을 이용해 값을 구한 뒤 evalresult에 저장
		case 'e': case 'E':
			evaluation();
			break;
		//d,D를 입력했을 경우 infixExp,postfixExp,evalResult의 값을 출력하고 postfixStack에 남아있는 값을 전부 출력
		case 'd': case 'D':
			debug();
			break;
		//r,R를 입력했을 경우 처음 상태로 리셋
		case 'r': case 'R':
			reset();
			break;
		//q,Q를 입력했을 경우 프로그램 종료
		case 'q': case 'Q':
			break;
		//그 외의 값을 입력했을 경우 집중하라는 메세지 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q,Q가 나올때까지 반복

	return 0;


}