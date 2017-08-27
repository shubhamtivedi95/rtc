#ifndef __I2C_H
#define __I2C_H
bit ack;
//decleration
sbit sda=P1^0;
sbit scl=P1^1;


unsigned char t=0x0F;
void I2C_delay()
{
	unsigned char j;
	for(j=0;j<t;j++);
}
void I2C_start()		//start condition
{
	sda=1;
	scl=1;
I2C_delay();         //No operation
	sda=0;
I2C_delay();
	scl=0;
}
void I2C_stop()			//stop condition
{
	sda=0;
	scl=1;
I2C_delay();
	sda=1;
I2C_delay(); 
	scl=0;
}
bit I2C_write(unsigned char send)	//send byte serially
{ 
	unsigned int i;
	for(i=0;i<8;i++)
	{
		sda=send & 0x80;			//extracting MSB
		send=send<<1;			//shiftng left
		scl=1;
I2C_delay();
		scl=0;
	}
  sda=1;
	scl=1;
I2C_delay();
	ack=sda;					//reading acknowledge
I2C_delay();
	scl=0;
	return ack;
}
unsigned char I2C_read()			//reading from EEPROM serially
{
	unsigned char	i,read_data=0;
	sda=1;
	for(i=0;i<8;i++)
	{
		read_data=read_data<<1;
		scl=1;
		I2C_delay();
		read_data=read_data | sda;
		I2C_delay();
		scl=0;
	}
	sda=0;
	scl=1;
	I2C_delay();
	scl=0;
	return read_data;				//Returns 8 bit data here
}		
#endif