#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char* argv[]){
    if (argc != 2){
        fprintf(2, "You must provide exactly 1 argument after sleep\n");
        exit(1);
    }

    int clockTicks = atoi(argv[1]);

    sleep(clockTicks);

    exit(0);
}