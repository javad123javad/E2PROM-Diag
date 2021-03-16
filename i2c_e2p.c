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

static int g_i2c_dev;
int g_i2c_number = 1;
char g_i2c_dev_path[20];

#define MAX_PAGE_SIZE 32
#define DEVICE_ADDR 0x50 // 0b1010xxxx

int8_t e2p_write(int g_i2c_dev, uint16_t wr_addr,
                 const uint8_t size, const uint8_t *data)
{
    int8_t fret = 0;
    uint8_t tmp_buf[MAX_PAGE_SIZE + 2] = {0};

    tmp_buf[0] = wr_addr >> 8;
    tmp_buf[1] = wr_addr & 0xff;

    for (uint8_t counter = 2; counter < size + 2; counter++)
    {
        tmp_buf[counter] = data[counter - 2];
    }

    if (write(g_i2c_dev, tmp_buf, (size + 2)) != (size + 2))
    {
        printf("Write number mismatch.\n");
        fret = -1;
    }

    usleep(2000);

    return fret;
}

int8_t e2p_read(int g_i2c_dev, uint16_t rd_addr,
                const uint8_t size, uint8_t *data)
{
    int8_t fret = 0;
    assert(data);

    data[0] = rd_addr >> 8;
    data[1] = rd_addr & 0xff;

    if (write(g_i2c_dev, data, 0x02) != 2)
    {
        printf("Write Problem in read\n");
        return -1;
    }

    fret = read(g_i2c_dev, data, size);

    return fret;
}

int main(void)
{
    int e2p_addr = 0x50;
    uint8_t byte_read;
    char byte_array[] = "Hello World, Its me, The EEPROM";
    char read_buf[62] = {0};
    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);
    g_i2c_dev = open(g_i2c_dev_path, O_RDWR);

    if (g_i2c_dev < 0)
    {
        fprintf(stderr, "Unable to open I2C port: /dev/i2c-%d\n", g_i2c_number);
        exit(1);
    }
    printf("I2C port opened\n");

    if (ioctl(g_i2c_dev, I2C_SLAVE, e2p_addr) < 0)
    {
        perror("I2C Error:");
        exit(1);
    }

    printf("I2C Setup in slave mode\n");
    
    /* Write Dummy message into the eeprom */
    e2p_write(g_i2c_dev, 0x0000, strlen(byte_array), byte_array);

    /* read the message from eeprom */
    int read_num = e2p_read(g_i2c_dev, 0x0000, strlen(byte_array), read_buf); //read(file,read_buf,32);
    printf("Num Read:%d, Read Val:%s\n", read_num, read_buf);

    close(g_i2c_dev);
    return 0;
}