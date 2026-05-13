#include <stdio.h>
#include <time.h>

#define max 100

void add(int A[max][max], int B[max][max], int C[max][max], int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            C[i][j] = A[i][j]+B[i][j];
        }
    }
}

void subtract(int A[max][max], int B[max][max], int C[max][max], int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            C[i][j] = A[i][j]-B[i][j];
        }
    }
}

void strassen(int A[max][max], int B[max][max], int C[max][max], int size){
    if(size==1){
        C[0][0] = A[0][0]*B[0][0];
        return;
    }

    int newSize = size/2;
    int A11[max][max], A12[max][max], A21[max][max], A22[max][max];
    int B11[max][max], B12[max][max], B21[max][max], B22[max][max];
    int C11[max][max], C12[max][max], C21[max][max], C22[max][max];

    int M1[max][max], M2[max][max], M3[max][max], M4[max][max], M5[max][max], M6[max][max], M7[max][max];

    int T1[max][max], T2[max][max];

    for(int i = 0; i<newSize; i++){
        for(int j = 0; j<newSize; j++){

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+newSize];
            A21[i][j] = A[i+newSize][j];
            A22[i][j] = A[i+newSize][j+newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+newSize];
            B21[i][j] = B[i+newSize][j];
            B22[i][j] = B[i+newSize][j+newSize];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    add(A11, A22, T1, newSize);
    add(B11, B22, T2, newSize);
    strassen(T1, T2, M1, newSize);

    // M2 = (A21 + A22)B11
    add(A21, A22, T1, newSize);
    strassen(T1, B11, M2, newSize);

    // M3 = A11(B12 - B22)
    subtract(B12, B22, T2, newSize);
    strassen(A11, T2, M3, newSize);

    // M4 = A22(B21 - B11)
    subtract(B21, B11, T2, newSize);
    strassen(A22, T2, M4, newSize);

    // M5 = (A11 + A12)B22
    add(A11, A12, T1, newSize);
    strassen(T1, B22, M5, newSize);

    // M6 = (A21 - A11)(B11 + B12)
    subtract(A21, A11, T1, newSize);
    add(B11, B12, T2, newSize);
    strassen(T1, T2, M6, newSize);

    // M7 = (A12 - A22)(B21 + B22)
    subtract(A12, A22, T1, newSize);
    add(B21, B22, T2, newSize);
    strassen(T1, T2, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, T1, newSize);
    subtract(T1, M5, T2, newSize);
    add(T2, M7, C11, newSize);

    // C12 = M3 + M5
    add(M3, M5, C12, newSize);

    // C21 = M2 + M4
    add(M2, M4, C21, newSize);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, T1, newSize);
    add(T1, M3, T2, newSize);
    add(T2, M6, C22, newSize);

    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

}

int main()
{

    int n;

    printf("Enter size of matrix (power of 2): ");

    scanf("%d", &n);

    int A[max][max], B[max][max], C[max][max];

    printf("Enter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {

            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    clock_t start, end;
    start = clock();
    strassen(A, B, C, n);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("\nResultant Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("\nTime taken: %f ms\n", time_taken);

    return 0;
}