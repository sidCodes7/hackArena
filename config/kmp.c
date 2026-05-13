#include <stdio.h>
#include <time.h>
#include <string.h>

#define max 100

void computeLPSArray(char pattern[], int M, int lps[]){
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while(i<M){
        if(pattern[i]==pattern[len]){
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len!=0){
                len = lps[len-1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char pattern[], char txt[]){
    int M = strlen(pattern);
    int N = strlen(txt);

    int lps[max];

    computeLPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;

    while(i<N){
        if(pattern[j]==txt[i]){
            i++;
            j++;
        }

        if(j==M){
            printf("%d pe pattern mila", i-j);
        } else if(i<N && pattern[j]!=txt[i]){
            if(j!=0){
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
}

int main(){
    char txt[max], pattern[max];

    printf("Enter text: ");
    scanf("%s", txt);

    printf("Enter pattern: ");
    scanf("%s", pattern);

    clock_t start, end;
    start = clock();
    KMP(pattern, txt);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    printf("\nTime taken: %f ms\n", time_taken);

    return 0;
}