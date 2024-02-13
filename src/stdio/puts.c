#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <stdio.h>
#include <internal/io.h>

int puts(const char *str)
{
    // calculate the length of the string and store it in i
    int i;
    for (i = 0; ; i++) {
        if (str[i] == '\0')
            break;
    }

    // write the string to stdout
    int ret = write(1, str, i);

    // error handling
    if (ret < 0) {
		errno = -ret;
		return -1;
	}

    // write the newline character
    ret = write(1, "\n", 1);

    // error handling
    if (ret < 0) {
		errno = -ret;
		return -1;
	}

    return ret;
}
