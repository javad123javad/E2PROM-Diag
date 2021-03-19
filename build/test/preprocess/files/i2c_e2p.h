





















int8_t e2p_write(int g_i2c_dev, uint16_t wr_addr,

                 const uint8_t size, const uint8_t *data);



int8_t e2p_read(int g_i2c_dev, uint16_t rd_addr,

                const uint8_t size, uint8_t *data);
