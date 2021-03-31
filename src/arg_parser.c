#include "arg_parser.h"
#include <argp.h>
#include <string.h>
#include <assert.h>
args_params_t g_params = {0};
/*********************************************************/

error_t init_parser(args_params_t *arg_param)
{
    char *argp_program_version =
        "e2pdiag 1.0";
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
        {"master", 'm',  0,      0,      "Device operates in master mode"},
        {"slave", 's',   0,      0,      "Device operate in slave mode"},
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

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    arguments_t *arguments = state->input;
    error_t fret = 0;
    switch (key)
    {
    case 'r':
        (arguments->write)?argp_error(state, "Just one command [read or write] should be specified."):(arguments->read = 1);
#ifdef TEST
        if(arguments->write)
        {
            fprintf(stderr,"Duplicate command write before\n");
        }
#endif
        break;
    case 'w':
        (arguments->read)?argp_error(state, "Just one command [read or write] should be specified."):(arguments->write = 1);

#ifdef TEST
        if(arguments->read)
        {
            fprintf(stderr,"Duplicate command read before\n");
        }
#endif
        break;
    case 'm':
        (MODE_SLAVE == arguments->dev_mode)?argp_error(state, "Only one mode (master or slave) should be specified."):(arguments->dev_mode = MODE_MASTER);
        break;
    case 's':
        (MODE_MASTER == arguments->dev_mode)?argp_error(state, "Only one mode (master or slave) should be specified."):(arguments->dev_mode = MODE_SLAVE);
        break;
    case 'd':
        arguments->data = arg;
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

error_t get_args(const uint8_t argc, char **argv, args_params_t *arg_params)
{
    assert(arg_params->args);
    assert(arg_params->argp_program_bug_address);
    assert(arg_params->argp_program_version);
    assert(arg_params->args_doc);
    assert(arg_params->doc);
    assert(arg_params->options);

    struct argp argp = { arg_params->options, parse_opt, arg_params->args_doc, arg_params->doc };

    /* Default values. */
    arg_params->args->read = 0;
    arg_params->args->write = 0;
    arg_params->args->data = "-";

    argp_parse (&argp, argc, argv, 0, 0, arg_params->args);

}