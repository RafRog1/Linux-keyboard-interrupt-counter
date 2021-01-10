#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "IO_definitions.h"

#define GET_COUNT_COMMAND   "-gc"
#define GET_TIME_COMMAND    "-gt"
#define RESET_COUNT_COMMAND "-rc"

static void print_usage(const char * first_arg)
{
    fprintf(stderr, "Usage: %s [%s | %s | %s]\n\
                        \r* %s -> get counter\n\
                        \r* %s -> get time last reset counter\n\
                        \r* %s -> reset counter\n", 
                        first_arg, GET_COUNT_COMMAND, GET_TIME_COMMAND, RESET_COUNT_COMMAND, 
                                    GET_COUNT_COMMAND, GET_TIME_COMMAND, RESET_COUNT_COMMAND);
}

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
        if (strcmp(argv[1], GET_COUNT_COMMAND) == 0) {
            uint64_t count;
            ioctl(fd, GET_COUNT, &count);
            printf("Count interrupts from keyboard: %lu\n", count);
        } else if (strcmp(argv[1], GET_TIME_COMMAND) == 0) {
            uint32_t time_sec;
            char buf[80];
            ioctl(fd, GET_COUT_TIME, &time_sec);
            time_t time = time_sec;
            struct tm ts = *localtime(&time);
            strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
            printf("Time last reset counter: \n%s\n", buf);
        } else if (strcmp(argv[1], RESET_COUNT_COMMAND) == 0) {
            ioctl(fd, RESET_COUNT);
            printf("Reset counter\n");
        } else {
            print_usage(argv[0]);
            ret = 1;
        }
    } else {
        print_usage(argv[0]);
        ret = 1;
    }

    close(fd);
    return ret;
}
