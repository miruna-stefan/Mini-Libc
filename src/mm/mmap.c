// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	long long ret = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return MAP_FAILED;
	}

	return (void *)ret;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	long long ret = syscall(__NR_mremap, old_address, old_size, new_size, flags);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return MAP_FAILED;
	}

	return (void *)ret;
}

int munmap(void *addr, size_t length)
{
	int ret = syscall(__NR_munmap, addr, length);

	// error handling
	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
}