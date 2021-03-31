#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // 배열 생성 함수
void print_matrix(int** matrix, int row, int col); // 배열 출력 함수
int free_matrix(int** matrix, int row, int col); // 배열 동적 할당 해제 함수
int fill_data(int** matrix, int row, int col); // 배열 초기화 함수, srand() 통해 seed 초기화
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // matrix_a와 matrix_b의 합을 구하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // matrix_a와 matrix_b의 차를 구하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // matrix_a의 전치행렬 matrix_a_t를 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // matrix_a와 matrix_a_t의 곱을 구하는 함수

int main()
{

    char command; // 명령어 입력 변수 선언
    printf("[----- [손영재]  [2018038080] -----]\n");

    int row, col; // 입력받을 행렬의 크기 변수 선언

    printf("행과 열의 크기를 공백으로 구분하여 입력하세요. : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); // 입력받은 행렬 크기대로 matrix_a 메모리 할당 함수 호출
    int** matrix_b = create_matrix(row, col); // 입력받은 행렬 크기대로 matrix_b 메모리 할당 함수 호출
    int** matrix_a_t = create_matrix(col, row); // matrix_a_t 메모리 할당 함수 호출, 전치행렬이므로 row, col 순서 바꿔서 호출

    if (matrix_a == NULL || matrix_b == NULL)  // 생성을 실패해 반환값이 NULL일 경우 오류메시지 출력 및 종료
        {   /* 후처리 검사 */
            printf("배열 초기 생성을 실패했습니다. 종료 후 다시 실행하십시오.\n");
            return -1;
        }


    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); // 초기화 명령 시
            fill_data(matrix_a, row, col); // matrix_a 초기화 함수 호출
            fill_data(matrix_b, row, col); // matrix_b 초기화 함수 호출     
            printf("행렬이 초기화되었습니다.\n");
            printf("생성한 행렬을 출력합니다.\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); // matrix_a 출력 함수 호출
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // matrix_b 출력 함수 호출
            break;
        case 'p': case 'P':
            printf("Print matrix\n"); // 출력 명령 시
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); // matrix_a 출력 함수 호출
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // matrix_b 출력 함수 호출
            break;
        case 'a': case 'A':
            printf("Add two matrices\n"); // add 명령시
            addition_matrix(matrix_a, matrix_b, row, col); // matrix_a와 matrix_b를 더하는 함수 호출
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n"); // subtract 명령시
            subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a에서 matrix_b를 빼는 함수 호출
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n"); // transpose 명령시
            transpose_matrix(matrix_a, matrix_a_t, col, row); // matrix_a를 전치한 행렬 값을 matrix_a_t에 대입하는 함수 호출하고 출력
            printf("전치한 행렬을 출력합니다.\n");
            print_matrix(matrix_a_t, col, row);    
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n"); // multiply 명령시
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 전치행렬 matrix_a_t를 구하는 함수 호출한 뒤
            multiply_matrix(matrix_a, matrix_a_t, row, col); // matrix_a와 matrix_a_t를 행렬곱하는 함수 호출
            break;
        case 'q': case 'Q':
            printf("모든 2차원 배열 할당을 해제합니다..\n"); // 프로그램 종료 명령시
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col); // 앞서 생성했던 matrix_a, matrix_b, matrix_a_t의 할당을 해제함
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 지정된 명령어가 아닌 명령 입력시 메시지 출력
            break;
        }

    }while(command != 'q' && command != 'Q'); // 종료 명령(q) 전까지 메뉴 계속 반복 실행

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* 전처리 검사 */
    if(row <= 0 || col <=0) {
    printf("행과 열의 값이 양의 정수인지 확인하십시오!\n"); // 입력받은 행 또는 열의 값이 자연수가 아닐 경우 오류메시지 출력
    return NULL;
    }

    int** tempr = (int**)malloc(sizeof(int*) * row); // tempr 이중포인터에 동적할당으로 (int 포인터 크기 * row)만큼의 size 메모리 배정

    for(int i = 0; i < row; i++)
            tempr[i] = (int*)malloc(sizeof(int) * col); // tempr에 속하는 각 부분배열에 대해 (int 크기 * column)만큼의 size 메모리 배정

    /* 후처리 검사 */
    if(tempr == NULL) {
    printf("배열 생성을 실패하였습니다. 재시도 하십시오!\n"); // 동적 할당 실패시 오류 메시지 출력
    return NULL; 
    }
    return tempr; // 정상적으로 실행되었을 경우 tempr 반환
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // 배열 이중포인터 변수와 행, 열 변수를 매개변수로 받아
{

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++) // 이중 for문을 통해 배열 내 모든 요소에 대하여
        {
            printf("%d\t", matrix[i][j]); // 같은 행에 속하는 요소는 \t로 구분하여 출력
        }
        printf("\n"); // 행이 바뀔 경우 개행문자 출력
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // 배열에 대한 동적할당 해제 함수 호출시
{
    for(int i = 0; i < row; i++)
            free(matrix[i]); // 먼저 2차원 배열 내의 부분배열에 대해 for문으로 모두 할당을 해제하고
    free(matrix); // 2차원 배열 할당 해제를 완료한다.
    return 0; /* O.K. */
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    _sleep(1000); // seed값 차이를 두기 위해 1초 대기
    srand((unsigned)time(NULL)); // srand()함수를 이용하여 seed값 변경
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++) // 이중 for문을 통해 배열 내 모든 요소에 대해
        {
            matrix[i][j] = rand()%20; // 배열 내 요소 값이 0~19 이므로 조건에 맞추어 대입
        }
    }
    return 0; /* O.K. */
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
        /* 전처리 검사 */
        if(row <= 0 || col <=0) {
        printf("행과 열의 값이 양의 정수인지 확인하십시오!\n"); // 잘못된 값이 입력되었을 경우 오류메시지 출력
        return -1; /* NOT O.K. */
        }
        int** matrix_add = create_matrix(row, col); // matrix_a와 matrix_b의 요소를 더한 값을 임시 저장할 2차원 배열 선언
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++) // 이중 for문을 통해 배열 내 모든 요소에 대해
                {
                    matrix_add[i][j] =  matrix_a[i][j] + matrix_b[i][j]; // matrix_a와 matrix_b의 각 요소를 더한 값을 대입
                    if(matrix_add[i][j]<0 || matrix_add[i][j] >38) // 더한 값이 가능한 범위를 초과한 값일 경우
                        {
                            /* 후처리 검사 */
                            printf("add 중 오류가 발생했습니다. add 함수 종료\n"); // 오류메시지 출력 및
                            free(matrix_add); // 더한 값 저장하는 배열 할당 해제
                            return -1;/* NOT O.K. */
                        }           
                }

        }
        printf("add한 행렬을 출력합니다.\n");
        print_matrix(matrix_add, row, col); // 정상적으로 더해졌을 경우 더한 값 배열 출력
        free_matrix(matrix_add, row, col); // 더한 값 배열 할당 해제
        return 0; /* O.K. */

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
        /* 전처리 검사 */
        if(row <= 0 || col <=0) {
        printf("행과 열의 값이 양의 정수인지 확인하십시오!\n");
        return -1; /* NOT O.K. */
        }
        int** matrix_sub = create_matrix(row, col); // 두 배열의 차를 저장할 2차원 배열 선언
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++) // add_matrix와 마찬가지로 이중 for문을 통해
                {
                    matrix_sub[i][j] =  matrix_a[i][j] - matrix_b[i][j]; // 두 배열의 각각의 차 값을 대입
                    if(matrix_sub[i][j]<-19 || matrix_sub[i][j] >19) // 차의 값이 가능한 범위를 초과한 값일 경우 메시지 출력
                        {
                            /* 후처리 검사 */
                            printf("subtract 중 오류가 발생했습니다. subtract 함수 종료\n");
                            free(matrix_sub); // 뺀 값 저장하는 배열 할당 해제
                            return -1;/* NOT O.K. */
                        }
                }
        }
        printf("subtract한 행렬을 출력합니다.\n");
        print_matrix(matrix_sub, row, col); // 정상적으로 뺀 경우 값 배열 출력
        free_matrix(matrix_sub, row, col); // 뺀 값 배열 할당 해제
        return 0; /* O.K. */
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int col, int row) // 전치행렬을 구하는 함수로 본행렬과 전치행렬 이중포인터, 행과 열 변수 매개변수로 받음
{
        for(int i = 0; i < col; i++)
        {
            for(int j = 0; j < row; j++) // 이중 for문을 통해 본행렬에 속하는 모든 요소에 대해
                {
                    matrix_t[i][j] = matrix[j][i]; // 요소마다 전치행렬값을 구하여 대입
                    if(matrix_t[i][j]<0 || matrix_t[i][j] >19) // 전치행렬값이 가능한 범위를 초과하는 경우
                        {
                            /* 후처리 검사 */
                            printf("transpose 중 오류가 발생했습니다. transpose 함수 종료\n"); // 오류메시지 출력
                            return -1;/* NOT O.K. */
                        }
                }
        }
    return 0; /* O.K. */
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // 행렬곱을 구하는 함수로 본행렬과 전치행렬 이중포인터, 행과 열 변수 매개변수로 받음
{
    int i, j, k;
     /* 전처리 검사 */
        if(row <= 0 || col <=0) {
        printf("행과 열의 값이 양의 정수인지 확인하십시오!\n");
        return -1; /* NOT O.K. */
        }
        int** matrix_mul = create_matrix(row, row); // 본 행렬과 전치행렬을 곱한 행렬의 크기는 본 행렬의 row * row 와 같으므로 알맞게 생성
        for(int a = 0; a < row; a++)
        {
            for(int b = 0; b < row; b++)
            {
                matrix_mul[a][b] = 0; // 생성한 행렬곱 2차원 배열의 모든 요소값을 0으로 초기화
            }
        }

        for(i = 0; i < row; i++)
        {
            for(j = 0; j < row; j++)
                {
                    for(k = 0; k < col; k++) // 삼중 for문을 통해 matrix_a와 matrix_a_t에 대한 행렬곱 구함
                    {
                        matrix_mul[i][j] += matrix_a[i][k] * matrix_t[k][j]; // 본행렬의 각 열의 요소에 대해 전치행렬과 곱한 값을 합하여 대입
                        if(matrix_mul[i][j]<0 || matrix_mul[i][j] >(19*19)) // 곱한 값이 정상적인 범위를 초과하는 경우
                            {
                            /* 후처리 검사 */
                            printf("transpose 중 오류가 발생했습니다. transpose 함수 종료\n"); // 오류 메시지 출력
                            return -1;/* NOT O.K. */
                            }
                    }  
                }

        }
        printf("multiply한 행렬을 출력합니다.\n");
        print_matrix(matrix_mul, row, row); // 정상적으로 행렬곱이 되면 출력
        free_matrix(matrix_mul, row, row); // 행렬곱에 대한 배열 할당 해제
        return 0; /* O.K. */
}

