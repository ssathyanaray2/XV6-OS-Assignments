# XV6 Operating System Assigments

# Overview
One of the most interesting courses I took during my Master's was Operating Systems (OS). As part of the coursework, I worked on three assignments that deepened my understanding of OS concepts. I modified XV6 OS, a lightweight version of Linux, to explore its inner workings and gain hands-on experience. 

# Assignment 1

The coding task in this project is to implement a system service that allows user programs to obtain the number of invocation times of three different system calls, fork(), wait(), and exit().

Steps:

1) Implement the interface for user programs to use the system service

    Each system call should have a corresponding library function that user programs call to invoke the system call. Its like a wrapper function and interface to access the system call.

    **int get syscall count(int call_type)**: It returns number of invocation of a system call. call type, which specifies the system call of which the invocation times the caller intends to obtain(0 - fork(), 1-wait(), 2-exit())

    **int reset syscall count(void)**: This function resets of the invocation counters of all the three system calls to 0.

    files modified:
        user.h
        testcount.c
        Makefile
        usys.S


2) Implement the system calls for the service
    We need to implement the system calls corresponding the two interface fucntions detailed above. 

    files modified:
    syscall.c
    syscall.h

3) Implement the logic of the system service
    The service logic is fairly simple: maintain an invocation counter for each supported system call, increment the counter each time the system call is invoked, and reset it to 0 when the user program instructs so.

    file modified:
    sysproc.c

Key Takeaway:
understanding how the existing user commands and the associated system calls
are implemented.


For a detailed implementation, refer to this [file] in the repository. (./OS_Assignment1_SystemCall/xv6-syscall-mechanisms.pdf)


# Assignment 2



# Assignment 3


# Instructions to run each of the project


