#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_nice(void)
{
    int pid, value;
    struct proc *p;
    int old_nice;

    // Fetch arguments from the user
    if(argint(0, &pid) < 0 || argint(1, &value) < 0)
        return -1;

    // Edge case handling: check if value is within bounds
    if (value < 0 || value > MAX_NICE) {
        return -1; // Return error for out-of-bound values
    }

    acquire(&ptable.lock);   // Lock the process table

    // Iterate over the process table to find the process by PID
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if(p->pid == pid) {       // Check if this is the target process
            old_nice = p->nice;   // Store old nice value before updating
            p->nice = value;      // Update to new nice value
           
            release(&ptable.lock);

            return old_nice;  // Return only the old nice value
        }
    }

    release(&ptable.lock);  // Unlock the process table if process is not found
    return -1;              // Process not found
}





int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
