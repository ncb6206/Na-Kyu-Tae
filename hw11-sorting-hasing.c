#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a); //array에 직접 메모리 할당 또는 메모리 공유 한 다음 랜덤값을 배열의 값으로 저장
int freeArray(int *a); //array에 할당된 메모리 해제
void printArray(int *a); //array에 들어있는 원소들을 출력

int selectionSort(int *a); //선택정렬을 이용해 원소들을 최소값부터 정렬
int insertionSort(int *a); //삽입정렬을 이용해 원소들을 최소값부터 정렬
int bubbleSort(int *a); //버블정렬을 이용해 원소들을 최소값부터 정렬
int shellSort(int *a); //셸정렬을 이용해 원소들을 최소값부터 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); //퀵정렬을 이용해 원소들을 최소값부터 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에 대한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);

int main()
{
	char command; //명령어를 입력받을 command 변수 선언
	int *array = NULL; //배열을 입력할 array 포인터 변수 선언
	int *hashtable = NULL; //데이터를 저장할 hashtable 포인터 변수 선언
	int key = -1; //key값 초기화
	int index = -1; //index값 초기화

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		//z나 Z가 입력될 경우 array에 직접 메모리 할당 또는 메모리 공유 한 다음 랜덤값을 배열의 값으로 저장
		case 'z': case 'Z':
			initialize(&array);
			break;
		//q나 Q가 입력될 경우 array에 할당된 메모리 해제
		case 'q': case 'Q':
			freeArray(array);
			break;
		//s나 S가 입력될 경우 선택정렬을 이용해 array배열의 원소들을 최소값부터 정렬
		case 's': case 'S':
			selectionSort(array);
			break;
		//i나 I가 입력될 경우 삽입정렬을 이용해 array배열의 원소들을 최소값부터 정렬
		case 'i': case 'I':
			insertionSort(array);
			break;
		//b나 B가 입력될 경우 버블정렬을 이용해 array배열의 원소들을 최소값부터 정렬
		case 'b': case 'B':
			bubbleSort(array);
			break;
		//l이나 L이 입력 될경우 셸정렬을 이용해 array배열의 원소들을 최소값부터 정렬
		case 'l': case 'L':
			shellSort(array); 
			break;
		//k나 K가 입력 될경우 퀵정렬을 이용해 array배열의 원소들을 최소값부터 정렬
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //퀵정렬 된 후 array배열의 원소들을 출력

			quickSort(array, MAX_ARRAY_SIZE); //퀵정렬을 이용해 array배열의 원소들을 최소값부터 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); //퀵정렬 된 후 array배열의 원소들을 출력
			break;
		//h나 H가 입력 될경우 array에 대한 hashtable을 만든 값 출력
		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //array배열의 원소들을 출력
			hashing(array, &hashtable); //array에 있는 원소들을 hashtable에 해싱한다
			printArray(hashtable); //hashtable에 있는값들 출력
			break;
		//e나 E가 입력될 경우 원하는 key를 입력해 hash table에서 key를 찾아 hash table의 key값과 index값, hashtable의 index자리에 있는 값 출력 
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable); //기존 hashtable의 값들을 출력
			index = search(hashtable, key); //hashtable안에 key값이 있는 index자리를 찾아 리턴된 값을 index에 대입
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;
		//p나 P가 입력될 경우 array에 들어있는 원소들을 출력
		case 'p': case 'P':
			printArray(array);
			break;
		//그 이외의 값이 입력 될 경우 집중하라는 문구 출력
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 입력될때까지 반복

	return 1;
}

//array에 직접 메모리 할당 또는 메모리 공유 한 다음 랜덤값을 배열의 값으로 저장
int initialize(int** a)
{
	int *temp = NULL; //int형 포인터 temp에 NULL대입

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) 
	{
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //temp에 MAX_ARRAY_SIZE만큼의 동적 할당 실시
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} 
	else //array가 NULL이 아닌 경우 temp에 array값 대입
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

//array에 할당된 메모리 해제
int freeArray(int *a)
{
	/* array가 NULL이 아닌경우 메모리 해제 */
	if(a != NULL)
		free(a);
	return 0;
}

//array에 들어있는 원소들을 출력
void printArray(int *a)
{
	if (a == NULL) //array에 아무것도 없을 경우
	{
		printf("nothing to print.\n"); //출력할 것이 없다는 문장 출력
		return;
	}

	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //0~MAX_ARRAY_SIZE이상이 되기전까지의 a배열의 원소 이름을 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //0~MAX_ARRAY_SIZE이상이 되기전까지의 a배열에 들어있는 원소의 값 출력
		printf("%5d ", a[i]);
	printf("\n");
}

//선택정렬을 이용해 원소들을 최소값부터 정렬
int selectionSort(int *a)
{
	int min; //최소값을 저장할 min 변수 선언
	int minindex; //최소값의 위치를 저장할 minindex 변수 선언
	int i, j; //반복문에 사용할 i와 j 변수 선언

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //선택정렬 되기전 a배열의 원소들을 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //i의 값을 0~MAX_ARRAY_SIZE이상이 되기전까지 1을 더하며 반복
	{
		minindex = i; //최소값의 위치에 i 대입
		min = a[i]; //최소값에 a[i] 대입
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //j의 값을 i+1~MAX_ARRAY_SIZE이상이 되기전까지 1을 더하며 반복
		{
			if (min > a[j]) //만약 최소값이 a[j]보다 작다면
			{
				min = a[j]; //최소값에 a[j] 대입
				minindex = j; //최소값의 위치에 j 대입
			}
		}
		a[minindex] = a[i]; //최소값이 저장된 a[minindex]에 a[i]값 대입
		a[i] = min; //a[i]에 최소값 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //선택정렬 된 후 a배열의 원소들을 출력
	return 0;
}

//삽입정렬을 이용해 원소들을 최소값부터 정렬
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //삽입정렬 되기전 a배열의 원소들을 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //i의 값을 1~MAX_ARRAY_SIZE이상이 되기전까지 1을 더하며 반복
	{
		t = a[i]; //t에 a배열의 i번째 원소에 들어있는 값 대입
		j = i; //j에 i의 값 대입
		while (a[j-1] > t && j > 0) //i의 값이 대입된 j에 a배열의 j-1번째에 들어있는값이 i번째에 들어있는 값보다 크고 j가 양의 정수라는 조건을 만족할 경우 반복
		{
			a[j] = a[j-1]; //a배열의 j번째에 들어있는 값에 j-1번째 들어있는 값 대입
			j--; //j값에 1을 뺀다
		}
		a[j] = t; //a배열의 j번째 원소에 들어있는 값에 a배열의 i번째 원소에 들어있는 값 가진 t 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //삽입정렬 된 후 a배열의 원소들을 출력

	return 0;
}

//버블정렬을 이용해 원소들을 최소값부터 정렬
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //버블정렬 되기전 a배열의 원소들을 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //i의 값을 0~MAX_ARRAY_SIZE이상이 되기전까지 1을 더하며 반복
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //j의 값을 1~MAX_ARRAY_SIZE이상이 되기전까지 1을 더하며 반복
		{
			if (a[j-1] > a[j]) //a배열의 j-1번째 원소에 들어있는 값이 j번째 원소에 들어있는 값보다 작을경우 j번째와 j-1번째 원소의 값을 교환
			{
				t = a[j-1]; //a배열의 원래 j-1번째 원소에 들어있는 값을 저장하기위해 t에 대입
				a[j-1] = a[j]; //a배열의 j-1번째 원소 안에 j번째 원소에 들어있는 값 대입
				a[j] = t; //a배열의 j번째 원소 안에 원래 j-1번째 원소에 들어있는 값을 저장한 t 대입 
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //버블정렬 된 후 a배열의 원소들을 출력

	return 0;
}

//셸정렬을 이용해 원소들을 최소값부터 정렬
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //셸정렬 되기전 a배열의 원소들을 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h의 값을 MAX_ARRAY_SIZE/2부터 h값이 0이하가 되기 전까지 2로 나누며 반복
	{
		for (i = 0; i < h; i++) //i의 값을 0부터 h값 이상이 되기전까지 1을 더하며 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //j의 값을 i+h부터 MAX_ARRAY_SIZE이상이 되기전까지 h의 값을 더하며 반복
			{
				v = a[j]; //v에 a배열의 j번째 원소에 들어있는 값 대입
				k = j; //k에 j값 대입
				while (k > h-1 && a[k-h] > v) //j값을 가지는 k의 값이 h-1보다 크고 a배열의 k-h번째 원소에 들어있는 값이 j번째 원소값이 들어있는 v보다 크다는 조건을 둘다 만족할 경우 반복
				{
					a[k] = a[k-h]; //a배열의 k번째 원소 안에 k-h번째 원소에 들어있는 값 대입
					k -= h; //k에 h값을 뺀 값 대입
				}
				a[k] = v; //a배열의 반복문을 실행해 얻은 k번째 원소 안에 a배열의 j번째 원소의 값이 들어있는 v값을 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //셸정렬 된 후 a배열의 원소들을 출력

	return 0;
}

//퀵정렬을 이용해 원소들을 최소값부터 정렬
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) //n이 1보다 클 경우
	{
		v = a[n-1]; //v에 a배열의 n-1번째 원소에 들어있는 값 대입
		i = -1; //i에 -1 대입
		j = n - 1; //j에 n-1 대입

		while(1)
		{
			while(a[++i] < v); //++i를 반복하면서 a배열의 i번째 원소에 들어있는 값이 v에 들어있는 값보다 이상이 되면 반복 종료
 			while(a[--j] > v); //--j를 반복하면서 a배열의 j번째 원소에 들어있는 값이 v에 들어있는 값보다 이하가 되면 반복 종료

			if (i >= j) break; //만약 반복문에서 구한 i값이 j와 같거나 클 경우 전체적인 반복 종료
			/* 반복문으로 구한 i,j를 이용해 a배열의 i번째와 j번째 원소에 들어있는 값을 서로 교환*/
			t = a[i]; 
			a[i] = a[j]; 
			a[j] = t; 
		}
		/* 반복문으로 구한 i를 이용해 a배열의 피봇에 위치한 원소와 i번째 원소에 들어있는 값을 서로 교환*/
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); //배열의 값을 a로 받고 기준값을 i로 받는 퀵정렬 함수 실시 
		quickSort(a+i+1, n-i-1); //배열의 값을 a+i+1로 받고 기준값을 n-i-1로 받는 퀵정렬 함수 실시
	}


	return 0;
}

/* hash code 생성, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //제산 함수를 이용해 key를 MAX_HASH_TABLE_SIZE로 나눈 나머지를 key의 홈 버킷으로 사용
}

/* array a에 대한 hash table을 만든다. */
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //데이터를 저장할 hashtable 선언

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //hashtable에 MAX_ARRAY_SIZE만큼의 메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	/* 키값이 0부터 MAX_HASH_TABLE_SIZE-1까지의 hash table주소의 버킷에 -1대입 */
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //key값 초기화
	int hashcode = -1; //hashcode값 초기화
	int index = -1; //index값 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //i를 0부터 MAX_ARRAY_SIZE-1까지 1씩 증가시키면서 반복
	{
		key = a[i]; //key에 array a[i]의 인자값 대입
		hashcode = hashCode(key); //hashcode에 (key % MAX_HASH_TABLE_SIZE)값 대입
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //hashtable의 hashcode자리에 값이 대입 안되었을경우
		{
			hashtable[hashcode] = key; //hashtable의 hashcode자리에 key값 대입
		} 
		else //그 외의 경우
		{
			index = hashcode; //index에 hashcode값 대입

			while(hashtable[index] != -1) //hashtable의 index자리에 값이 없을때까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //index에 1을 더한값에 % MAX_HASH_TABLE_SIZE한 값을 index에 대입
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //hashtable의 index자리에 key값 대입
		}
	}

	return 0;
}

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key)
{
	int index = hashCode(key); //key % MAX_HASH_TABLE_SIZE값을 index에 대입한다

	if(ht[index] == key) //hash table의 index자리에 있는 값이 key랑 같을 경우
		return index; //index값 리턴

	while(ht[++index] != key) //hash table의 ++index 자리에 있는 값이 key랑 같아질 때까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE; //index % MAX_HASH_TABLE_SIZE 한 값을 index에 대입
	}
	return index; //index값 리턴
}