#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
//#include "kernel"
#define MSGSIZE 16
int main(int argc, char *argv[MAXARG]){
    int old_argc = 0;
    char* xargv[MAXARG];
    for(int i = 1;i<argc;i++){
        xargv[old_argc] = argv[i];
        old_argc++;
    }
    //printf("%s ",xargv[0]);
    //char a = 1;
    char buf[512];
    char* p = buf;
    //printf("%d ",buf);
    int status;
    //argv++;
    int i = 0;
    while(read(0,buf+i,1) != 0){
        
        if(buf[i] == ' '){
            //printf("1");
            buf[i] = 0;
            //printf("%s ",p);
            xargv[old_argc] = p;
            old_argc++;
            //xargv[old_argc] = '\0';
            p = buf+1+i;
            i++;
        }
        else if(buf[i] == '\n'){
            //printf("2");
            buf[i] = '\0';
            //printf("%d ",old_argc);
            xargv[old_argc] = p;
            //printf("%s ",xargv[3]);
            old_argc++;
            xargv[old_argc] = '\0';
            p = buf+1+i;
            i++;
            int pid = fork();
            if(pid >0){
                old_argc = argc-1;
                wait(&status);
            }
            else if(pid == 0){
                //printf("%s ",xargv[2]);                
                exec(xargv[0],xargv);
                //exec("echo",xargv);
                exit(0);
            }
        }
        else{
            //printf("%c:%s ",*buf,xargv[0]);
            i++;
            
        }
    };
    exit(0);
}