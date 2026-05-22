#include<stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, start_time;
};

int main() {
    int n, tq;
    struct Process p[20];
    int queue[100];
    int visited[20] = {0}; // Track if added to queue
    int front = 0, rear = 0;
    int time = 0, completed = 0;
    int order[200];
    int timeMark[200];
    int k = 0;
    float avgwt = 0, avgtat = 0, avgrt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].start_time = -1; // Initialize start time
    }

    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Initial check: Add process with earliest AT to queue
    queue[rear++] = 0;
    visited[0] = 1;
    time = p[0].at;
    timeMark[0] = time;

    while (completed < n && front < rear) {
        int idx = queue[front++];

        // Record start time for Response Time
        if (p[idx].start_time == -1) {
            p[idx].start_time = time;
        }

        order[k] = p[idx].pid;

        if (p[idx].rt > tq) {
            p[idx].rt -= tq;
            time += tq;
        } else {
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            avgwt += p[idx].wt;
            avgtat += p[idx].tat;
            avgrt += (p[idx].start_time - p[idx].at);
            completed++;
        }

        k++;
        timeMark[k] = time;

        // Check for new arrivals while the current process was running
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && visited[i] == 0 && i != idx && p[i].rt > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If current process not finished, add back to queue
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        }

        // If queue is empty but processes remain, skip time
        if (front == rear && completed < n) {
            for(int i=0; i<n; i++) {
                if(visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    time = p[i].at;
                    timeMark[k] = time;
                    break;
                }
            }
        }
    }

    printf("\n--- Round Robin Scheduling ---\n");
    printf("\nGantt Chart:\n");
    for (int i = 0; i < k; i++) printf("| P%d ", order[i]);
    printf("|\n");
    for (int i = 0; i <= k; i++) printf("%-5d", timeMark[i]);
    printf("\n\n");

    printf("Process\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].start_time - p[i].at);
    }

    printf("\nAverage TAT = %.2f", avgtat / n);
    printf("\nAverage WT = %.2f", avgwt / n);
    printf("\nAverage RT = %.2f\n", avgrt / n);

    return 0;
}
