#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define GET_COUNT       _IOR('a', 'a', uint64_t*)
#define RESET_COUNT     _IO('a', 'b')
#define GET_COUT_TIME   _IOR('a', 'c', uint32_t*)

int main(int argc, char *argv[])
{
    int ret = 0;
    const char * file_name = "/dev/key_interrupt_counter_device";
    int fd = open(file_name, O_RDWR);
    if (fd < 0) {
        printf("Cannot open device file\n");
        return 1;
    }

    if (argc == 2) {
        if (strcmp(argv[1], "-gc") == 0) {
            uint64_t count;
            ioctl(fd, GET_COUNT, &count);
            printf("Count interrupts from keyboard: %lu\n", count);
        } else if (strcmp(argv[1], "-gt") == 0) {
            uint32_t time_sec;
            char buf[80];
            ioctl(fd, GET_COUT_TIME, &time_sec);
            time_t time = time_sec;
            struct tm ts = *localtime(&time);
            strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
            printf("Time last reset counter: \n%s\n", buf);
        } else if (strcmp(argv[1], "-rc") == 0) {
            ioctl(fd, RESET_COUNT);
            printf("Reset counter\n");
        } else {
            fprintf(stderr, "Usage: %s [-gc | -gt | -rc]\n\
                        \r* -gc -> get counter\n\
                        \r* -gt -> get time last reset counter\n\
                        \r* -rc -> reset counter\n", argv[0]);
            ret = 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [-gc | -gt | -rc]\n\
                        \r* -gc -> get counter\n\
                        \r* -gt -> get time last reset counter\n\
                        \r* -rc -> reset counter\n", argv[0]);
        ret = 1;
    }

    close(fd);
    return ret;
}