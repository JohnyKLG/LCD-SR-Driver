void lcd_nibble(unsigned int8 n)
{
   output_bit(LCD_DT4, bit_test(n, 0));
   output_bit(LCD_DT5, bit_test(n, 1));
   output_bit(LCD_DT6, bit_test(n, 2));
   output_bit(LCD_DT7, bit_test(n, 3));
   delay_cycles(1);
   output_bit(LCD_EN, 1);
   delay_us(2);
   output_bit(LCD_EN, 0);
}
void lcd_byte(unsigned int8 address, unsigned int8 n)
{
   output_bit(LCD_RS, 0);
   output_bit(LCD_RS, address);
   delay_cycles(1);
   output_bit(LCD_EN, 0);
   lcd_nibble(n >> 4);
   lcd_nibble(n & 0xf);
}
void lcd_init(void) 
{
   unsigned int8 i;
   unsigned int8 LCD_INIT_STRING[4] = {0x20 | (2 << 2), 0xc, 1, 6};
   output_bit(LCD_EN, 0);
   output_bit(LCD_RS, 0);
   delay_ms(15);
   for(i=1;i<=3;++i)
   {
      lcd_nibble(3);
      delay_ms(5);
   }
   lcd_nibble(2);
   delay_ms(5);
   for(i=0;i<=3;++i)
      lcd_byte(0,LCD_INIT_STRING[i]);
}
void lcd_gotoxy(unsigned int8 x, unsigned int8 y)
{
   unsigned int8 address;
   if(y!=1)
      address=0x40;
   else
      address=0;
   address+=x-1;
   lcd_byte(0,0x80|address);
}
void lcd_clr(void)
{
   lcd_byte(0,1);
   delay_ms(5);
}
void lcd_putc(char c)
{  
   lcd_byte(1,c);
}
