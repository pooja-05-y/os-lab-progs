#include <stdio.h>

struct Process {
    int id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int type;
    int done;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].done = 0;

        printf("\nProcess %d\n", i + 1);

        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);

        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);
    }

    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1;

        for (int priority = 0; priority <= 1; priority++) {
            for (int i = 0; i < n; i++) {
                if (!p[i].done && p[i].at <= time && p[i].type == priority) {
                    if (idx == -1 || p[i].at < p[idx].at)
                        idx = i;
                }
            }
            if (idx != -1) break;
        }

        if (idx != -1) {
            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].done = 1;
            completed++;
        } else {
            time++;
        }
    }


    float totalWT = 0, totalTAT = 0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].type == 0 ? "System" : "User",
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}

