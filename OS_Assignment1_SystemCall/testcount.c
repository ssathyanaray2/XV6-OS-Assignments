#include "types.h"
#include "stat.h"
#include "user.h"


void test_count(int loop){
    int fork_count =0;
    int exit_count =0;
    int wait_count =0;

    reset_syscall_count();
    for(int i=0; i<loop; i++){

        int val = fork();
        if(val<0){
            printf(1, "fork failed\n");
            exit();
        }
        else if(val==0){
            exit();
        }
        else{
            wait();
        }
    }

    fork_count = get_syscall_count(0);
    exit_count = get_syscall_count(2);
    wait_count = get_syscall_count(1);

    printf(1, "Expected Results: fork[%d] exit[%d] wait[%d]\n", loop, loop, loop);
    printf(1, "Actual Results: fork[%d] exit[%d] wait[%d]\n", fork_count, exit_count, wait_count);
}

//Test error condition.
void test_count_1(){
    int val = get_syscall_count(-1);
    if(val==-1){
        printf(1, "Expected Result for invalid input: [-1]\n");
        printf(1, "Actual Result for invalid input: [%d]\n", val);
    }
}

int main(int argc, char* argv[])
{
    test_count(9);
    test_count_1(100);
    exit();
}


// #include "types.h"
// #include "user.h"
// #define P_LOOP_CNT 0x10000000
// #define C_LOOP_CNT 0x20000000


// unsigned int avoid_optm = 0; // a variable used to avoid compiler optimization
// void do_parent(void)
// {
//     unsigned int cnt = 0;
//     unsigned int tmp = 0;
//     while(cnt < P_LOOP_CNT)
//     {
//         tmp += cnt;
//         cnt ++;
//     }
    
//     avoid_optm = tmp;
// }
// void do_child(void)
// {
//     unsigned int cnt = 0;
//     unsigned int tmp = 0;
//     while(cnt < C_LOOP_CNT)
//     {
//         tmp += cnt;
//         cnt ++;
//     }
    
//     avoid_optm = tmp;
// }
// void example_test_code()
// {
//     int pid = 0;

//     pid = fork();
//     if (pid < 0)
//     {
//         printf(1, "fork() failed!\n");
//         exit();
//     }
//     else if (pid == 0) // child
//     {
//         //sleep(100);
//         do_child();
//     }
//     else // parent
//     {
//         do_parent();
//         if (wait() < 0)
//         {
//             printf(1, "wait() failed!\n");
//         }
//     }
	
// 	printf(1, "\n");
// }

// int
// main(int argc, char *argv[])
// {

//     printf(1,"1d");
//     example_test_code();

//     printf(1,"2d");
//     example_test_code();

//     printf(1,"3d");
//     example_test_code();

//     printf(1,"4d");
//     example_test_code();

//     exit();
// }