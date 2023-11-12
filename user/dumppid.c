#include "user.h"

#define PGSIZE 4096 // bytes per page

int dumppid2(const int pid)
{
	int size = PGSIZE;
	char *addr = (char *)0x0;
	void *buffer = malloc(size);
	int res;
	uint i = 0; 

  	while (1) {
    	res = dump_alloc(pid, addr+i, buffer, size);

		if(res <= 0) break;

    	for (int j = 0; j < res; ++j) {
    		printf("addr: 0x%d: %d\n", addr + i + j, ((int*)buffer)[*addr + i + j]);
    	}

		i += res;  
  	}

	if(i == 0 && res <= 0) {
		printf("dump: fail to dump memory of pid %d\n", pid);
		return -1;
	}

  	free(buffer);
  	return 0;
}


int main(int argc, char *argv[])
{
	int pid;

	if(argc <= 1){

		pid = -1;
	}
	else{

		pid = atoi(argv[1]);
	}

    dumppid2(pid);
    exit(0);
}