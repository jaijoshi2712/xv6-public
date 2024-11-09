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
       
    } else {
       
        exit();
    }

    // Call the `nice` system call with pid and value
    old_value = nice(pid, value);

    if(old_value < 0) {
        
    } else {
       
    }

    exit();
}
