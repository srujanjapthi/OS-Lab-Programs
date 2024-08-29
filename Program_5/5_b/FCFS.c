/**
 * Implement FCFS scheduling algorithm by defining process structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int responseTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    bool isCompleted;
} Process;

void sortByArrivalTime(int n, Process processes[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void printProcesses(int n, Process processes[]) {
    printf("\nObservation Table:");
    printf("\nPID\tAT\tBT\tCT\tRT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        const Process *currProcess = (processes + i);

        printf(
            "%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            currProcess->pid,
            currProcess->arrivalTime,
            currProcess->burstTime,
            currProcess->completionTime,
            currProcess->responseTime,
            currProcess->waitingTime,
            currProcess->turnAroundTime
        );
    }
}

void fcfsScheduling(int n, Process processes[]) {
    int currTime = processes[0].arrivalTime, totCompleted = 0;
    int totWT = 0, totRT = 0, totTAT = 0;

    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > currTime) {
            currTime = processes[i].arrivalTime;
        }

        printf(
            "| (%d) P%d (%d) ",
            currTime,
            processes[i].pid,
            currTime + processes[i].burstTime
        );

        totWT = totRT += processes[i].responseTime = processes[i].waitingTime = currTime - processes[i].arrivalTime;
        processes[i].completionTime = currTime += processes[i].burstTime;
        totTAT += processes[i].turnAroundTime = currTime - processes[i].arrivalTime;
    }

    printf("|\n");
    printProcesses(n, processes);
    printf("\nAverage Waiting Time: %.2f\n", (float) totWT / n);
    printf("Average Response Time: %.2f\n", (float) totRT / n);
    printf("Average Turn Around Time: %.2f\n", (float) totTAT / n);
}

void main() {
    int n;
    printf("\nEnter the number of Processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    printf("\nEnter the Processes:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].isCompleted = false;

        printf("\nProcess P%d:", i + 1);
        printf("\nArrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    sortByArrivalTime(n, processes);
    fcfsScheduling(n, processes);

    free(processes);
}
