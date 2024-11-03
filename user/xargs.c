#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


int main(int argc, char* argv[]){
    int fd = 0;
    char buf[512];
    int n = 0, len = 0;
    while(1){
        n = read(fd, buf + len, 1);
        len += n;
        if (buf[len - 1] == '\n'){
            buf[len - 1] = '\0';
            len--;
        } else if (n == 0){
            buf[len] = '\0';
        } else{
            continue;
        }

        if (strlen(buf) == 0) exit(0); 
        
        if (fork() != 0){
            wait(0);
            for (int i = 0; i < len; i++) buf[i] = '\0';
            len = n = 0;
            continue;
        } else{
            char* newargv[argc + 1];
            for (int i = 0; i < argc - 1; i++) newargv[i] = argv[i + 1];
            newargv[argc - 1] = buf;
            newargv[argc] = 0;

            exec(argv[1], newargv);
        }
    }
}