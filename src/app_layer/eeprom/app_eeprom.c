#include "app_eeprom.h"
#include "i2c_e2p.h"
#include "arg_parser.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char**argv)
{
    printf("Hello From ee2prom app\n");
    int e2p_addr = 0x50;
    int g_i2c_dev;
    int g_i2c_number = 1;
    char g_i2c_dev_path[20];

    uint8_t byte_read;
    char byte_array[] = "Hello World, Its me, The EEPROM";
    char read_buf[62] = {0};
    args_params_t args_params = {0};

    init_parser(&args_params);

    get_args(argc, argv, &args_params);

    printf("Device Address:0x%02x\n"
           "Register Address:0x%02x\n"
           "Write:%d\n"
           "Read:%d\n"
           "Mode:%d\n"
           "Data:%s\n",
           (int16_t)strtol(args_params.args->args[0], NULL, 16),
           (int16_t)strtol(args_params.args->args[1], NULL, 16),
           args_params.args->write,
           args_params.args->read,
           args_params.args->dev_mode,
           args_params.args->data);

    sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);
    g_i2c_dev = i2c_open(g_i2c_dev_path, O_RDWR);

    if (g_i2c_dev < 0)
    {
        fprintf(stderr, "Unable to open I2C port: /dev/i2c-%d\n", g_i2c_number);
        exit(1);
    }
    printf("I2C port opened\n");

    if (i2c_ioctl(g_i2c_dev, I2C_SLAVE, e2p_addr) < 0)
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

    i2c_close(g_i2c_dev);
    return 0;
}