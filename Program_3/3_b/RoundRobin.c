/**
 * Problem Statement:
 * Implement Round Robin scheduling algorithm by defining process structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int responseTime;
    int waitingTime;
    int turnAroundTime;
    int remainingTime;
    int completionTime;
    bool isInQueue;
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

void roundRobinScheduling(int n, Process processes[], int quantum) {
    int currTime = processes[0].arrivalTime, totCompleted = 0;
    int totWT = 0, totRT = 0, totTAT = 0;
    int *waitQueue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    waitQueue[0] = 0;
    processes[0].isInQueue = true;

    printf("\nGantt Chart:\n");
    while (totCompleted != n) {
        if (front == (rear + 1) % n) {
            for (int i = 0; i < n; i++) {
                if (!processes[i].isInQueue) {
                    waitQueue[rear = (rear + 1) % n] = i;
                    processes[i].isInQueue = true;
                    currTime = processes[i].arrivalTime;
                    break;
                }
            }
        }

        int currIdx = waitQueue[front];
        front = (front + 1) % n;

        Process *currProcess = (processes + currIdx);

        if (currProcess->responseTime == -1) {
            totRT += currProcess->responseTime = currTime - currProcess->arrivalTime;
        }

        if (currProcess->remainingTime > quantum) {
            printf(
                "| (%d) P%d (%d) ",
                currTime,
                currProcess->pid,
                currTime + quantum
            );

            currProcess->remainingTime -= quantum;
            currTime += quantum;
        } else {
            printf(
                "| (%d) P%d (%d) ",
                currTime,
                currProcess->pid,
                currTime + currProcess->remainingTime
            );

            currTime += currProcess->remainingTime;
            currProcess->remainingTime = 0;
            totTAT += currProcess->turnAroundTime = currTime - currProcess->arrivalTime;
            totWT += currProcess->waitingTime = currProcess->turnAroundTime - currProcess->burstTime;
            currProcess->completionTime = currTime;

            currProcess->isInQueue = false;
            totCompleted++;
        }

        for (int i = 0; i < n && processes[i].arrivalTime <= currTime; i++) {
            if (!processes[i].isInQueue && processes[i].remainingTime > 0) {
                waitQueue[rear = (rear + 1) % n] = i;
                processes[i].isInQueue = true;
            }
        }

        if (currProcess->remainingTime > 0) {
            waitQueue[rear = (rear + 1) % n] = currIdx;
        }
    }

    printf("|\n");
    printProcesses(n, processes);
    printf("\nAverage Waiting Time: %.2f\n", (float) totWT / n);
    printf("Average Response Time: %.2f\n", (float) totRT / n);
    printf("Average Turn Around Time: %.2f\n", (float) totTAT / n);

    free(waitQueue);
}

void main() {
    int n, quantum;

    printf("\nEnter the number of Processes: ");
    scanf("%d", &n);
    printf("Enter the Quantum Time: ");
    scanf("%d", &quantum);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    printf("\nEnter the Processes:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].responseTime = -1;
        processes[i].isInQueue = false;

        printf("\nProcess P%d:", i + 1);
        printf("\nArrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    sortByArrivalTime(n, processes);
    roundRobinScheduling(n, processes, quantum);

    free(processes);
}
