#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*int is_prime(int num){
    for(int i = 2;i<=num-1;i++){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}*/
int
main(int argc, char *argv[])
{
    int rw[2];
    pipe(rw);
    int status;
    int pid = fork();
    if(pid > 0){
        close(rw[0]);
        for(int i = 2;i<=35;i++){
            write(rw[1],&i,4);
        }
        close(rw[1]);
        wait(&status);
        exit(0);
    }
    while(pid == 0){
        int number[35] = {0};
        close(rw[1]);
        int flag = 1;
        int j = 0;
        while(flag){
            flag = read(rw[0],number+j,4);
            j++;
        }
        int p = number[0];
        if(p == 0){
            exit(0);
        }
        printf("prime %d\n",p);
        pipe(rw);
        pid = fork();
        if(pid > 0){
            close(rw[0]);
            for(int i = 1;i<35;i++){
                if(number[i] != 0 && number[i] % p != 0){
                    write(rw[1],&number[i],4);
                }
            }
            close(rw[1]);
            wait(&status);
            exit(0);
        }
    }
    exit(0);
}