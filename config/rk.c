#include <stdio.h>
#include <string.h>
#include <time.h>


#define d 256
#define q 101
#define max 100

void rabinKarp(char txt[], char pat[]){
    int m = strlen(pat);
    int n = strlen(txt);

    int p = 0;
    int t = 0;
    int h = 1;

    for(int i = 0; i<m-1; i++){
        h = (h*d)%q;
    }

    for(int i = 0; i<m; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }

    for(int i = 0; i<=n-m; i++){
        if(p==t){
            int match = 1;
            for(int j = 0; j<m; j++){
                if(txt[j+i]!=pat[j]){
                    match = 0;
                    break;
                }
            }

            if(match){
                printf("%d\n", i);
            }
        }

        if(i<n-m){
            t = (d*(t-txt[i]*h)+txt[i+m])%q;

            if(t<0){
                t = t+q;
            }
        }
    }
}

int main() {

    char txt[max], pat[max];

    printf("Enter text: ");
    scanf("%s", txt);

    printf("Enter pattern: ");
    scanf("%s", pat);

    clock_t start, end;

    start = clock();

    rabinKarp(txt, pat);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Time taken: %f ms\n", time_taken);

    return 0;
}