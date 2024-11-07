#include "types.h"
#include "user.h"

int main(void) {
    int pid = fork();
    if(pid == 0) {
        // Child process
        printf(1, "Child process with PID %d\n", getpid());
        while(1) {} // Infinite loop to keep process running
    } else {
        // Parent process: change child's nice value
        sleep(10); // Ensure child process has started
        int old_value = nice(pid, 10);
        printf(1, "Changed nice value of PID %d from %d to 10\n", pid, old_value);
        wait();
    }
    exit();
}
