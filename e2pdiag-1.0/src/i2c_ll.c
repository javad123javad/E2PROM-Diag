#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "i2c_ll.h"

inline i2c_dev_t ll_i2c_open (const char *__path, int __oflag)
{
    return open(__path, __oflag);
}

inline int8_t ll_i2c_close(int __fd)
{
    return close(__fd);
}

inline ssize_t ll_i2c_read(int __fd, void* __buf, size_t __nbytes)
{  
  return read(__fd, __buf, __nbytes);
}

inline ssize_t ll_i2c_write(int __fd, const void* __buf, size_t __n)
{
  return write(__fd, __buf, __n);
}

inline int ll_i2c_ioctl(const int fd, const unsigned long request, const int i2c_addr)
{
  return ioctl(fd, request, i2c_addr);
}