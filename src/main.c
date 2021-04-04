#include "arg_parser.h"
#include "i2c_e2p.h"
#include <stdint.h>

#include <string.h>




int main(int argc, char **argv)
{
    args_params_t args_params = {0};

    init_parser(&args_params);

    get_args(argc, argv, &args_params);
    
    printf("Device Address:0x%02x\n"
            "Register Address:0x%02x\n"
            "Write:%d\n"
            "Read:%d\n"
            "Mode:%d\n" 
            "Data:%s\n"
            "Nbytes:%d",
            (int16_t)strtol(args_params.args->args[0], NULL, 16),
            (int16_t)strtol(args_params.args->args[1], NULL, 16),
            args_params.args->write,
            args_params.args->read,
            args_params.args->dev_mode,
            args_params.args->data,
            args_params.args->nbytes);


    return 0;
}
