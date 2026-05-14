#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int src, dst, n;
    char buffer[1024];

    struct stat s1, s2;

    src = open("source.txt", O_RDONLY);
    if(src<0){
        perror("error opening src file");
        return 1;
    }

    dst = open("backup.txt", O_WRONLY | O_CREAT | O_RDONLY | 0644);
    if(dst<0){
        perror("error creating dst file");
        close(src);
        return 1;
    }

    while((n = read(src, buffer, sizeof(buffer))>0)){
        if(write(dst, buffer, n)!=n){
            perror("write error");
            close(src);
            close(dst);
            return 1;
        }
    }

    if(n<0){
        perror("Read error");
    }

    close(src);
    close(dst);

    if(stat("source.txt", &s1) < 0 || stat("backup.txt", &s2) < 0){
        perror("stat error");
        return 1;
    }

    if (s1.st_size == s2.st_size)
        printf("File copied successfully\n");
    else
        printf("Copy failed\n");

    return 0;
}
