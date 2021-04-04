#ifndef APP_EEPROM_H
#define APP_EEPROM_H

#include "i2c_e2p.h"
#include "arg_parser.h"
#include <stdint.h>
#include <stdio.h>

uint32_t app_read(char *read_buf, const args_params_t* dev_args);

#endif // APP_EEPROM_H
