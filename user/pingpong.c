#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int rw[2];
    pipe(rw);
    int status;
    char message[1];
    int pid = fork();
    if(pid == 0){
        printf("%d: received ping\n",getpid());
        write(rw[1],"a",1);
        close(rw[0]);
        close(rw[1]);
        exit(0);
    } //child process
    else if(pid > 0){
        write(rw[1],"a",1);
        wait(&status);
        read(rw[0],message,1);
        printf("%d: received pong\n",getpid());
        close(rw[0]);
        close(rw[1]);
        exit(0);
    }
    exit(0);
}
