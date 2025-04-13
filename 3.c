#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child(void) {
    printf("\n\n");
    printf("Jestem procesem potomnym, mój PID to %d, PPID: %d\n", getpid(), getppid());
    execl("SIGTERM.out", "", NULL);
}

void zinterpretuj(int status, pid_t child_pid) {
    if (child_pid == -1) {
        perror("Wait failed");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Zakończono proces potomny %d z kodem %d\n", child_pid, WEXITSTATUS(status));
    }

    if (WIFSIGNALED(status)) {
        printf("Proces potomny %d zniszczony sygnałem %d%s\n", child_pid, WTERMSIG(status),
            WCOREDUMP(status) ? " (wykonano zrzut systemowy)" : "");
    }
}

int main(void) {
    int fork_status = fork();
    if (fork_status == -1) {
        perror("Fork failed");
        return 1;
    }

    if (fork_status == 0) {
        // Kod procesu potomnego
        child();
        return 0; // Zakończenie potomka
    } else {
        // Kod procesu rodzica
        printf("Jestem procesem rodzicem (PID: %d, PPID: %d), PID potomka to %d\n", getpid(), getppid(), fork_status);

        int child_status;
        pid_t child_pid = wait(&child_status);
        zinterpretuj(child_status, child_pid);
    }

    fork_status = fork();
    if (fork_status == -1) {
        perror("Fork failed");
        return 1;
    }

    if (fork_status == 0) {
        // Kod procesu potomnego
        child();
        return 0; // Zakończenie potomka
    } else {
        int child_status;
        pid_t child_pid = wait(&child_status);
        zinterpretuj(child_status, child_pid);
    }

    return 0;
}