#include "user.h"

int main() {
    int fd[2] = {0, 0};

    if (pipe(fd) < 0) {
        printf("pipe failed\n");
        exit(1);
    }

    int pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (pid == 0) { // child 
        char buf[8];
        read(fd[0], buf, sizeof buf);
        printf("<%d> got <%s>\n", pid, buf);

        write(fd[1], "pong", 4);
        close(fd[1]);
        exit(0);
    } else { // parent
        write(fd[1], "ping", 4);
        close(fd[1]);
      
        char buf[8];
        read(fd[0], buf, sizeof buf);
        printf("<%d> got <%s>\n", pid, buf);
    }

    exit(0);
}