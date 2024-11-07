#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid, value, old_value;

    if(argc == 3) {
        // If PID and value are provided
        pid = atoi(argv[1]);
        value = atoi(argv[2]);
    } else if(argc == 2) {
        // If only value is provided, assume it’s for the current process
        pid = getpid();
        value = atoi(argv[1]);
        printf(1, "Current PID: %d\n", pid);  // Debug: Print the current process PID
    } else {
        printf(2, "Usage: nice <pid> <value> or nice <value>\n");
        exit();
    }

    // Call the `nice` system call with pid and value
    old_value = nice(pid, value);

    if(old_value < 0) {
        printf(2, "Error: Invalid PID or nice value\n");
    } else {
        printf(1, "%d %d\n", pid, old_value);  // Print PID and old nice value only
    }

    exit();
}
