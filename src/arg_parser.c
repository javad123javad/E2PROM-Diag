#include "arg_parser.h"
#include <argp.h>
#include <string.h>
#include <assert.h>
args_params_t g_params = {0};
/*********************************************************/



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
        // arguments->verbose = 1;

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