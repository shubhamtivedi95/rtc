#ifndef __LCD_H
#define __LCD_H
//#include<delay_ms.h>
#include<reg52.h>
//Declarations
#define dataport P3 	//data port for lcd
#define cmdport     P1//cmd port for lcd
sbit rs =cmdport^6;//register select signal to P1.6
sbit rw =cmdport^5;//read/write signal to P1.5
sbit e =cmdport^4 ;//enable signal to P1.4
unsigned char check_4bit=0;

void delay_ms(unsigned int msec)  // Function to provide time delay_ms in
{
int r,p;
	
	for(p=0;p<msec;p++)
for(r=0;r<110;r++);
}

//function to send data two time fo 4 bit mode
void send_data(unsigned char t)
{
      char temp,y;
           temp = t&0x0F;
            y = t&0xF0;
            dataport=dataport || y;             //Data transfer
            e = 1;
            delay_ms(2);
            e = 0;
            dataport=dataport ||(temp<<4);
            e = 1;
            delay_ms(2);
            e = 0;
}

//Function to send data to LCD
void lcddata(unsigned char chr)  //Function to send data to LCD
{
    rs=1;
   // rw=0;
    if(check_4bit)
    {
        send_data(chr);
    }
    else
    {
        dataport = chr;
        e=1;
        delay_ms(1);
        e=0;

    }
delay_ms(5);
}
//Function to display integer variable on LCD
void lcd_Decimal_display(unsigned int value)
{
unsigned char u,v,w;
	u=value/100;
	lcddata(u+0x30);
	value=value%100;
	v=value/10;
	lcddata(v+0x30);
	value=value%10;
	w=value;
	lcddata(w+0x30);
        }

void lcd_BCD_display(unsigned int value)
{
	   unsigned char b,c;
        b=value&0xF0;
        b=b>>4;
        lcddata(b+0x30);
        c=value&0x0F;
        lcddata(c+0x30);
}

//Function to send command to LCD
void lcdcmd(unsigned char chr)
{
    rs=0;
 //   rw=0;
    if(check_4bit)
    {
        send_data(chr);
    }
    else
    {
        dataport = chr;
        e=1;
        delay_ms(2);
        e=0;
    }
delay_ms(5);
}

//Function to intitalise LCD
void lcd_init(unsigned char bits)
{
		rw=0;
    dataport=0x00;
    delay_ms(50);
    lcdcmd(0x30);
    delay_ms(5);
    lcdcmd(0x30);
    delay_ms(1);
    lcdcmd(0x30);
    delay_ms(1);
    if(bits==4)
        {
            lcdcmd(0x20);
            delay_ms(1);
            check_4bit=1;
            lcdcmd(0x28);  // for using 4-bit 2 row mode of LCD
        }
    else if(bits==8)
        {
            lcdcmd(0x30);
            delay_ms(1);
            check_4bit=0;
            lcdcmd(0x38);  // for using 8-bit 2 row mode of LCD
        }

    lcdcmd(0x01);  //clear screen
    lcdcmd(0x06);  //display ON
    lcdcmd(0x80);  // bring cursor to position 0 of line 1
    lcdcmd(0x0C);  // turn display ON for cursor blinking
}

//function to display string on lcd
void lcd_msg_display(unsigned char text[])
{
	int s;
	for(s=0;text[s]!='\0';s++)
        {
            lcddata(text[s]);
        }
}

//function to clear to lcd
void lcd_clear()
{
    lcdcmd(0x01);
}
//function to set curser position on lcd
void curser_pos(unsigned char row,unsigned char col)
{
    unsigned char pos;
	col=col-1;
    if(row==1)
       pos=0x80;
    else if(row==2)
         pos=0xC0;
    pos=pos+col;
    lcdcmd(pos);
}
//Function to shift entired display onleft
void lcd_shift_left(unsigned char time,unsigned int duration)
{
    unsigned char z;
    for(z=0;z<time;z++)
    {
        lcdcmd(0x18);
        delay_ms(duration);
    }
}
//Function to shift entired display onleft
void lcd_shift_right(unsigned char time,unsigned int duration)
{
    unsigned char z;
    for(z=0;z<time;z++)
    {
        lcdcmd(0x1C);
        delay_ms(duration);
    }

}


#endif

