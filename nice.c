#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid, value, old_value;

    if (argc == 3) {
        // If PID and value are provided
        pid = atoi(argv[1]);
        value = atoi(argv[2]);
    } else if (argc == 2) {
        // If only value is provided, assume it’s for the current process
        pid = getpid();
        value = atoi(argv[1]);
    } else {
        // Print usage if arguments are incorrect and exit
        printf(1, "Usage: nice <pid> <value> or nice <value>\n");
        exit();
    }

    // Call the `nice` system call with pid and value
    old_value = nice(pid, value);

    if (old_value < 0) {
        // If nice returned a negative value, it indicates an error
        printf(1, "Error: Invalid PID or nice value\n");
    } else {
        // Print the PID and the old nice value before the change
        printf(1, "%d %d\n", pid, old_value);  // Expected output format
    }

    exit();
}
