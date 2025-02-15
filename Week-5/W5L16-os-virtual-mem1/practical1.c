#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int fd = open("mapfile", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char *p = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    p[100] = 42;  // Modify memory
    printf("Mapped memory address: %p\n", p);

    sleep(1000);  // Keep the process running
    return 0;
}
