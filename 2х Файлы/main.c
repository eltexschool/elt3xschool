#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
    int fd = 0;
    const char const* fname = "file.txt";

    if((fd = open(fname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        puts(strerror(errno));
        exit(-1);
    }

    char buf[] = "0123456789";

    if(write(fd, buf, sizeof(buf)-1) == -1) {
        puts(strerror(errno));
        exit(-1);
    }

    sync();
    close(fd);

    if((fd = open(fname, O_RDONLY)) == -1) {
        puts(strerror(errno));
        exit(-1);
    }

    int offset = -1;

    while(1) {
        int rr = lseek(fd, offset, SEEK_END);
        if(rr == -1) {
            puts(strerror(errno));
            exit(-1);
        }

        char c;

        if(read(fd, &c, 1) == -1) {
            puts(strerror(errno));
            exit(-1);
        }
        printf("%c", c);
        if(rr == 0) {
            printf("\n");
            break;
        }
        offset--;
    }

    return 0;
}
