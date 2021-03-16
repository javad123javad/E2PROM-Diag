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
int file;
int adapter_nr = 1;
char filename[20];
#define MAX_PAGE_SIZE 32
#define DEVICE_ADDR 0x50 // 0b1010xxxx

__s32 e2p_write(int file, __u16 wr_addr,
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

    if (write(file, tmp_buf, (size + 2)) != (size + 2))
    {
        printf("Write number mismatch.\n");
        fret = -1;
    }

    usleep(2000);

    return fret;
}

__s32 e2p_read(int file, __u16 rd_addr,
                const uint8_t size, uint8_t *data)
{
    int8_t fret = 0;
    assert(data);

    data[0] = rd_addr >> 8;
    data[1] = rd_addr & 0xff;

    if(write(file, data, 0x02) != 2)
    {
        printf("Write Problem in read\n");
        return -1;
    }
    
    fret = read(file, data, size); 

    return fret;
}
int main(void)
{
    int e2p_addr = 0x50;
    uint8_t byte_read;
    char byte_array[] = "Salam Javad Rahimi";//{22, 23, 24, 25};
    char read_buf[62] = {0};
    sprintf(filename, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);

    if (file < 0)
    {
        fprintf(stderr, "Unable to open I2C port: /dev/i2c-%d\n", adapter_nr);
        exit(1);
    }
    printf("I2C port opened\n");

    if (ioctl(file, I2C_SLAVE, e2p_addr) < 0)
    {
        perror("I2C Error:");
        exit(1);
    }
    printf("I2C Setup in slave mode\n");
    e2p_write(file, 0x0000, strlen(byte_array), byte_array);


    int read_num = e2p_read(file,0x0000,strlen(byte_array),read_buf);//read(file,read_buf,32);
    printf("Num Read:%d, Read Val:%s\n", read_num, read_buf);
    // for (int counter = 0; counter < 30; counter++)
    // {
    //     printf("Byte Read:%c\n", read_buf[counter]);
    // }

    close(file);
    return 0;
}