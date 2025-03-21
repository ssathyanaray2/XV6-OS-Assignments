#include "types.h"
#include "user.h"

#define P_LOOP_CNT 0x10000000
#define C_LOOP_CNT 0x20000000

unsigned int avoid_optm = 0; // a variable used to avoid compiler optimization
void do_parent(void)
{
    unsigned int cnt = 0;
    unsigned int tmp = 0;

    while(cnt < P_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
    
    avoid_optm = tmp;
}


void do_child(void)
{
    unsigned int cnt = 0;
    unsigned int tmp = 0;

    while(cnt < C_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
    
    avoid_optm = tmp;
}

void example_test_code()
{
    int pid = 0;

    pid = fork();
    //fork();

    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        do_child();
    }
    else // parent
    {
        int tickets_at_parent = tickets_owned(getpid());
        printf(1,"pid: %d tickets: %d\n",getpid(), tickets_at_parent);
        int tickets_at_child = tickets_owned(pid);
        printf(1,"pid: %d tickets: %d\n",pid, tickets_at_child);
        do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
	
	printf(1, "\n");
}

void example_test_code_two()
{
    int pid = 0;

    pid = fork();

    if(pid>0){
        int returnVal = transfer_tickets(pid,-2);
        printf(1,"%d\n",returnVal);
        int tickets_at_parent = tickets_owned(getpid());
        returnVal = transfer_tickets(pid,tickets_at_parent+1);
        printf(1,"%d\n",returnVal);
        returnVal = transfer_tickets(65,tickets_at_parent-1);
        printf(1,"%d\n",returnVal);
        returnVal = transfer_tickets(pid,tickets_at_parent/2);
        printf(1,"%d\n",returnVal);
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }

    }

    else if (pid == 0) // child
    {
    }
}


void example_test_code_three()
{
    int pid = 0;

    pid = fork();

    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        do_child();
        exit();
    }
    else // parent
    {

        int tickets_at_parent = tickets_owned(getpid());
        int returnVal = transfer_tickets(pid,tickets_at_parent/2);
        tickets_at_parent = tickets_owned(getpid());
        printf(1,"pid: %d tickets: %d\n",getpid(), tickets_at_parent);
        int tickets_at_child = tickets_owned(pid);
        printf(1,"pid: %d tickets: %d\n",pid, tickets_at_child);
        printf(1,"%d", returnVal);
        do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
	
	printf(1, "\n");

 }

void example_test_code_four()
{
    int pid = 0;

    pid = fork();

    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        do_child();
        exit();
    }
    else // parent
    {

        int tickets_at_parent = tickets_owned(getpid());
        int returnVal = transfer_tickets(pid,tickets_at_parent-1);
        tickets_at_parent = tickets_owned(getpid());
        printf(1,"pid: %d tickets: %d\n",getpid(), tickets_at_parent);
        int tickets_at_child = tickets_owned(pid);
        printf(1,"pid: %d tickets: %d\n",pid, tickets_at_child);
        printf(1,"%d", returnVal);
        do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
	
	printf(1, "\n");

 }


int
main(int argc, char *argv[])
{
    enable_sched_trace(1);

    /* ---------------- start: add your test code ------------------- */
    /* ---------------- test case 1 ------------------- */

    // set_sched(0);
    // example_test_code();
    

    // /* ---------------- test case 2 ------------------- */

    // printf(1,"\n");
    // set_sched(1);
    // example_test_code();
    // set_sched(0);

    // /* ---------------- test case 3 ------------------- */

    // set_sched(1);
    // example_test_code_two();
    // set_sched(0);

    // /* ---------------- test case 4 ------------------- */

    set_sched(1);
    example_test_code_three();
    set_sched(0);
    

    // sleep(100);
    // /* ---------------- test case 5 ------------------- */


    // set_sched(1);
    // example_test_code_four();
    // set_sched(0);

    // /* ---------------- end: add your test code ------------------- */

    enable_sched_trace(0);
    
    exit();
}
