#include <16F887.h>
#device adc=8
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)

int secuencia[5];
int cont_secuencia=1;
int x;
int y;
int pulsado;

void chequeo_botones()
{

if (input(pin_a0)==1)
{
 pulsado=1;
}
if (pulsado==1 && input(pin_a0)==0)
{
 cont_secuencia+=1;
 pulsado=0;
 if (cont_secuencia==4)
 {
  cont_secuencia=1;
 }
}

}

void generar_secuencia (int valor, int retardo)
{

do
{
 output_d(secuencia[x]);
 x+=1;
 if (x==5)
 {
  x=0;
 }
 for (y=0;y<retardo;y++)
 {
  delay_ms(100);
  chequeo_botones();
 }

} while (cont_secuencia==valor);
}


void main()
{
set_tris_a(0x00);
set_tris_b(0x00);
set_tris_c(0x00);
set_tris_d(0x00);
set_tris_e(0x00);

setup_adc(adc_off);
setup_adc_ports(no_analogs);

while (true)
{

switch (cont_secuencia)
{

case 1:
secuencia[0]=0b10000001;
secuencia[1]=0b00011000;
secuencia[2]=0b11000011;
secuencia[3]=0b00111100;
secuencia[4]=0b11110000;
generar_secuencia(1,5);
break;
case 2:
secuencia[0]=0b10000001;
secuencia[1]=0b11000011;
secuencia[2]=0b11100111;
secuencia[3]=0b11111111;
secuencia[4]=0b00000000;
generar_secuencia(2,5);
break;
case 3:
secuencia[0]=0b00011000;
secuencia[1]=0b00111100;
secuencia[2]=0b01111110;
secuencia[3]=0b11111111;
secuencia[4]=0b00000000;
generar_secuencia(3,5);
break;
}

}
}
