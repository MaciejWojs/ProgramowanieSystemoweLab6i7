#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int fork_status = fork();
    if (fork_status == -1) {
        perror("Fork failed");
        return 1;
    }

    if (fork_status == 0) {
        // Kod procesu potomnego
        printf("\n\n");
        printf("Jestem procesem potomnym, mój PID to %d, PPID: %d\n", getpid(), getppid());
        execl("SIGTERM.out", "", NULL);
        return 0; // Zakończenie potomka
    } else {
        // Kod procesu rodzica
        printf("Jestem procesem rodzicem (PID: %d, PPID: %d), PID potomka to %d\n", getpid(), getppid(), fork_status);

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

    return 0;
}