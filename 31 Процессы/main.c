#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define T 60

int main()
{
    printf("p1 pid: %d ppid: %d\n", getpid(), getppid());

    pid_t p11;
    pid_t p22;


    if((p11 = fork()) == 0) {
        printf("p1-1 pid: %d ppid: %d\n", getpid(), getppid());

        pid_t p111;
        
        if((p111 = fork()) == 0) {
             printf("p1-1-1 pid: %d ppid: %d\n", getpid(), getppid());
        }
    }

    if((p11 != 0) && (p22 = fork()) == 0) {
        printf("p1-2 pid: %d ppid: %d\n", getpid(), getppid());

        pid_t p121;
        pid_t p122;

        if((p121 = fork()) == 0) {
            printf("p1-2-1 pid: %d ppid: %d\n", getpid(), getppid());
        }
        if((p121 != 0) && (p122 = fork()) == 0) {
            printf("p1-2-2 pid: %d ppid: %d\n", getpid(), getppid());
        }
    }

    sleep(T);

    return 0;
}