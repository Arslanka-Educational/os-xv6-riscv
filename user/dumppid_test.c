#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/fcntl.h"
#include "kernel/memlayout.h"
#include "user/user.h"

void
test0() {
    printf("dumppid_test: start\n");
  
    uint64 addr = { 0x80000000LL};
    int fd = open("copyin1", O_CREATE|O_WRONLY);
    if(fd < 0){
      printf("open(copyin1) failed\n");
      exit(1);
    }
    int n = write(fd, (void*)addr, 8192);
    if(n >= 0){
      printf("write(fd, %p, 8192) returned %d, not -1\n", addr, n);
      exit(1);
    }
    close(fd);
    unlink("copyin1");

    int pid = getpid();

    int size = PGSIZE;
	  char *address = (char *)0x0;
	  void *buffer = malloc(size);
	  int res;
	  uint i = 0; 

    while (1) {
      res = dump_alloc(pid, address+i, buffer, size);

	    if(res <= 0) break;

      for (int i = 0; i < size; ++i) {
        printf("addr %s:        %s\n", addr + i, ((int*)buffer)[*address + i]);
      }

	    i = i + res;  
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  test0();
  exit(0);
}