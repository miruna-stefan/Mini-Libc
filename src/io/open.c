// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* implementation inspired from the pclp1 Lab 13
	https://ocw.cs.pub.ro/courses/programare/laboratoare/lab13*/

	mode_t mode = 0;
	va_list args;
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);

	int ret = syscall(__NR_open, filename, flags, mode);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}
