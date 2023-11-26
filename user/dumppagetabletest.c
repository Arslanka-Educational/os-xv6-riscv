#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/fcntl.h"
#include "kernel/memlayout.h"
#include "user/user.h"

void
test0() {
    printf("dumppagetabletest: start\n");
  
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
    printf("###################################\n");
    printf("            EXPECTED               \n");
    printf("...    0: pte 0x00000000200a1c01 pa 0x0000000080287000 ---  ||   \n");
    printf("... ...    0: pte 0x00000000200a2001 pa 0x0000000080288000 ---  ||  [\n");
    printf("... ... ...    0: pte 0x00000000200a185b pa 0x0000000080286000 r-x  ||  �\"�&�\n");
    printf("... ... ...    1: pte 0x00000000200a2417 pa 0x0000000080289000 rw-  ||  \n");
    printf("... ... ...    2: pte 0x00000000200a2807 pa 0x000000008028a000 rw-  ||  \n");
    printf("... ... ...    3: pte 0x00000000200a2cd7 pa 0x000000008028b000 rw-  ||  \n");
    printf("...    255: pte 0x00000000200a1001 pa 0x0000000080284000 ---  ||  \n");
    printf("... ...    511: pte 0x00000000200a1401 pa 0x0000000080285000 ---  ||  \n");
    printf("... ... ...    510: pte 0x0000000021ff5cc7 pa 0x0000000087fd7000 rw-  ||  �\n");
    printf("... ... ...    511: pte 0x000000002000204b pa 0x0000000080008000 r-x  ||  s7\n");
    printf("###################################\n\n");

    printf("            ACTUAL               \n");
    dumppagetable(pid);
    printf("###################################\n\n");
}

int
main(int argc, char *argv[])
{
  test0();
  exit(0);
}