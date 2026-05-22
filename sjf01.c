#include <stdio.h>

int main() {
    int n, i, time = 0, smallest, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], start[n];
    int sumtat = 0, sumwt = 0, sumrt = 0;
    float avgtat, avgwt, avgrt;

    for(i=0;i<n;i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d",&at[i],&bt[i]);
        rt[i] = bt[i];      // remaining time
        start[i] = -1;      // to track response time
    }

    while(count != n) {

        smallest = -1;

        for(i=0;i<n;i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(smallest == -1 || rt[i] < rt[smallest])
                    smallest = i;
            }
        }

        if(smallest == -1) {
            time++;
            continue;
        }

        if(start[smallest] == -1)
            start[smallest] = time;

        rt[smallest]--;
        time++;

        if(rt[smallest] == 0) {
            count++;
            ct[smallest] = time;
        }
    }

    for(i=0;i<n;i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        int rt_time = start[i] - at[i];

        sumtat += tat[i];
        sumwt += wt[i];
        sumrt += rt_time;
    }

    avgtat = (float)sumtat/n;
    avgwt  = (float)sumwt/n;
    avgrt  = (float)sumrt/n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], start[i]-at[i]);
    }

    printf("\nAverage TAT: %.2f", avgtat);
    printf("\nAverage WT: %.2f", avgwt);
    printf("\nAverage RT: %.2f\n", avgrt);

    return 0;
}
