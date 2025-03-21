#include "types.h"
#include "user.h"

/* IMPORTANT INSTRUCTION: the test code below should not be changed. 
   Failure to follow this instruction will lead to zero point for this part */

#define TOTAL_TEST_TRIALS 50
#define SCHEDULER_DEFAULT  0
#define SCHEDULER_STRIDE 1

int
main(int argc, char *argv[])
{
    int i = 0;
    int w = 0;
    int ret = 0;

    if (argc < 2)
    {
        printf(1, "Usage: %s 0|1 \n"
                  "\t0: Disable alternating fork winner\n"
                  "\t1: Enable alternating fork winner\n", argv[0]);
        exit();
    }

    if (argv[1][0] == '0')
    {
        w = 0;
        printf(1, "\nDisable alternating fork winner ...\n");
    }
    else
    {
        w = 1;
        printf(1, "\nEnable alternating fork winner ...\n");
    }

    fork_alternate_winner(w); // set according to user input
    set_sched(SCHEDULER_DEFAULT); 
    
    for (i = 0; i < TOTAL_TEST_TRIALS; i++)
    {
        printf(1, "\nTrial %d: ", i);
        ret = fork();
        if (ret < 0)
        {
            printf(1, "fork() failed (%d)\n", ret);
            exit();
        }
        else if (ret == 0) // child
        {
            printf(1, " child! ");
            exit();
        }

        // parent
        printf(1, " parent! ");
        if (ret != wait())
        {
            printf(1, "wait() failed!\n");
        }
    }

    printf(1, "\n");

    if (w)
    {
        fork_alternate_winner(0); // set back to default
    }

    exit();
}

