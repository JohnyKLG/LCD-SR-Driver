unsigned int rs, PIN_V0, PIN_V1, PIN_V2;

void lcd_clock(unsigned int8 b)
{
   output_low(LCD_CK);
   output_bit(LCD_DT, b);
   output_high(LCD_CK);
}
void lcd_nibble(unsigned int8 n)
{
   lcd_clock(PIN_V2);
   lcd_clock(PIN_V1);
   lcd_clock(PIN_V0);
   lcd_clock(rs);
   lcd_clock(bit_test(n, 0));
   lcd_clock(bit_test(n, 1));
   lcd_clock(bit_test(n, 2));
   lcd_clock(bit_test(n, 3));
   output_bit(LCD_EN, 1);
   output_bit(LCD_EN, 0);
}
void lcd_byte(unsigned int8 address, unsigned int8 n)
{
   rs = address;
   output_bit(LCD_EN, 0);
   lcd_nibble(n >> 4);
   lcd_nibble(n & 0xf);
}
void lcd_clr(void)
{
   lcd_byte(0,1);
   delay_ms(2);
}
void lcd_init(void) 
{
   unsigned int8 i;
   unsigned int8 LCD_INIT_STRING[4] = {0x20 | (2 << 2), 0xc, 1, 6};
   output_bit(LCD_EN, 0);
   rs = 0;
   delay_ms(15);
   for(i=1;i<=3;++i)
   {
      lcd_nibble(3);
      delay_ms(5);
   }
   lcd_nibble(2);
   delay_ms(5);
   for(i=0;i<=3;++i){
      lcd_byte(0,LCD_INIT_STRING[i]);
   }
   delay_ms(250);
   lcd_clr();
}
void lcd_xy(unsigned int8 x, unsigned int8 y)
{
   unsigned int8 address;
   if(y!=1)
      address=0x40;
   else
      address=0;
   address+=x-1;
   lcd_byte(0,0x80|address);
}
void lcd_show(char c)
{
   lcd_byte(1,c);
}
