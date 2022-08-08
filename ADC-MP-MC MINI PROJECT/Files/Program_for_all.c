#include<reg51.h>
sfr mydata = 0x90;
sbit rd= P2^5; 
sbit wr= P2^6;
sbit intr= P2^7;
sbit RS = P2^0;
sbit EN = P2^1;
 //(0x90)is address of port1, else you can write as : #defintre mydata P1

void delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<255;j++);
}
void lcd_cmd(char a)
{
	P3 = a;
	RS = 0;
	EN = 1;
	delay(10);
	EN = 0;
}

void lcd_data(char a)
{
	P3 = a;
	RS = 1;
	EN = 1;
	delay(10);
	EN = 0;
}

void display(char *ptr)
{
	while(*ptr != '\0')
	{
		lcd_data(*ptr);
		ptr++;
	}
}
void main()
{
	unsigned char value;
	char temp[4];
	int i=0;
	lcd_cmd(0x01); //clear screen
	lcd_cmd(0x0E); //Display On, Cursor Blinking
	lcd_cmd(0x38); //2 lines and 5*7 matrix
	lcd_cmd(0x80); //Force Cursor to beginning of first
	display("ADC Value=");
	lcd_cmd(0xC0);
	//mydata = 0xEF;
	intr = 1;
	rd = 1;
	wr = 1;
	while(1)
	{
		lcd_cmd(0xC0);
		wr = 0;
		wr = 1;
		while(intr==1);
	  rd=0;
		value = mydata;
		
		while(i<3)
		{
			temp[i] = (value%10) + '0'; // For converting into ASCII
			value = value / 10;
			i++;
		}
		
		for(i=2;i>=0;i--)
		{
			lcd_cmd(0x06);
			lcd_data(temp[i]);
		}
		i=0;
		delay(1000);
		rd = 1;
	}
}