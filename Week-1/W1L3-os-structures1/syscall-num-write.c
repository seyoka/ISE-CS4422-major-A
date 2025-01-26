#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
    printf("The syscall number for write is: %d\n", SYS_write);
}
