/*
 * i2c.h
 *
 * Created: 13/03/2024 10:04:30
 *  Author: unk0wnn4m3
 */ 

// code made in school
#ifndef I2C_H_
#define I2C_H_

void init_i2c(void);
uint8_t read_i2c();
void write_i2c(uint8_t data);
void start(void);
void stop(void);

#define TRUE 1
#define FALSE 0

#endif /* I2C_H_ */