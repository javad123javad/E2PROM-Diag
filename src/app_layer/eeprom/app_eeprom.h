#ifndef APP_EEPROM_H
#define APP_EEPROM_H

#include "i2c_e2p.h"
#include "arg_parser.h"
#include <stdint.h>
#include <stdio.h>

int8_t app_open(args_params_t* dev_args);
uint32_t app_read(char *read_buf, const args_params_t* dev_args);
uint32_t app_write(const char *write_buf, const ssize_t buf_len, const args_params_t* dev_args);
int8_t app_close(args_params_t* dev_args);

#endif // APP_EEPROM_H
