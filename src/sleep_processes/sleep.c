#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec request;
    struct timespec remaining;
    request.tv_sec = seconds;
    request.tv_nsec = 0;

    while (nanosleep(&request, &remaining) == -1) {
        /* check if there are no more (nano)seconds remaining,
        meaning that the sleep is completed */
        if (remaining.tv_sec == 0) {
            if (remaining.tv_nsec == 0)
                break;
        }

        // update the remaining sleep time
        request = remaining;
    }

    // return the remaining seconds to be slept
    return remaining.tv_sec;
}
