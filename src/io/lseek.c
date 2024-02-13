// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	int ret = syscall(__NR_lseek, fd, offset, whence);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
