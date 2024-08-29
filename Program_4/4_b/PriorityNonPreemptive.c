/**
 * Problem Statement:
 * Implement Priority Non-preemptive scheduling algorithm by defining process structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
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
    printf("\nPID\tAT\tBT\tCT\tPRT\tRT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        const Process *currProcess = (processes + i);

        printf(
            "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            currProcess->pid,
            currProcess->arrivalTime,
            currProcess->burstTime,
            currProcess->completionTime,
            currProcess->priority,
            currProcess->responseTime,
            currProcess->waitingTime,
            currProcess->turnAroundTime
        );
    }
}

void priorityScheduling(int n, Process processes[]) {
    int currTime = processes[0].arrivalTime, totCompleted = 0;
    int totWT = 0, totRT = 0, totTAT = 0;

    printf("\nGantt Chart:\n");
    while (totCompleted != n) {
        int currIdx = -1, maxPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            Process *currProcess = (processes + i);
            if (currProcess->arrivalTime <= currTime) {
                if (!currProcess->isCompleted && currProcess->priority < maxPriority) {
                    maxPriority = currProcess->priority;
                    currIdx = i;
                }
            } else {
                break;
            }
        }

        if (currIdx != -1) {
            Process *currProcess = (processes + currIdx);

            totWT += currProcess->waitingTime = currTime - currProcess->arrivalTime;
            totRT += currProcess->responseTime = currProcess->waitingTime;
            currTime += currProcess->burstTime;
            totTAT += currProcess->turnAroundTime = currTime - currProcess->arrivalTime;
            currProcess->completionTime = currTime;

            printf(
                "| (%d) P%d (%d) ",
                currTime - currProcess->burstTime,
                currProcess->pid,
                currTime
            );

            totCompleted++;
            currProcess->isCompleted = true;
        } else {
            currTime = INT_MAX;
            for (int i = 0; i < n; i++) {
                int arrivalTime = processes[i].arrivalTime;
                if (!processes[i].isCompleted && arrivalTime < currTime) {
                    currTime = arrivalTime;
                }
            }
        }
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
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    sortByArrivalTime(n, processes);
    priorityScheduling(n, processes);

    free(processes);
}
