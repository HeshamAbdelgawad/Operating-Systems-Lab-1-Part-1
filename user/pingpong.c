#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int main(int argc, char* argv[]){
    if (argc > 1){
        fprintf(2, "Invalid command\n");
        exit(1);
    }

    int p1[2], p2[2];

    char byte = 'c';

    pipe(p1);
    pipe(p2);

    if (fork() == 0){
        close(p1[1]);
        read(p1[0], &byte, 1);
        printf("%d: received ping\n", getpid());
        close(p2[0]);
        write(p2[1], &byte, 1);
        close(p2[1]);

    } else{
        close(p1[0]);
        write(p1[1], &byte, 1);
        close(p1[1]);
        close(p2[1]);
        read(p2[0], &byte, 1);
        printf("%d: received pong\n", getpid());
    }
}