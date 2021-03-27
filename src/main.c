#include <i2c_e2p.h>
#include <argp.h>
#include <stdint.h>

const char *argp_program_version =
    "i2c_diag 1.0";
const char *argp_program_bug_address =
    "<javad321javad@gmail.com>";

static char doc[] =
    "Example: e2pdiag -a 0x50 -r 0x0001";

static char args_doc[] = "ADDRESS REGISTER";
/* The options we understand. */
static struct argp_option options[] = {
    {"read",        'r',    0,      0,      "Read command"},
    {"write",       'w',    0,      0,      "Write command"},
    {   "data",        'd',    "data",  OPTION_ARG_OPTIONAL,      "Output to FILE instead of standard output"
    },
    { 0 }
};

struct arguments
{
    char *args[2];                /* arg1 & arg2 */
    uint8_t  read, write;
    char *output_file;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    struct arguments *arguments = state->input;

    switch (key)
    {
    case 'r':
        (arguments->write)?argp_error(state, "Just one command [read or write] should be specified."):(arguments->read = 1);
       
        break;
    case 'w':
            (arguments->read)?argp_error(state, "Just one command [read or write] should be specified."):(arguments->write = 1);
        break;
    case 'v':
        // arguments->verbose = 1;
        break;
    case 'o':
        arguments->output_file = arg;
        break;

    case ARGP_KEY_ARG:
        if (state->arg_num >= 2)
            /* Too many arguments. */
            argp_usage (state);

        arguments->args[state->arg_num] = arg;

        break;

    case ARGP_KEY_END:
        if (state->arg_num < 2)
            /* Not enough arguments. */
            argp_usage (state);
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char argv[])
{
    int e2p_addr = 0x50;
    int g_i2c_dev;
    int g_i2c_number = 1;
    char g_i2c_dev_path[20];

    uint8_t byte_read;
    char byte_array[] = "Hello World, Its me, The EEPROM";
    char read_buf[62] = {0};

    struct arguments arguments;

    /* Default values. */
    arguments.read = 0;
    arguments.write = 0;
    arguments.output_file = "-";

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    printf ("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\nRead:%u\nWrite:%u",
            arguments.args[0], arguments.args[1],
            arguments.output_file
            , arguments.read, arguments.write);

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
