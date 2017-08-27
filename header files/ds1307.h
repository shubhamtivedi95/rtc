#ifndef __DS1307_H
#define __DS1307_H

#include <i2c.h> /* Need i2c bus */
#define DS1307_ID 0xD0 
#define SEC   0x00
#define MIN   0x01 
#define HOUR  0x02
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06
char ampm_check(unsigned char value);
void DS1307_settime(unsigned char hh, unsigned char min, unsigned char ss, bit status,unsigned char mode);
void DS1307_setdate(unsigned char dd, unsigned char mm, unsigned char yy,unsigned char day);
unsigned char DS1307_get(unsigned char addr);
bit am=0,pm=1;

char ampm_check(unsigned char value)
{
    value =value & 0x60;
    if(value== 0x00 || value== 0x20 )
        return 2;
    else if(value== 0x40)
        return 0;
    else if(value== 0x60)
        return 1;
}
void DS1307_settime(unsigned char hh, unsigned char min, unsigned char ss,bit status,unsigned char mode)
{
    if(mode==12)
        {
         if(status==pm)
            hh=hh|0x60;
         else
            hh=hh|0x40;
        }
    else if(mode==24)
            hh=hh & 0xBF;
         I2C_start();
         while(I2C_write(DS1307_ID)==1)	// connect to DS1307
            I2C_start();
         I2C_write(0x00); 		// Request RAM address at 00H
	 I2C_write(ss); 		// Write sec on RAM address 00H
	 I2C_write(min); 		// Write min on RAM address 01H
	 I2C_write(hh); 		// Write hour on RAM address 02H
	 I2C_stop();            // Stop i2c bus
}

void DS1307_setdate(unsigned char dd, unsigned char mm, unsigned char yy,unsigned char day)
{
	 I2C_start();
	while(I2C_write(DS1307_ID)==1) 	// connect to DS1307
	 I2C_start();
         I2C_write(0x03); 		// Request RAM address at 04H
	 I2C_write(day);
         I2C_write(dd); 		// Write date on RAM address 04H
	 I2C_write(mm); 		// Write month on RAM address 05H
	 I2C_write(yy); 		// Write year on RAM address 06H
         I2C_stop(); 			// Stop i2c bus
}

unsigned char DS1307_get(unsigned char addr)
{
	unsigned char ret;
	I2C_start();           	// Start i2c bus
	while(I2C_write(DS1307_ID)==1)	// Connect to DS1307
        I2C_start();
        I2C_write(addr); 		// Request RAM address on DS1307
	I2C_start(); 			// Start i2c bus
	I2C_write(DS1307_ID+1); // Connect to DS1307 for Read

        ret = I2C_read(); 		// Receive value

	I2C_stop(); 			// Stop i2c bus
	return ret;
}
#endif