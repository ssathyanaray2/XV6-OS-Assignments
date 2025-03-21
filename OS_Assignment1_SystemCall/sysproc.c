#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "stdio.h"

int forkcount = 0;
int waitcount = 0;
int exitcount = 0;

int
sys_fork(void)
{
  int returnValue = fork();
  forkcount=forkcount+1;
  return returnValue;
}

int
sys_exit(void)
{
  exitcount=exitcount+1;
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  waitcount=waitcount+1;
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

int sys_shutdown(void)
{
  /* Either of the following will work. Does not harm to put them together. */
  outw(0xB004, 0x0|0x2000); // working for old qemu
  outw(0x604, 0x0|0x2000); // working for newer qemu

  return 0;
  
}

int sys_get_syscall_count(int type){
    argint(0,&type);
    if(type==0){
      return forkcount;
    }
    else if(type==1){
      return waitcount;
    }
    else if(type==2){
      return exitcount;
    }
    else{
      return -1;
    }
}

int sys_reset_syscall_count(void){
    forkcount = 0;
    waitcount = 0;
    exitcount = 0;
    return 0;
}


