#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0, shortest;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    int visited[n];
    int sumtat = 0, sumwt = 0, sumrt = 0;
    float avgtat, avgwt, avgrt;

    for(i=0;i<n;i++){
        printf("Enter Arrival Time and Burst Time for P%d: ",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        visited[i] = 0;
    }

    while(completed < n){

        shortest = -1;

        for(i=0;i<n;i++){
            if(at[i] <= time && visited[i]==0){
                if(shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if(shortest == -1){
            time++;
            continue;
        }

        time += bt[shortest];
        ct[shortest] = time;
        visited[shortest] = 1;
        completed++;

        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];
        rt[shortest] = wt[shortest];

        sumtat += tat[shortest];
        sumwt += wt[shortest];
        sumrt += rt[shortest];
    }

    avgtat = (float)sumtat / n;
    avgwt  = (float)sumwt / n;
    avgrt  = (float)sumrt / n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage TAT: %.2f",avgtat);
    printf("\nAverage WT: %.2f",avgwt);
    printf("\nAverage RT: %.2f\n",avgrt);

    return 0;
}
