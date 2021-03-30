#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stdint.h>
#include <argp.h>

typedef enum DEV_MODE
{
    MODE_MASTER=1,
    MODE_SLAVE
}dev_mode_t;
typedef struct _P_ARGS_
{
    char *args[2];                /* arg1 & arg2 */
    uint8_t  read, write;
    dev_mode_t dev_mode;
    char *data;
} arguments_t;

typedef struct _ARS_PARAMS
{
    char *argp_program_version;
    char *argp_program_bug_address;
    char *doc;
    char *args_doc;
    arguments_t *args;
    struct argp_option *options;
}args_params_t;

error_t parse_opt (int key, char *arg, struct argp_state *state);
error_t get_args(const uint8_t argc, char **argv, args_params_t *arg_params);
#endif // ARG_PARSER_H
