#define TEST
#ifdef TEST

#include "unity.h"
#include <unity/unity.h>
#include "mock_i2c_e2p.h"
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
    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);
    g_i2c_dev = open(g_i2c_dev_path, O_RDWR);
    TEST_ASSERT_GREATER_OR_EQUAL(0, g_i2c_dev);

    TEST_ASSERT_GREATER_OR_EQUAL(0, ioctl(g_i2c_dev, I2C_SLAVE, g_e2p_addr));
}

void test_i2c_e2p_close(void)
{
    TEST_ASSERT_EQUAL(0, close(g_i2c_dev));
}

void test_i2c_e2p_read(void)
{
    // sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);
    // g_i2c_dev = open(g_i2c_dev_path, O_RDWR);
    // if (g_i2c_dev < 0)
    // {
    //     fprintf(stderr, "Unable to open I2C port: /dev/i2c-%d\n", g_i2c_number);
    //     exit(1);
    // }

    // printf("Reading 30 byte of data from Device");
    char read_buf[62] = {0};

    mock_i2c_e2p_Init();
    e2p_read_CMockExpectAndReturn(__LINE__, g_i2c_dev, 0x0000, 30, read_buf, 30);
    int read_num = e2p_read(g_i2c_dev, 0x0000, 31, read_buf); //read(file,read_buf,32);
    TEST_ASSERT_EQUAL(30, read_num);


}
void test_i2c_e2p_write(void)
{
}
void test_i2c_e2p_read_write(void)
{
    // TEST_IGNORE_MESSAGE("Need to Implement i2c_e2p");

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

    if (ioctl(g_i2c_dev, I2C_SLAVE, g_e2p_addr) < 0)
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

#endif // TEST
