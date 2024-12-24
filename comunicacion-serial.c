#include <16F887.h>
#device adc=8 //resolucion del adc
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)
#use rs232 (baud=9600, bits=8, xmit=pin_c6, rcv=pin_c7, stop=1, parity=n)
#include <Flex_LCD416.c>

int1 trama_recibida;
int trama[10];
int cont=0;
int x;

#int_rda
void rx()
{
 int recibido;
 recibido=getc();
 switch (recibido)
 {
  case '/':
  cont=0;
  break;
  case '$':
  trama_recibida=1;
  break;
  default:
  trama[cont]=recibido;
  cont+=1;
 }
}


void procesar_trama()
{
if (trama_recibida==1)
{
 if (trama[0]=='a' && trama[1]=='e') //trama encendido alarma
 {
  output_high(pin_d0);
 }
 else if (trama[0]=='a' && trama[1]=='a') //trama apagado alarma
 {
  output_low(pin_d0);
 }
 trama_recibida=0;
}
}

void main()
{
set_tris_c(0x80); //el pin de xmit(tx) es salida y el pin rcv(rx) es entrada
set_tris_d(0x00);
output_low(pin_d0);
enable_interrupts(int_rda);
enable_interrupts(global);
 while (true)
 {
  output_toggle(pin_d4);
  for (x=0;x<5;x++)
  {
   delay_ms(100);
   procesar_trama();
  }
 }
}
