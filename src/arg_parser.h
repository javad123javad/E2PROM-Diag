#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stdint.h>
#include <argp.h>

typedef struct _P_ARGS_
{
    char *args[2];                /* arg1 & arg2 */
    uint8_t  read, write;
    char *output_file;
} arguments_t;

typedef struct _ARS_PARAMS
{
    char *argp_program_version;
    char *argp_program_bug_address;
    const char *doc;
    const char *args_doc;
    arguments_t *args;
    const struct argp_option *options;
}args_params_t;

error_t parse_opt (int key, char *arg, struct argp_state *state);
error_t get_args(const uint8_t argc, const char **argv, args_params_t *arg_params);
#endif // ARG_PARSER_H
