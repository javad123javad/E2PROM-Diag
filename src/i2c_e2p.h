#ifndef I2C_E2P_H
#define I2C_E2P_H

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
#include <netinet/in.h> // htons
#include <assert.h>
#include <string.h>
#include <unity/unity.h> 



#define MAX_PAGE_SIZE 32
#define DEVICE_ADDR 0x50 // 0b1010xxxx 


int8_t e2p_write(int g_i2c_dev, uint16_t wr_addr,
                 const uint8_t size, const uint8_t *data);

int8_t e2p_read(int g_i2c_dev, uint16_t rd_addr,
                const uint8_t size, uint8_t *data);
#endif // I2C_E2P_H
