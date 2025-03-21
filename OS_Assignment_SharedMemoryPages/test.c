#include "types.h"
#include "user.h"

#define PGSIZE 4096

int
main(int argc, char *argv[])
{
    char * page_addr = "0x3000";
    page_addr = get_shared_page_addr(0);
    char * test_str = "CS 550 Shared Memory Page Project";
    strcmp(test_str, page_addr) == 0 ? printf(1, "***PASSED***\n") : printf(1, "***FAILED***\n");
    printf(1, "\n");
}