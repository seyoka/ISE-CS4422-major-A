#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld bytes\n", page_size);

    void *ptr = malloc(page_size * 2);
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Allocated memory at: %p\n", ptr);
    free(ptr);
    return 0;
}
