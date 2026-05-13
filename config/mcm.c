#include <stdio.h>
#include <time.h>
#include <limits.h>

#define max 100
void optPar(int s[max][max], int i, int j){
    if(i==j){
        printf("A%d", i);
        return;
    }

    printf("(");
    optPar(s, i, s[i][j]);
    optPar(s, s[i][j]+1, j);
    printf(")");
}

int mcm(int p[], int n){
    int m[max][max];
    int s[max][max];

    for(int i = 0; i<n; i++){
        m[i][i] = 0;
    }

    for(int L = 2; L<n; L++){
        for(int i = 1; i<n-L+1; i++){
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for(int k = i; k<j; k++){
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

                if(q<m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    optPar(s, 1, n-1);
    printf("\n");
    return m[1][n-1];
}

int main() {

    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[max];
    printf("Enter dimensions array:\n");
    for(int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    clock_t start, end;
    start = clock();
    int result = mcm(p, n + 1);
    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nMinimum number of multiplications = %d\n",result);

    printf("Time taken: %f ms\n", time_taken);
    return 0;

}


