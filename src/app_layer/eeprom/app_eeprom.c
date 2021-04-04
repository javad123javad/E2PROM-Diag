#include "app_layer/eeprom/app_eeprom.h"

static int g_i2c_dev;

int main(int argc, char**argv)
{
    int e2p_addr = 0x50;
    int g_i2c_number = 1;
    char g_i2c_dev_path[20];

    uint8_t byte_read;
    char byte_array[] = "Hello World, Its me, The EEPROM";
    char read_buf[62] = {0};
    args_params_t args_params = {0};

    init_parser(&args_params);

    get_args(argc, argv, &args_params);

    printf(
        "Interface:%s\n"
        "Device Address:%d\n"
        "Register Address:%d\n"
        "Write:%d\n"
        "Read:%d\n"
        "Mode:%d\n"
        "Data:%s\n"
        "Bytes:%d\n",
        args_params.args->args[0],
        (int16_t)strtol(args_params.args->args[1], NULL, 16),//
        (int16_t)strtol(args_params.args->args[2], NULL, 16),
        args_params.args->write,
        args_params.args->read,
        args_params.args->dev_mode,
        args_params.args->data,
        args_params.args->nbytes);

    // sprintf(g_i2c_dev_path, "/dev/i2c-%d", g_i2c_number);
    g_i2c_dev = ll_i2c_open(args_params.args->args[0], O_RDWR);

    if (g_i2c_dev < 0)
    {
        fprintf(stderr, "Unable to open I2C port: /dev/i2c-%d\n", g_i2c_number);
        exit(1);
    }
    printf("I2C port opened\n");

    if (ll_i2c_ioctl(g_i2c_dev, I2C_SLAVE, e2p_addr) < 0)
    {
        perror("I2C Error:");
        exit(1);
    }

    printf("I2C Setup in slave mode\n");

    /* Write Dummy message into the eeprom */
    e2p_write(g_i2c_dev, 0x0000, strlen(byte_array), byte_array);

    /* read the message from eeprom */
    // int read_num = e2p_read(g_i2c_dev, 0x0000, strlen(byte_array), read_buf); //read(file,read_buf,32);
    // printf("Num Read:%d, Read Val:%s\n", read_num, read_buf);
    app_read(read_buf, &args_params);

    ll_i2c_close(g_i2c_dev);
    return 0;
}

uint32_t app_read(char *read_buf, const args_params_t* dev_args)
{

    /* read the message from eeprom */
    uint16_t reg_addr = (int16_t)strtol(dev_args->args->args[2], NULL, 16);
    int read_num = e2p_read(g_i2c_dev, reg_addr, dev_args->args->nbytes, read_buf); //read(file,read_buf,32);
    printf("Num Read:%d, Read Val:%s\n", read_num, read_buf);

}