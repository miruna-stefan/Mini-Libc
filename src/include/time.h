#ifndef TIME_H
#define TIME_H	1

#ifdef __cplusplus
extern "C" {
#endif


struct timespec {
    int tv_sec;            /* seconds */
    long   tv_nsec;        /* nanoseconds */
};

int nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif
