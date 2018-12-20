#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern struct PTABLE ptable;

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


int
sys_addToTicket(void){
  int n;
  if(argint(0, &n) < 0)
    return -1;
  struct proc *curproc = myproc();
  acquire(&ptable.lock);
  curproc->queue = TICKET;
  curproc->ticket_num = n;
  release(&ptable.lock);
  return 0;
}

int
sys_addToFCFS(void){
  struct proc *curproc = myproc();
  acquire(&ptable.lock);
  curproc->queue = FCFS;
  release(&ptable.lock);
  return 0;
}

int
sys_addToPriority(void){
  int n;
  if(argint(0, &n) < 0)
    return -1;
  struct proc *curproc = myproc();
  acquire(&ptable.lock);
  curproc->queue = PRIORITY;
  curproc->priority = n;
  release(&ptable.lock);
  return 0;
}

int
sys_logProcs(void){
  cprintf("name\t\tpid\t\tstate\t\tpriority\t\tticketNumbet\t\tcreateTime\n");
  cprintf("---------------------------------------------------------------------");
  struct proc* p;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    else{
      cprintf("%c\t\t%d\t\t",p->name,p->pid);
      switch(p->state){
        case EMBRYO:
          cprintf("EMBRYO");
          break;
        case SLEEPING:
          cprintf("SLEEPING");
          break;
        case RUNNABLE:
          cprintf("RUNNABLE");
          break;
        case RUNNING:
          cprintf("RUNNING");
          break;
        case ZOMBIE:
          cprintf("ZOMBIE");
          break;
        default:
          break;
      }
      cprintf("\t\t");
      if(p->queue == PRIORITY){
        cprintf("%d\t\t",p->priority);
      }
      else{
        cprintf("-\t\t");
      }

      if(p->queue == TICKET){
        cprintf("%d\t\t",p->ticket_num);
      }
      else{
        cprintf("-\t\t");
      }

      cprintf("%d\n",p->started_time);
    }
  }
  return 0;
}
