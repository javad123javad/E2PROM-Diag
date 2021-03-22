#ifndef I2C_LL_H
#define I2C_LL_H

#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

int16_t i2c_close(int __fd);
int16_t i2c_open (const char *__path, int __oflag);
ssize_t i2c_read (int __fd, void *__buf, size_t __nbytes);
ssize_t i2c_write (int __fd, const void *__buf, size_t __n);

int i2c_ioctl(const int fd, const unsigned long request, const int i2c_addr);

#endif // I2C_LL_H
