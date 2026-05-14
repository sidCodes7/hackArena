#include <stdio.h>

int main(){
    int at[5] = {0,1,2,3,4};
    int bt[5] = {6,4,2,3,1};
    int wt[5], tat[5], ct[5];

    float avg_wt = 0;

    wt[0] = 0;
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];

    for(int i = 1; i<5; i++){
        wt[i] = ct[i-1] - at[i];
        if(wt[i]<0){
            wt[i] = 0;
        }
        ct[i] = at[i] + wt[i] + bt[i];
        tat[i] = ct[i] - at[i];
    }

    printf("\nGantt Chart:\n");
    printf("0--P1--6--P2--10--P3--12--P4--15--P5--16\n");

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(int i = 0; i < 5; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], wt[i], tat[i]);

        avg_wt += wt[i];
    }
    avg_wt /= 5;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;

}