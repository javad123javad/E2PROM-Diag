#include "build/test/mocks/mock_i2c_ll.h"
#include "build/test/mocks/mock_i2c_e2p.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"






static int g_i2c_dev;

static int g_i2c_number = 1;

static char g_i2c_dev_path[20];

static uint8_t g_e2p_addr = 0x50;



void setUp(void)

{

}



void tearDown(void)

{

}



void test_i2c_e2p_open(void)

{

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);

    g_i2c_dev = open(g_i2c_dev_path, 

                                    02

                                          );

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((0)), (UNITY_INT) ((g_i2c_dev)), UNITY_GREATER_OR_EQUAL, (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);



    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((0)), (UNITY_INT) ((ioctl(g_i2c_dev, 

   0x0703

   , g_e2p_addr))), UNITY_GREATER_OR_EQUAL, (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

}



void test_i2c_e2p_close(void)

{

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((close(g_i2c_dev))), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);

}



void test_i2c_e2p_read(void)

{

    char read_buf[62] = {0};



    mock_i2c_e2p_Init();

    e2p_read_CMockExpectAndReturn(49, g_i2c_dev, 0x0000, 30, read_buf, 30);

    int read_num = e2p_read(g_i2c_dev, 0x0000, 31, read_buf);

    UnityAssertEqualNumber((UNITY_INT)((30)), (UNITY_INT)((read_num)), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);





}

void test_i2c_e2p_write(void)

{

}

void test_i2c_e2p_read_write(void)

{





    uint8_t byte_read;

    char byte_array[] = "Hello World, Its me, The EEPROM";

    char read_buf[62] = {0};

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);

    g_i2c_dev = open(g_i2c_dev_path, 

                                    02

                                          );



    if (g_i2c_dev < 0)

    {

        fprintf(

               stderr

                     , "Unable to open I2C port: /dev/i2c-%d\n", g_i2c_number);

        exit(1);

    }

    printf("I2C port opened\n");



    if (ioctl(g_i2c_dev, 

                        0x0703

                                 , g_e2p_addr) < 0)

    {

        perror("I2C Error:");

        exit(1);

    }



    printf("I2C Setup in slave mode\n");





    e2p_write(g_i2c_dev, 0x0000, strlen(byte_array), byte_array);





    int read_num = e2p_read(g_i2c_dev, 0x0000, strlen(byte_array), read_buf);

    printf("Num Read:%d, Read Val:%s\n", read_num, read_buf);



    close(g_i2c_dev);

    return 0;

}
