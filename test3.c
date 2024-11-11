#include "types.h"
#include "user.h"

void find_primes(int nice_value) {
    int count = 0;
    int i = 2;

    // Print the starting message
    printf(1, "Process %d with nice value %d started\n", getpid(), nice_value);
    sleep(5);  // Small delay to reduce overlapping output

    while (count < 5) {
        int prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) {
            printf(1, "Process %d (nice %d) found prime: %d\n", getpid(), nice_value, i);
            sleep(5);  // Small delay after each prime found
            count++;
        }
        i++;
    }

    printf(1, "Process %d with nice value %d finished\n", getpid(), nice_value);
    sleep(5);  // Delay after finishing the process
}

int main(void) {
    int pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        nice(0, 5);  // Set nice value to 5
        find_primes(5);
        exit();
    }

    pid2 = fork();
    if (pid2 == 0) {
        nice(0, 5);  // Set nice value to 5
        find_primes(5);
        exit();
    }

    pid3 = fork();
    if (pid3 == 0) {
        nice(0, 5);  // Set nice value to 5
        find_primes(5);
        exit();
    }

    // Wait for all child processes to finish
    wait();
    wait();
    wait();
    exit();
}
