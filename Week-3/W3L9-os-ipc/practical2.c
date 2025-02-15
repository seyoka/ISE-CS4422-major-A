#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


#define FILEPATH "shared_memory_file"
#define FILESIZE 4096

int main(){
    int fd;
    char *map;

    fd = open(FILEPATH, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("Error opening file");
        exit(EXIT_FAILURE);

    }

    if(ftruncate(fd, FILESIZE) == -1){
        perror("Error resizing file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
    if(map == MAP_FAILED){
        perror("Error mapping file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *messages = "Hello from mmap()";
    strncpy(map, messages, strlen(messages) + 1);

    printf("Process 1: data written to mmap file: %s\n", messages);

    sleep(5);

    munmap(map, FILESIZE);
    close(fd);
}
