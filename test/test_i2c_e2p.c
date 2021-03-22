#define TEST
#ifdef TEST

#include "unity.h"
#include <unity/unity.h>
// #include "mock_i2c_e2p.h"
#include "mock_i2c_ll.h"
static int g_i2c_dev;
static int g_i2c_number = 1;
static char g_i2c_dev_path[20];
static uint8_t g_e2p_addr = 0x50; /* A0=0,A1=0,A2=0 */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_i2c_e2p_open(void)
{
    mock_i2c_ll_Init();

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);

    i2c_open_ExpectAndReturn(g_i2c_dev_path, O_RDWR, 0);
    g_i2c_dev = i2c_open(g_i2c_dev_path, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, g_i2c_dev);

    i2c_ioctl_ExpectAndReturn(g_i2c_dev, I2C_SLAVE, g_e2p_addr, 0);
    TEST_ASSERT_EQUAL(0, i2c_ioctl(g_i2c_dev, I2C_SLAVE, g_e2p_addr));
}

void test_i2c_e2p_close(void)
{
    i2c_close_ExpectAndReturn(g_i2c_dev, 0);
    TEST_ASSERT_EQUAL(0, i2c_close(g_i2c_dev));
}

void test_i2c_e2p_read(void)
{
    /* First Open The I2C Bus */

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);

    i2c_open_ExpectAndReturn(g_i2c_dev_path, O_RDWR, 0);
    g_i2c_dev = i2c_open(g_i2c_dev_path, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, g_i2c_dev);

    i2c_ioctl_ExpectAndReturn(g_i2c_dev, I2C_SLAVE, g_e2p_addr, 0);
    TEST_ASSERT_EQUAL(0, i2c_ioctl(g_i2c_dev, I2C_SLAVE, g_e2p_addr));

    /* Now read from device */
    int8_t fret = 0;
    ssize_t size = 32;
    uint8_t addr_size = 2u;
    uint16_t rd_addr = 0x0000;
    uint8_t data[32] = {0};
    data[0] = rd_addr >> 8;
    data[1] = rd_addr & 0xff;

    /* First send the target address */
    i2c_write_ExpectAndReturn(g_i2c_dev, data, addr_size, addr_size);

    TEST_ASSERT_EQUAL(addr_size, i2c_write(g_i2c_dev, data, addr_size));
    /* Now read `size` byte from device */
    memset(data, 0, sizeof(data));
    i2c_read_ExpectAndReturn(g_i2c_dev, data, size, size);
    fret = i2c_read(g_i2c_dev, data, size);
    TEST_ASSERT_EQUAL(fret, size);

    /* Close the i2c device */
    i2c_close_ExpectAndReturn(g_i2c_dev, 0);
    TEST_ASSERT_EQUAL(0, i2c_close(g_i2c_dev));

}
void test_i2c_e2p_write(void)
{
    /* First Open The I2C Bus */

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);

    i2c_open_ExpectAndReturn(g_i2c_dev_path, O_RDWR, 0);
    g_i2c_dev = i2c_open(g_i2c_dev_path, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, g_i2c_dev);

    i2c_ioctl_ExpectAndReturn(g_i2c_dev, I2C_SLAVE, g_e2p_addr, 0);
    TEST_ASSERT_EQUAL(0, i2c_ioctl(g_i2c_dev, I2C_SLAVE, g_e2p_addr));

    /* Now write into the device */
    int8_t fret = 0;
    #define DATA_SIZE  32 /* Dummy write size */
    uint8_t data[DATA_SIZE] = {0};
    uint8_t tmp_buf[DATA_SIZE + 2] = {0};
    const uint8_t wr_addr = 0x0000;
    /* First determine write address */
    tmp_buf[0] = wr_addr >> 8;
    tmp_buf[1] = wr_addr & 0xff;

    for (uint8_t counter = 2; counter < DATA_SIZE + 2; counter++)
    {
        tmp_buf[counter] = data[counter - 2];
    }

        i2c_write_ExpectAndReturn(g_i2c_dev, tmp_buf, (DATA_SIZE + 2), (DATA_SIZE + 2));

    if (i2c_write(g_i2c_dev, tmp_buf, (DATA_SIZE + 2)) != (DATA_SIZE + 2))
    {
        printf("Write number mismatch.\n");
        fret = -1;
    }

    usleep(2000);

    return fret;

}
void test_i2c_e2p_read_write(void)
{
    // TEST_IGNORE_MESSAGE("Need to Implement i2c_e2p");

}

#endif // TEST
