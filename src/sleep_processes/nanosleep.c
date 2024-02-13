#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    int ret = syscall(__NR_nanosleep, req, rem);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
