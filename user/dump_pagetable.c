#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pid;

	if(argc <= 1)
    {
        pid = -1;
	}
	else
    {
		pid = atoi(argv[1]);
	}
    dumppagetable(pid);
    exit(0);
}