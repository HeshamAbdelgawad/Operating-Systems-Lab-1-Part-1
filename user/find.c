#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char* conc(const char* s, const char* t) {
    int len1 = strlen(s);
    int len2 = strlen(t);
    char* res = (char*)malloc(len1 + len2 + 1);
    for (int i = 0; i < len1; i++) {
        res[i] = s[i];
    }
    for (int i = 0; i < len2; i++) {
        res[i + len1] = t[i];
    }
    res[len1 + len2] = '\0';

    return res;
}

void find(char* path, char* name){
    int fd;
    if ((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "NO shuch directory\n");
        exit(1);
    }
    struct dirent entry;
    struct stat st;

    while(read(fd, &entry, sizeof(entry)) > 0){
        if (entry.inum == 0) continue;
        char* res = conc(path, conc("/", entry.name));
        stat(res, &st);

        if (st.type == T_DIR && strcmp(entry.name, ".") && strcmp(entry.name, "..")){
            find(res, name);
        } else if (!strcmp(entry.name, name)){
            printf("%s/%s\n", path, entry.name);
        }
    }
}


int main(int argc, char* argv[]){
    
    if (argc < 2 || argc > 3){
        fprintf(2, "Wrong number of arguments\n");
        exit(1);
    } else if (argc == 2){
        find(".", argv[1]);
    } else{
        find (argv[1], argv[2]);
    }

    
}