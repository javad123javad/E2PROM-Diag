#include "build/test/mocks/mock_i2c_e2p.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}



void test_i2c_e2p_NeedToImplement(void)

{





    int g_i2c_dev;

    int g_i2c_number = 1;

    char g_i2c_dev_path[20];

    int e2p_addr = 0x50;

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

                                 , e2p_addr) < 0)

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
