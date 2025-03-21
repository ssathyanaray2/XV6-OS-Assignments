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


# Assignment 2




# Assignment 3


# Instructions to run each of the project


