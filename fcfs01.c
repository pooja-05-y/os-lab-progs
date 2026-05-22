#include <stdio.h>

int main() {
    int n, i, sum1, sum2, sum3;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    float avgtat, avgwt, avgrt;

    sum1 = sum2 = sum3 = 0;

    for(i=0;i<n;i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    ct[0] = at[0] + bt[0];

    for(i=1;i<n;i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    for(i=0;i<n;i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];
    }

    for(i=0;i<n;i++){
        sum1 += tat[i];
        sum2 += wt[i];
        sum3 += rt[i];
    }

    avgtat = (float)sum1 / n;
    avgwt  = (float)sum2 / n;
    avgrt  = (float)sum3 / n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage TAT: %.2f\nAverage WT: %.2f\nAverage RT: %.2f\n",
           avgtat, avgwt, avgrt);

    return 0;
}
