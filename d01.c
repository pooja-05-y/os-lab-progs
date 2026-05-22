

#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main() {

    int n, m;

    int Allocation[MAX_P][MAX_R];
    int Request[MAX_P][MAX_R];
    int Available[MAX_R];

    int Work[MAX_R];
    int Finish[MAX_P];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }


    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &Request[i][j]);
        }
    }
    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    for (int i = 0; i < n; i++) {

        int allZero = 1;

        for (int j = 0; j < m; j++) {
            if (Allocation[i][j] != 0) {
                allZero = 0;
                break;
            }
        }

        if (allZero)
            Finish[i] = 1;
        else
            Finish[i] = 0;
    }

    // Detection Algorithm
    int found;

    do {
        found = 0;

        for (int i = 0; i < n; i++) {

            if (Finish[i] == 0) {

                int possible = 1;

                // Check if Request[i] <= Work
                for (int j = 0; j < m; j++) {

                    if (Request[i][j] > Work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // If request can be satisfied
                if (possible) {

                    // Work = Work + Allocation[i]
                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    Finish[i] = 1;
                    found = 1;

                    printf("\nProcess P%d has finished.", i);
                }
            }
        }

    } while (found);

    // Check for deadlock
    int deadlock = 0;

    printf("\n\nDeadlocked Processes: ");

    for (int i = 0; i < n; i++) {

        if (Finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if (!deadlock)
        printf("None");

    if (deadlock)
        printf("\n\nSystem is in DEADLOCK state.\n");
    else
        printf("\n\nSystem is NOT in deadlock state.\n");

    return 0;
}
