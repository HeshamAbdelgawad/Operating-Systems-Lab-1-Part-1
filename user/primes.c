#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void filter(int* p){
    int prime;
    close(p[1]);
    if (read(p[0], &prime, 4) == 0){
        close(p[0]);
        exit(0);
    }

    printf("prime %d\n", prime);

    int iter;
    int pp[2];

    pipe(pp);

    if (fork() == 0){
        filter(pp);
    } else{
        close(pp[0]);
        while(read(p[0], &iter, 4) != 0){
            if (iter % prime) write(pp[1], &iter, 4); 
        }
        close(pp[1]);
    }
    close(pp[0]);
    wait(0);
}

int main(int argc, char* argv[]){
    if (argc != 1){
        fprintf(2, "Wrong number of arguments\n");
        exit(1);
    }

    int p[2];

    pipe(p);

    if (fork() == 0){
        filter(p);
    } else{
        close(p[0]);
        for (int i = 2; i <= 36; i++){
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
    }
}