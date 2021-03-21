#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "i2c_ll.h"

inline int16_t i2c_open (const char *__path, int __oflag)
{
    return open(__path, __oflag);
}

inline int16_t i2c_close(int __fd)
{
    return close(__fd);
}

inline ssize_t i2c_read(int __fd, void* __buf, size_t __nbytes)
{  
  return read(__fd, __buf, __nbytes);
}

inline ssize_t i2c_write(int __fd, const void* __buf, size_t __n)
{
  return write(__fd, __buf, __n);
}
