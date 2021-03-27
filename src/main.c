#include "arg_parser.h"
#include "i2c_e2p.h"
#include <stdint.h>

#include <string.h>

error_t init_parser(args_params_t *arg_param)
{
    char *argp_program_version =
        "i2c_diag 1.0";
    char *argp_program_bug_address =
        "<javad321javad@gmail.com>";

    static char doc[] =
        "Example: e2pdiag -w --data=\"hello\" \"/dev/i2c-1\" 0x04 0x44";

    static char args_doc[] = "DEVICE ADDRESS REGISTER";
    /* The options we understand. */
    static struct argp_option options[] = {
        {"read", 'r',    0,      0,      "Read command"},
        {"write",'w',    0,      0,      "Write command"},
        {"data", 'd',    "data", 0,      "Output to FILE instead of standard output"},
        {"mode", 'm',    "master|slave", 0, "Device openning mode"},
        { 0 }
    };

    arguments_t args = {0};

    arg_param->argp_program_version = argp_program_version;
    arg_param->argp_program_bug_address = argp_program_bug_address;
    arg_param->doc = doc;
    arg_param->args_doc =  args_doc;
    arg_param->options = options;
    arg_param->args = &args;

}


int main(int argc, char **argv)
{
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
            "Register Address:0x%02x\n", 
            (int16_t) strtol(args_params.args->args[0], NULL, 16),
            (int16_t)strtol(args_params.args->args[1], NULL, 16));

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
