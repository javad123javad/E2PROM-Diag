#include "build/test/mocks/mock_i2c_ll.h"
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

    mock_i2c_ll_Init();



    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);



    i2c_open_CMockExpectAndReturn(27, g_i2c_dev_path, 

   02

   , 0);

    g_i2c_dev = i2c_open(g_i2c_dev_path, 

                                        02

                                              );

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((0)), (UNITY_INT) ((g_i2c_dev)), UNITY_GREATER_OR_EQUAL, (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);



    i2c_ioctl_CMockExpectAndReturn(31, g_i2c_dev, 

   0x0703

   , g_e2p_addr, 0);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((i2c_ioctl(g_i2c_dev, 

   0x0703

   , g_e2p_addr))), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);

}



void test_i2c_e2p_close(void)

{

    i2c_close_CMockExpectAndReturn(37, g_i2c_dev, 0);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((i2c_close(g_i2c_dev))), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

}



void test_i2c_e2p_read(void)

{





    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);



    i2c_open_CMockExpectAndReturn(47, g_i2c_dev_path, 

   02

   , 0);

    g_i2c_dev = i2c_open(g_i2c_dev_path, 

                                        02

                                              );

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((0)), (UNITY_INT) ((g_i2c_dev)), UNITY_GREATER_OR_EQUAL, (

   ((void *)0)

   ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);



    i2c_ioctl_CMockExpectAndReturn(51, g_i2c_dev, 

   0x0703

   , g_e2p_addr, 0);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((i2c_ioctl(g_i2c_dev, 

   0x0703

   , g_e2p_addr))), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);





    int8_t fret = 0;

    ssize_t size = 32;

    uint8_t addr_size = 2u;

    uint16_t rd_addr = 0x0000;

    uint8_t data[32] = {0};

    data[0] = rd_addr >> 8;

    data[1] = rd_addr & 0xff;





    i2c_write_CMockExpectAndReturn(64, g_i2c_dev, data, addr_size, addr_size);



    UnityAssertEqualNumber((UNITY_INT)((addr_size)), (UNITY_INT)((i2c_write(g_i2c_dev, data, addr_size))), (

   ((void *)0)

   ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_INT);



    memset(data, 0, sizeof(data));

    i2c_read_CMockExpectAndReturn(69, g_i2c_dev, data, size, size);

    fret = i2c_read(g_i2c_dev, data, size);

    UnityAssertEqualNumber((UNITY_INT)((fret)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);





    i2c_close_CMockExpectAndReturn(74, g_i2c_dev, 0);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((i2c_close(g_i2c_dev))), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);



}

void test_i2c_e2p_write(void)

{





    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);



    i2c_open_CMockExpectAndReturn(84, g_i2c_dev_path, 

   02

   , 0);

    g_i2c_dev = i2c_open(g_i2c_dev_path, 

                                        02

                                              );

    UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((0)), (UNITY_INT) ((g_i2c_dev)), UNITY_GREATER_OR_EQUAL, (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);



    i2c_ioctl_CMockExpectAndReturn(88, g_i2c_dev, 

   0x0703

   , g_e2p_addr, 0);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((i2c_ioctl(g_i2c_dev, 

   0x0703

   , g_e2p_addr))), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);





    int8_t fret = 0;



    uint8_t data[32] = {0};

    uint8_t tmp_buf[32 + 2] = {0};

    const uint8_t wr_addr = 0x0000;



    tmp_buf[0] = wr_addr >> 8;

    tmp_buf[1] = wr_addr & 0xff;



    for (uint8_t counter = 2; counter < 32 + 2; counter++)

    {

        tmp_buf[counter] = data[counter - 2];

    }



        i2c_write_CMockExpectAndReturn(106, g_i2c_dev, tmp_buf, (32 + 2), (32 + 2));



    if (i2c_write(g_i2c_dev, tmp_buf, (32 + 2)) != (32 + 2))

    {

        printf("Write number mismatch.\n");

        fret = -1;

    }



    usleep(2000);



    return fret;



}

void test_i2c_e2p_read_write(void)

{





}
