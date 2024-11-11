#include "types.h"
#include "stat.h"
#include "user.h"

void prime_number_task(int limit, int pid, int nice_value) {
    int i, j, is_prime, count = 0;

    // Starting message with a delay
    printf(1, "Process %d with nice value %d started\n", pid, nice_value);
    sleep(20);

    for (i = 2; count < limit; i++) {
        is_prime = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            printf(1, "Process %d (nice %d) found prime: %d\n", pid, nice_value, i);
            count++;
            sleep(20); // Delay after printing each prime
        }
    }

    printf(1, "Process %d with nice value %d finished\n", pid, nice_value);
    sleep(20); // Delay to separate finishing message
}

int main() {
    int pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 == 0) {
        nice(0, 1); // Highest priority
        prime_number_task(5, getpid(), 1);
        exit();
    }

    pid2 = fork();
    if (pid2 == 0) {
        nice(0, 3); // Medium-high priority
        prime_number_task(5, getpid(), 3);
        exit();
    }

    pid3 = fork();
    if (pid3 == 0) {
        nice(0, 5); // Medium-low priority
        prime_number_task(5, getpid(), 5);
        exit();
    }

    pid4 = fork();
    if (pid4 == 0) {
        nice(0, 9); // Lowest priority
        prime_number_task(5, getpid(), 9);
        exit();
    }

    wait();
    wait();
    wait();
    wait();

    exit();
}
