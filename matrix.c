#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int** create_matrix(int row, int col); //row와 col을 행과 열로 가지는 2차원 배열을 메모리 할당후 리턴하는 함수
int free_matrix(int** matrix, int row, int col); //create_matrix 함수에 할당된 메모리를 해제하는 함수 
void print_matrix(int** matrix, int row, int col); //row와 col을 행과 열로 갖는 matrix를 출력하는 함수
int fill_data(int** matrix, int row, int col); //0~19사이의 랜덤값으로 배열을 채우는 함수
//matrix의 전치를 matrix_t에 대입하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
//matrix_a와 matrix_b를 더한값을 matrix_sum에 대입하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col); 
//matrix_a에 matrix_b를 빼준값을 matrix_sub에 대입하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col);
//matrix_a에 matrix_t를 곱해준값을 matrix_axt에 대입하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col); 

void main()
{
	int row, col; //행과 열을 입력받는 변수
	//배열들을 저장하는 2차원 포인터 배열 변수 선언
	int** matrix_a, ** matrix_b, ** matrix_t, **matrix_sum, **matrix_sub, **matrix_axt;
	srand(time(NULL)); //랜덤으로 난수를 생성하는 srand함수

	printf("[----- [Na Kyu Tae]   [2017038073] -----]\n"); //이름과 학번 출력
	printf("Input the matrix row : ");
	scanf("%d", &row); //행을 입력한다
	printf("Input the matrix col : ");
	scanf("%d", &col); //열을 입력한다

	matrix_a = create_matrix(row, col); //row와 col을 행과 열로 갖는 matrix_a 배열 메모리 할당
	fill_data(matrix_a, row, col); //0~19사이의 난수를 matrix_a의 행과 열에 대입
	printf("Matrix A \n");
	print_matrix(matrix_a, row, col); //matrix_a 배열 출력
	
	matrix_b = create_matrix(row, col); //row와 col을 행과 열로 갖는 matrix_b 배열 메모리 할당
	fill_data(matrix_b, row, col); //0~19사이의 난수를 matrix_b의 행과 열에 대입
	printf("Matrix B \n");
	print_matrix(matrix_b, row, col); //matrix_b 배열 출력

	matrix_sum = create_matrix(row, col); //row와 col을 행과 열로 갖는 matrix_sum 배열 메모리 할당
	addition_matrix(matrix_a, matrix_b, matrix_sum, row, col); //matrix_a와 matrix_b를 더한값을 matrix_sum에 대입
	printf("Matrix A+B \n");
	print_matrix(matrix_sum, row, col); //matrix_sum 배열 출력
	free_matrix(matrix_sum, row, col); //matrix_sum 배열의 메모리를 해제

	matrix_sub = create_matrix(row, col); //row와 col을 행과 열로 갖는 matrix_sub 배열 메모리 할당
	subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col); //matrix_a와 matrix_b를 빼준값을 matrix_sub에 대입
	printf("Matrix A-B\n");
	print_matrix(matrix_sub, row, col); //matrix_sub 배열 출력
	free_matrix(matrix_b, row, col); //matrix_b 배열의 메모리를 해제
	free_matrix(matrix_sub, row, col); //matrix_sub 배열의 메모리를 해제

	matrix_t = create_matrix(col, row); //col와 row을 행과 열로 갖는 matrix_t 배열 메모리 할당
	transpose_matrix(matrix_a, matrix_t, row, col); //matrix_a를 전치해준 값을 matrix_t에 대입
	printf("Matrix T\n");
	print_matrix(matrix_t, col, row); //matrix_t 배열 출력

	matrix_axt = create_matrix(row, row); //row와 row을 행과 열로 갖는 matrix_a 배열 메모리 할당
	multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col); //matrix_a와 matrix_t를 곱해준 값을 matrix_axt에 대입
	printf("Matrix A*T\n");
	print_matrix(matrix_axt, row, row); //matrix_axt 배열 출력
	free_matrix(matrix_a, row, col); //matrix_a 배열의 메모리를 해제
	free_matrix(matrix_t, col, row); //matrix_t 배열의 메모리를 해제
	free_matrix(matrix_axt, row, row); //matrix_axt 배열의 메모리를 해제
}

//row와 col을 행과 열로 가지는 2차원 배열을 메모리 할당후 리턴하는 함수
int** create_matrix(int row, int col)
{
	//행 또는 열의 값이 0이하일 때 NULL을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	int** matrix ; //메모리를 할당 받을 2차원 배열 변수 matrix 선언

	matrix = (int**)malloc(sizeof(int*) * row); //각 행(row)마다 메모리 할당
	for (int i = 0; i < row; i++)
		matrix[i] = (int*)malloc(sizeof(int) * col); //각 행에 있는 열(col)마다 메모리 할당

	//matrix의 값이 NULL이 나왔을때 NULL을 반환하는 후처리함수
	if (matrix == NULL) {
		printf("배열이 할당되지 않았습니다.\n");
		return NULL;
	}

	return matrix; //matrix값 리턴
}

//create_matrix 함수에 할당된 메모리를 해제하는 함수 
int free_matrix(int** matrix, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	for (int i = 0; i < row; i++)
		free(matrix[i]); //각 행에 있는 열(col)마다 할당된 메모리 해제
	free(matrix); //각 행(row)마다 할당된 메모리 해제

	//matrix가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix == NULL) {
		printf("Matrix not released.\n");
		return -1;
	}

	return 1;
}

//row와 col을 행과 열로 갖는 matrix를 출력하는 함수
void print_matrix(int** matrix, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 NULL을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
	}

	for (int i = 0; i < row; i++) //i의 값이 0~row-1까지 1씩증가
	{
		for (int j = 0; j < col; j++) //j의값이 0~col-1까지 1씩 증가
			printf("%5d", matrix[i][j]); //5칸 간격으로 matrix의 i행의 열 전부 출력
		printf("\n"); //i행의 열을 전부 출력하고 줄바꿈
	}
	printf("\n");

	//matrix가 NULL일경우 배열이 제대로 출력되지 않았음을 출력하는 후처리 함수
	if (matrix == NULL) {
		printf("Matrix is not output properly.\n");
	}
}

//0~19사이의 랜덤값으로 배열을 채우는 함수
int fill_data(int** matrix, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	//rand()함수를 이용해 matrix의 각 행과 열에 0~19 사이의 랜덤값으로 채운다.
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix[i][j] = rand() % 20;

	//matrix가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix == NULL) {
		printf("Matrix is not properly filled\n");
		return -1;
	}

	return 1;
}

//matrix의 전치를 matrix_t에 대입하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}
	//matrix에 행과 열에 들어있는 값들을 matrix_t에는 열과 행에 집어넣어서 전치행렬로 만든다.
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix_t[j][i] = matrix[i][j];

	//matrix_t가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix_t == NULL) {
		printf("Matrix not properly transposed.\n");
		return -1;
	}

	return 1;
}

//matrix_a와 matrix_b를 더한값을 matrix_sum에 대입하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}
	//matrix_a의 행과 열에 들어있는값과 matrix_b의 행과 열에 들어있는값을 더해 matrix_sum의 행과열에 대입
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];

	//matrix_sum가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix_sum == NULL) {
		printf("Matrix did not addition properly.\n");
		return -1;
	}

	return 1;
}

//matrix_a에 matrix_b를 빼준값을 matrix_sub에 대입하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}
	//matrix_a의 행과 열에 들어있는값과 matrix_b의 행과 열에 들어있는값을 빼서 matrix_sub의 행과열에 대입
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];

	//matrix_sub가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix_sub == NULL) {
		printf("Matrix did not subtraction properly.\n");
		return -1;
	}

	return 1;
}

//matrix_a에 matrix_t를 곱해준값을 matrix_axt에 대입하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)
{
	//행 또는 열의 값이 0이하일 때 -1을 반환하는 전처리함수
	if (row <= 0 || col <= 0) {
		printf("Check the sizes of row and col!\n");
		return -1;
	}

	for (int i = 0; i < row; i++) //matrix_a와 matrix_t를 곱하면 rowXrow의 정사각 행렬이 나온다.
		for (int a = 0; a < row; a++) {
			int sum = 0; //matrix_a의 행과 matrix_t의 열을 곱한값을 더하기 위한 sum변수 선언
			for (int t = 0; t < col; t++)
				//matrix_a의 행과 matrix_t의 열을 곱한값을 sum에 더한다.
				sum += (matrix_a[i][t] * matrix_t[t][a]);
		matrix_axt[i][a] = sum; //sum값을 matrix_axt의 행과 열에 대입
	}

	//matrix_axt가 NULL일경우 -1을 반환하는 후처리 함수
	if (matrix_axt == NULL) {
		printf("Matrix did not multiply properly.\n");
		return -1;
	}

	return 1;
}