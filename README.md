KLG SR Driver é um driver de display LCD para Shif-Registers diversos. No projeto foi utilizado o 74HC595, porém pode ser utilizado qualquer SR. Está programado em C na plataforma CCS e compilado por CW.

As funções do driver são:
lcd_init();  // Inicia o display setando as configurações para comunicar com o SR.
lcd_xy(x,y); // Direciona o ponteiro do display para iniciar a escrita.
lcd_show();  // Escreve uma sequencia "char" no display.
lcd_clr();   // Limpa o conteúdo da tela e da memória do display.
 
Exemplo:
#define LCD_EN          PIN_E0 \\ Define o pino Enable do SR e LCD
#define LCD_CK          PIN_E1 \\ Define o pino Clock do SR
#define LCD_DT          PIN_E2 \\ Define o pino Data do SR

#include <KLG_LCD.c>

lcd_init();delay_ms(100);
lcd_xy(3, 1);lcd_show("GitHub.com/JohnyKLG");
delay_ms(10000);lcd_clr();
