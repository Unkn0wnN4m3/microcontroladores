#include "i2c.h"
#include <avr/io.h>

void init_i2c(void)
{
	TWSR = ((0 << TWPS1) & (0 << TWPS0)); //Prescaler = 1
	TWBR = 0X14; //Define Bit rate SCL_frec=CPU_frec/(16+2(TWBR)x4^(prescaler))
	//SCL_Frec=(16000000/(16+2(20)(4)))=74Khz
	TWCR = (1<<TWEN); //Enable TWI
}
void start_i2c(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START condition
	while((TWCR & (1<<TWINT))==0); //wait until TWINT=0 (TWI then finish)
}
void stop_i2c(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //STOP condition
	_delay_ms(1);
}



uint8_t I2C_Start(char write_address)/* I2C start function */
{   // putchUSART0('b');
	//_delay_ms(10);
	uint8_t status;		/* Declare variable */
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);;// /* Enable TWI, generate START */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status!=0x08)		/* Check weather START transmitted or not? */
	return 0;			/* Return 0 to indicate start condition fail */
	TWDR=write_address;		/* Write SLA+W in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI & clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x18)		/* Check for SLA+W transmitted &ack received */
	return 1;			/* Return 1 to indicate ack received */
	if(status==0x20){		/* Check for SLA+W transmitted &nack received */
		//putchUSART0('d');
		return 2;			/* Return 2 to indicate nack received */
	}
	else
	return 3;			/* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char read_address) /* I2C repeated start function */
{
	uint8_t status;		/* Declare variable */
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);/* Enable TWI, generate start */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status!=0x10)		/* Check for repeated start transmitted */
	return 0;			/* Return 0 for repeated start condition fail */
	TWDR=read_address;		/* Write SLA+R in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x40)		/* Check for SLA+R transmitted &ack received */
	return 1;			/* Return 1 to indicate ack received */
	if(status==0x20)		/* Check for SLA+R transmitted &nack received */
	return 2;			/* Return 2 to indicate nack received */
	else
	return 3;			/* Else return 3 to indicate SLA+W failed */
}
uint8_t I2C_Write(char data)	/* I2C write function */
{
	uint8_t status;		/* Declare variable */
	TWDR=data;			/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x28)		/* Check for data transmitted &ack received */
	return 0;			/* Return 0 to indicate ack received */
	if(status==0x30)		/* Check for data transmitted &nack received */
	return 1;			/* Return 1 to indicate nack received */
	else
	return 2;			/* Else return 2 for data transmission failure */
}
char I2C_Read_Ack()		/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;			/* Return received data */
}
char I2C_Read_Nack()		/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;		/* Return received data */
}