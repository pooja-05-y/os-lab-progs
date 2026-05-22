#include <stdio.h>

struct process {
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int rt;
    int remaining;
    int visited;
};

int main() {

    int n, time = 0, completed = 0, i, highest;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct process p[n];

    for(i=0;i<n;i++){
        p[i].pid = i + 1;
        printf("Enter AT, BT and Priority for P%d: ",p[i].pid);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pr);

        p[i].remaining = p[i].bt;
        p[i].visited = 0;
    }

    int sumtat=0, sumwt=0, sumrt=0;
    float avgtat, avgwt, avgrt;

    while(completed < n){

        highest = -1;

        for(i=0;i<n;i++){
            if(p[i].at <= time && p[i].remaining > 0){
                if(highest == -1 || p[i].pr < p[highest].pr)
                    highest = i;
            }
        }

        if(highest == -1){
            time++;
            continue;
        }

        if(p[highest].visited == 0){
            p[highest].rt = time - p[highest].at;
            p[highest].visited = 1;
        }

        p[highest].remaining--;
        time++;

        if(p[highest].remaining == 0){

            p[highest].ct = time;
            completed++;

            p[highest].tat = p[highest].ct - p[highest].at;
            p[highest].wt = p[highest].tat - p[highest].bt;

            sumtat += p[highest].tat;
            sumwt += p[highest].wt;
            sumrt += p[highest].rt;
        }
    }

    avgtat = (float)sumtat / n;
    avgwt = (float)sumwt / n;
    avgrt = (float)sumrt / n;

    printf("\nP\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,
        p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

    printf("\nAverage TAT: %.2f",avgtat);
    printf("\nAverage WT: %.2f",avgwt);
    printf("\nAverage RT: %.2f\n",avgrt);

    return 0;
}
