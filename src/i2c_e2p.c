#include "i2c_e2p.h"
#include "i2c_ll.h"



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

    if (i2c_write(g_i2c_dev, tmp_buf, (size + 2)) != (size + 2))
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

    if (i2c_write(g_i2c_dev, data, 0x02) != 2)
    {
        printf("Write Problem in read\n");
        return -1;
    }

    fret = i2c_read(g_i2c_dev, data, size);

    return fret;
}

