/**
 * Problem Statement:
 * Write a program to demonstrate zombie process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t my_pid, child_pid, parent_pid;

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (!child_pid) {
        // Child Process
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] This is the child Process...\n");
        printf("[CHILD] My PID is %d\n", my_pid);
        printf("[CHILD] My parent's PID is %d\n", parent_pid);
        printf("[CHILD] I've Completed my execution... Exiting...\n");
        exit(0);
    } else {
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] This is the Parent Process...\n");
        printf("[PARENT] My PID is %d\n", my_pid);
        printf("[PARENT] My parent's PID is %d\n", parent_pid);
        printf("[PARENT] My child's PID is %d\n", child_pid);
        printf("[PARENT] Let me sleep for 10 seconds...\n");
        sleep(10);
        printf("[PARENT] Execution of the process is completed...\n");
    }
}
