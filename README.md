# XV6 Operating System Assigments

# Overview
One of the most interesting courses I took during my Master's was Operating Systems (OS). As part of the coursework, I worked on three assignments that deepened my understanding of OS concepts. I modified XV6 OS, a lightweight version of Linux, to explore its inner workings and gain hands-on experience. 

# **Assignment 1: System Call Invocation Counter**  

### **Objective**  
The goal of this assignment was to implement a system service that allows user programs to track the number of times the following system calls are invoked:  
- fork(), wait(), and exit().  

This involved modifying XV6 OS to introduce system calls that maintain invocation counters.  

## **Implementation Steps**  

### **1) Implement the User Program Interface**  
- Created wrapper functions to allow user programs to interact with the system service.  
- Implemented two interface functions:  

  **int get_syscall_count(int call_type)**;
  - Returns the number of times a system call has been invoked.  
  - call_type values:  
    - 0 → fork()  
    - 1 → wait()  
    - 2 → exit()  

  **int reset_syscall_count(void);**
  - Resets all three counters to 0.  

- **Files Modified:**  
  - user.h
  - testcount.c
  - Makefile
  - usys.S

### **2) Implement the System Calls**  
- Defined the new system calls that map to the user interface functions.  
- Integrated the calls into XV6’s syscall table.  

- **Files Modified:**  
  - syscall.c  
  - syscall.h

### **3) Implement the System Service Logic**  
- Maintained counters for each system call (fork, wait, exit).  
- Incremented the respective counter each time the system call was invoked.  
- Implemented logic to reset counters when instructed by the user.  

- **File Modified:**  
  - sysproc.c 

## **Key Takeaways**  
- Gained hands-on experience in XV6 system call mechanisms.  
- Understood how user commands interact with system calls in the OS.  
- Explored modifications to key OS files and syscall handling logic.  

For a detailed implementation, refer to [this file in the repository](./OS_Assignment_SharedMemoryPages/xv6-syscall-mechanisms).  


# Assignment 2: Alternate fork winner and stride scheduling algorithm

This assignment has two parts. In the first part, I analyzed how different operating systems handle process scheduling after a fork(). While some OSes prioritize the parent process, others allow the child to run first. By default, XV6 mostly schedules the parent first. I modified this behavior to alternate execution, ensuring that the parent and child processes take turns as the "fork winner" after a fork().

## **Implementation Steps** 

### **1) Implement the User Program Interface**  
- Created wrapper functions to allow user programs to interact with the system service.
- test function fork_rc_test.c to test the implementation.  
- Implemented interface function: 

    **void fork_alternate_winner(enable)** 
        - if the argument is 0, the alternating fork winner feature is disabled(default behaviour) and if the argument is 1 , the alternating fork winner feature is enabled.

- **File Modified:**  
  - fork_rc_test.c
  - user.h
  - Makefile
  - usys.S

### **2) Implement the System Calls**  
- Defined the new system calls that map to the user interface functions.  
- Integrated the calls into XV6’s syscall table.

- **Files Modified:**  
  - syscall.c  
  - syscall.h

### **3) Implement the System call Logic**  
- Based on the argument integer value set a variable in sysproc.c
- Based on the value set by the system call, modify the code for sys_fork. If the value is 1, use yeild to alternate the winner. 

- **File Modified:**  
  - sysproc.c (sys_fork(), sys_fork_alternate_winner())


In the second part, I implemented stride scheduler instead of default round robin scheduling in XV6. Stride Scheduling is a proportional-share CPU scheduling algorithm that ensures processes receive CPU time based on assigned priorities. Each process is given a stride value based on its priority(number of tickets in our case). A lower priority results in a higher stride value i.e., less frequent execution. A process cannot increase its own tickets. But it can transfer its own tickets to another process.

## **Implementation Steps** 

### **1) Implemented user-interface and system call
- Implemented a system call and user interface similar using similar steps as mentioned above to control whether the default policy (RR) is used or the stride scheduling policy is used.
- Implemented a system call and user interface to get the number of tickets owned by a process.
- Implement the functionality that allows a user process to transfer its own tickets to another process.

    **void set_sched(int)** 
        - 0 : default shceduling(RR)
        - 1 : stride scheduling

    **int tickets_owned(int pid)**
        -  return number of process owned by the process with PID equal to pid.
    
    **int transfer_tickets(int pid, int tickets)**
        - transfers the specified number of tickets from the calling process to the process with PID equal to pid.

- **Files Modified:**  
    - fork_rc_test.c
    - usys.S
    - Makefile
    - user.h
    - syscall.c
    - syscall.h
    - sysproc.c


### **2) Implement logic for ticketing and stride scheduling
- Implemented function to assignTickets, the tickets should be equally distributed among the existing process and if a new process is created(total number of tickets in the system is 100).
- Used assignTickets in fork() system call.
- Implemenation of stride scheduling and assign cpu to the process wihch as lowest pass value.

- **Files Modified:**  
    - proc.c (functions modified: assignTickets(), scheduler(), fork())

## **Key Takeaways**  
- Became confortable in writing system calls
- Understood different sheduling algorithm and their implementation
- Understood the working of process table, user mode and kernal mode.
- Understood the concept of different states of a process from creation to termination.

# Assignment 3 - Interprocess communication and Shared memory pages
In this project, I have implemented functionality where the two pages after the user stack page are used as shared memory pages which can be used for inter-process communication among different processes. In other words, the (n + 3)-th page and the (n + 4)-th page in an address space are reserved as shared memory page, where 'n' is the number of pages used for the process code and data. 

The first shared memory page is mapped to physical memory statically when an address space is initialized. Therefore, we call this page in an address space the statically mapped shared memory page (SMSMP). The second shared memory page should be mapped to physical memory dynamically when a process first writes on it. Therefore, we call this page in an address space the dynamically mapped shared memory page (DMSMP).

### **1) Implemented user-interface and system call
- 
- 
    **char* get_shared_page_addr(int type)**
        - return address of shared memory page.
        - 0: statically mapped shared memory page
        - 1: dynamically mapped shared memory

- **Files Modified:**  
    - shmtest12.c
    - shmtest34.c
    - usys.S
    - Makefile
    - user.h
    - syscall.c
    - syscall.h
    - sysproc.c

### **2) Implement Logic for SMSMP and DMSMP
- Implement logic for SMSMP in exec.c, statically a memory of size equal to PGSIZE(page size) is allocated as SMSMP and update process table about the address of the page.
- Implement logic for DMSMP in exec.c using mappage function in vm.c, a custom funtion map the page dynamically when a process writes to that location. This function is run as a part of interrupt service routine.

- **Files Modified:**
    - proc.c
    - exec.c
    - main.c
    - proc.h
    - vm.c
    - defs.h
    - trap.c

## **Key Takeaways**  
- Understand address space layout of process described in exec.c
- Understand the functioning of interrupts and implementation of traps and interrup service routines.
- Deep dive into different form of interprocess communication and implement shared memory pages.


# Instructions to run each of the project


