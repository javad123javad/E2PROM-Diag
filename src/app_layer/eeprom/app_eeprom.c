#include "app_layer/eeprom/app_eeprom.h"

static int g_i2c_dev;

#define DEBUG 0
#define _DEBUG(fmt, args...) if(DEBUG) printf("%s:%s:%d: "fmt, __FILE__, __FUNCTION__, __LINE__, args)

int main(int argc, char**argv)
{
    int e2p_addr = 0x50;
    int fret = 0;
    uint8_t byte_read;
    char byte_array[] = "Hello, This is Javad Rahimi From Iran Islamic Republic ";
    char read_buf[62] = {0};
    args_params_t args_params = {0};

    init_parser(&args_params);

    get_args(argc, argv, &args_params);

    args_params.dev_addr = (int16_t)strtol(args_params.args->args[1], NULL, 16);

    _DEBUG(
        "Interface:%s\n"
        "Device Address:0x%02x\n"
        "Register Address:0x%02x\n"
        "Write:%d\n"
        "Read:%d\n"
        "Mode:%d\n"
        "Data:%s\n"
        "Bytes:%d\n",
        args_params.args->args[0],
        e2p_addr,//
        (int16_t)strtol(args_params.args->args[2], NULL, 16),
        args_params.args->write,
        args_params.args->read,
        args_params.args->dev_mode,
        args_params.args->data,
        args_params.args->nbytes);

    /* Open I2C port with input parameters */
    fret = app_open(&args_params);
    if(fret < 0)
    {
        printf("Openning %s\t[FAILED] \n", args_params.args->args[0]);
    }
    else
    {
        printf("\t[Opened]\n");

        if(args_params.args->write)
        {
            fret = app_write(args_params.args->data, args_params.args->nbytes, &args_params);

            if(fret < 0)
            {
                printf("Write Operation Failed: %d.\n",fret);
            }
            else
            {
                printf("%d bytes written.\n", args_params.args->nbytes);
            }

        }

        if (args_params.args->read)
        {
            /* read the message from eeprom */

            int read_num = app_read(read_buf, &args_params);
            if(fret < 0)
            {
                fprintf(stderr, "Read Operation Failed.\n");
            }
            else
            {
                printf("Read %d bytes: %s\n", read_num, read_buf);
            }
        }

        app_close(&args_params);
    }
    return fret;
}

int8_t app_open(args_params_t* args_params)
{
    int fret = 0;
    
    printf("Openning I2C port...");
    args_params->dev_file = ll_i2c_open(args_params->args->args[0], O_RDWR);

    if (args_params->dev_file < 0)
    {
        fret = args_params->dev_file;
    }
    else
    {
        fret = ll_i2c_ioctl(args_params->dev_file, I2C_SLAVE, args_params->dev_addr);
    }
    return fret;

}

int8_t app_close(args_params_t* dev_args)
{
    return ll_i2c_close(dev_args->dev_file);
}

uint32_t app_read(char *read_buf, const args_params_t* dev_args)
{

    /* read the message from eeprom */
    uint16_t reg_addr = (int16_t)strtol(dev_args->args->args[2], NULL, 16);
    int read_num = e2p_read(dev_args->dev_file, reg_addr, dev_args->args->nbytes, read_buf);
    return read_num;
}

uint32_t app_write(const char *write_buf, const ssize_t buf_len, const args_params_t* dev_args)
{
    int fret = 0;
    /* read the message from eeprom */
    uint16_t reg_addr = (int16_t)strtol(dev_args->args->args[2], NULL, 16);
    /* Write Dummy message into the eeprom */
    fret = e2p_write(dev_args->dev_file, reg_addr, buf_len, write_buf);
    return fret;
}