#include "types.h"
#include "stat.h"
#include "user.h"

void prime_number_task(int limit, int pid, int nice_value) {
    int i, j, is_prime, count = 0;

    printf(1, "Process %d with nice value %d started\n", pid, nice_value);

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
            sleep(5); // Small delay to reduce interleaving
        }
    }

    printf(1, "Process %d with nice value %d finished\n", pid, nice_value);
}

int main() {
    int pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        nice(0, 1); // Higher priority (low nice value)
        prime_number_task(10, getpid(), 1); // Limit to 10 primes
        exit();
    }

    pid2 = fork();
    if (pid2 == 0) {
        nice(0, 5); // Medium priority
        prime_number_task(10, getpid(), 5); // Limit to 10 primes
        exit();
    }

    pid3 = fork();
    if (pid3 == 0) {
        nice(0, 9); // Lower priority (high nice value)
        prime_number_task(10, getpid(), 9); // Limit to 10 primes
        exit();
    }

    // Wait for all child processes to finish
    wait();
    wait();
    wait();

    exit();
}
