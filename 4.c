#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
    int statusFork = fork();
    if (statusFork == -1) {
        perror("Fork failed");
        return 1;
    }

    if (statusFork == 0) {
        cpu_set_t cpuset;
        int cpu = 1;
        CPU_ZERO(&cpuset);
        CPU_SET(cpu, &cpuset);

        if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
            perror("sched_setaffinity failed");
            return 1;
        }

        int cpuChild = sched_getcpu();
        printf("Jestem procesem potomnym, mój PID to %d, PPID: %d\n", getpid(), getppid());
        printf("Aktualne CPU potomka: %d\n", cpuChild);
    } else {
        // Kod procesu rodzica
        int cpuParent = sched_getcpu();
        printf("Jestem procesem rodzicem (PID: %d, PPID: %d), PID potomka to %d\n", getpid(), getppid(), statusFork);
        printf("Aktualne CPU rodzica: %d\n", cpuParent);

        int child_status;
        pid_t child_pid = wait(&child_status);

        if (child_pid == -1) {
            perror("Wait failed");
            return 1;
        }

        if (WIFEXITED(child_status)) {
            printf("Zakończono proces potomny %d z kodem %d\n", child_pid, WEXITSTATUS(child_status));
        }

        if (WIFSIGNALED(child_status)) {
            printf("Proces potomny %d zniszczony sygnałem %d%s\n", child_pid, WTERMSIG(child_status),
                WCOREDUMP(child_status) ? " (wykonano zrzut systemowy)" : "");
        }
    }
}