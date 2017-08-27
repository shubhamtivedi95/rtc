/* 
 * File:   demo.c
 * Author: shubh
 *
 * Created on March 25, 2016, 1:09 PM
 */
#include<reg52.h>
#include<lcd.h>
//#include<delay.h>
#include <ds1307.h>
//#include <i2c.h>


#define SEC   0x00
#define MIN   0x01
#define HOUR  0x02
#define DOW  0x03
#define DATE  0x04
#define MONTH 0x05
#define YEAR  0x06

#define mon   0x01
#define tue  0x02
#define wed  0x03
#define thu  0x04
#define fri 0x05
#define sat  0x06
#define sun   0x07
unsigned char date,month,year,hour,min,sec,hour1,dow;
void main (void)
{
    lcd_init(4);
    lcd_msg_display("ELECTRO-PASSION");
/* THe below two lines are used to load current time in rtc ds1307. 
	Please comment out this two lines while just reading from rtc. 
	otherwise you will get wrong value after after each reset.*/
	  DS1307_settime(0x12,0x59,0x00,pm,12);
    DS1307_setdate(0x15,0x04,0x16,fri);
    curser_pos(2,1);
    lcd_msg_display("Real Time Clock");
    delay_ms(1000);
    lcd_clear();
       	lcd_msg_display("Time:");
	curser_pos(2,1);
	lcd_msg_display("Date:");
	 while(1)
	{
		/* Get Date & Time */
		sec   = DS1307_get(SEC);
		min   = DS1307_get(MIN);
		hour  = DS1307_get(HOUR);
                dow  = DS1307_get(DOW);
		date  = DS1307_get(DATE);
		month = DS1307_get(MONTH);
		year  = DS1307_get(YEAR);
		// Show Time in format hr:min:sec

                curser_pos(1,6); 			// Set LCD cursor at (1,6)
                hour1=hour & 0x1F;
                lcd_BCD_display(hour1); 		// Show min on LCD
		lcddata(':');
		lcd_BCD_display(min); 		// Show hour on LCD
		lcddata(':');
		lcd_BCD_display(sec); 		// Show sec on LCD
                if(ampm_check(hour)==1)
                    lcd_msg_display("PM");
                else
                    if(ampm_check(hour)==0)
                        lcd_msg_display("AM");
		// Show Date in format dd/mm/yr
		curser_pos(2,6); 			// Set LCD cursor at (2,6)
		lcd_BCD_display(date); 		// Show date on LCD
		lcddata('/');
		lcd_BCD_display(month); 		// Show year on LCD
		lcddata('/');
		lcd_BCD_display(year); 	// Show month on LCD
                switch(dow){
                    case(mon):
                    {lcd_msg_display("MON");break;}
                    case(tue):
                    {lcd_msg_display("TUE");break;}
                    case(wed):
                    {lcd_msg_display("WED");break;}
                    case(thu):
                    {lcd_msg_display("THU");break;}
                    case(fri):
                    {lcd_msg_display("FRI");break;}
                    case(sat):
                    {lcd_msg_display("SAT");break;}
                    case(sun):
                    {lcd_msg_display("SUN");break;}
                    default:
                    {lcd_BCD_display(dow);break;}
                }
                delay_ms(1000);

    }
}
