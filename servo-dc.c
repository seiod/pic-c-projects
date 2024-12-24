#include <16F887.h>
#device adc=8
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)

int angulo=1;
int nivel=1;
int sentido=0;
int potencia;
int x;

#int_rtcc
void servo()
{
 if (nivel==1)
  {
   output_high(pin_d0);
   nivel=0;
   
   if (angulo==1)
   {
    set_timer0(251);
   }
   else if (angulo==2)
   {
    set_timer0(246);
   }
   else 
   {
    set_timer0(239);
   }
  }
  else 
  {
    output_low(pin_d0);
    nivel=1;
    set_timer0(100);
  }
}

#int_rb
void botones()
{
 if (input(pin_b4)==1)
 {
  if (sentido==1)
  {
   sentido=0;
  }
  else
  {
   sentido=1;
  }
 }
 
  if (input(pin_b5)==1)
 {
  potencia+=1;
  if (potencia==11)
  {
   potencia=0;
  }
 }
 
 if (input(pin_b6)==1)
 {
  angulo+=1;
  if (angulo==4)
  {
   angulo=1;
  }
 }
 
}

void main()
{
set_tris_a(0x0f);
set_tris_b(0x00);
set_tris_c(0x00);
set_tris_d(0x00);
set_tris_e(0x00);

setup_adc(adc_off);
setup_adc_ports(no_analogs);

setup_timer_0(T0_INTERNAL|T0_DIV_128);

enable_interrupts(int_rtcc);
enable_interrupts(int_rb);
enable_interrupts(global);

potencia=5;

while (true)
{

if (sentido==1)
{
 output_high(pin_d4);
}
else
{
output_high(pin_d5);
}

 for (x=0;x<potencia;x++)
 {
  delay_ms(10);
 }
 
output_low(pin_d4);
output_low(pin_d5);

 for (x=0;x<(10-potencia);x++)
 {
  delay_ms(10);
 }

}
}
