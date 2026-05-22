#include <stdio.h>
#define MAX_P 10
#define MAX_R 10

int n, m;

int Allocation[MAX_P][MAX_R];
int Max[MAX_P][MAX_R];
int Need[MAX_P][MAX_R];
int Available[MAX_R];


void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

int safetyAlgorithm() {
    int Work[MAX_R];
    int Finish[MAX_P] = {0};
    int SafeSequence[MAX_P];
    int count = 0;


    for (int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {

            if (Finish[i] == 0) {

                int possible = 1;


                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    SafeSequence[count++] = i;
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is in UNSAFE STATE!\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE.\n");
    printf("Safe Sequence: ");

    for (int i = 0; i < n; i++) {
        printf("P%d", SafeSequence[i]);

        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 1;
}

void resourceRequest() {
    int p;
    int Request[MAX_R];

    printf("\nEnter process number making request: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Request[i]);
    }

    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[p][i]) {
            printf("\nERROR: Process exceeded maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        if (Request[i] > Available[i]) {
            printf("\nResources not available. Process must wait.\n");
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[p][i] += Request[i];
        Need[p][i] -= Request[i];
    }

    printf("\nChecking system safety after allocation...\n");

    if (safetyAlgorithm()) {
        printf("\nRequest can be GRANTED.\n");
    }
    else {
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[p][i] -= Request[i];
            Need[p][i] += Request[i];
        }

        printf("\nRequest CANNOT be granted. Rolling back.\n");
    }
}

int main() {

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

    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    calculateNeed();

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    printf("\nInitial Safety Check:\n");
    safetyAlgorithm();

    resourceRequest();

    return 0;
}
