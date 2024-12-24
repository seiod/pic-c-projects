#include <16F887.h>
#device adc=8
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)

#byte PORTD= 0x08 
int matriz[10];
int letra=0;
int cont_barrido;
int x; 

void cargar(int valor)
{
  if (letra==0)
  {
   matriz[0]=0b01101000;
   matriz[1]=0b00001010;
   matriz[2]=0b01101000;
   matriz[3]=0b11111111;
   matriz[4]=0b01111000;
   matriz[5]=0b01111000;
   matriz[6]=0b00011010;
   matriz[7]=0b01101000;
   matriz[8]=0b01101000;
  }
}

void main()
{
set_tris_b(0x00);
set_tris_d(0x00);
set_timer0(0);
setup_adc(adc_off);
letra=0;

while (true)
{
  output_b(0x00);
  cargar(letra);
  for (x=0;x<8;x++)
  {
  output_d(matriz[x]); //apago display 
  output_b(2<<x);
  delay_ms(5); //espero
  output_b(0x00);
  }
  cont_barrido+=1;
  if (cont_barrido==100)
  {
    letra+=1;
  }
}
}
