#include <16F887.h>
#device adc=8
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)

int soltado;
int pulsado;
int x;

void chequeo_botones()
{

if (input(pin_a0)==1)
 {
  pulsado=1;
 }
 else if (input(pin_a0)==0 && pulsado==1)
 {
  pulsado=0;
  output_toggle(pin_d0);
 }
 
  if (input(pin_a1)==0)
 {
  soltado=1;
 }
 else if (input(pin_a1)==1 && soltado==1)
 {
  soltado=0;
  output_toggle(pin_d1);
 }
 
 if (input(pin_a2)==1)
 {
  delay_ms(1);
  while(input(pin_a2)==1){}
  output_toggle(pin_d2);
 }
 
 if (input(pin_a3)==1)
 {
  delay_ms(50);
  if(input(pin_a3)==0)
  {
  output_toggle(pin_d3);
  } 
 }

}

void main ()
{
set_tris_a(0x0f);
set_tris_b(0x00);
set_tris_c(0x00);
set_tris_d(0x00);
set_tris_e(0x00);

setup_adc(adc_off);
setup_adc_ports(no_analogs);

soltado=1;
pulsado=0;

output_d(0x00);

while (true)
{
 
 output_toggle(pin_d4);
 for (x=0;x<5;x++)
 {
 delay_ms(100);
 chequeo_botones();
 }

}
}
