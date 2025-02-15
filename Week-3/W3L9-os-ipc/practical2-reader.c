#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FILEPATH "shared_memory_file"
#define FILESIZE 4096

int main(){
    int fd;
    char *map;

    fd = open(FILEPATH, O_RDWR);

    if(fd == -1){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Process 2: read from shared memory: %s\n", map);

    munmap(map, FILESIZE);
    close(fd);
}
