#include <16F887.h>
#device adc=8 //resolucion del adc
#FUSES XT,nowdt,noprotect,noput,nobrownout
#use delay(clock=4000000)
#include <Flex_LCD416.c>

float temp;
float lum;
int x;
void main()
{
 //para que un canal sea analogico el pin debe ser configurado primero como entrada
 set_tris_a(0x0F); 
 set_tris_b(0x00); 
 set_tris_d(0x00);
 
 setup_adc(ADC_CLOCK_INTERNAL); //configuracion de velocidad de conversion
 setup_adc_ports(sAN0|sAN1|sAN2|sAN3|sAN4); //seleccionar canales analogicos
 //el 887 tiene la caracteristica que puedo seleccionar pin a pin 
 //y determina cual sera analogico 
 
 lcd_init();
 lcd_putc("\fTEMP:\n");
 lcd_putc("LUZ:");
while(true)
{
  set_adc_channel(0); //determinamos que sensaremos el canal 0 del convertidor (AN0)
  delay_us(50); //tiempo breve para esperar que el micro seleccione el canal
  temp=(read_adc() * 0.01953); //obtenemos la medicion 
  lcd_gotoxy(6,1);
  printf(lcd_putc,"%1.2f", temp); //especificamos que la variable a mostrar es float
  
  /*al inicio del codigo especificamos que el microcontrolador trabajara con 
  8 bit de resolucion; para este modelo el puede trabajar con 8 0 10
  los bits de resolucion determinan la resolucion de conversion; es decir el cambio 
  minimo de voltaje para que se afecte la conversion con 8 bit tenemos una resolucion de 
  
  resolucion = vref / 2^n donde n son los bit de resolucion 
  con 5v de referencia nos da res=5/2^8 = 0.01953
  
  si la conversion arroja 200 es porque a la entrada habia un voltaje de 3.9V
  
  Conversion = VIN/RESOLUCIOM*/
  
  set_adc_channel(1); //determinamos que sensaremos el canal 0 del convertidor (AN0)
  delay_us(50); //tiempo breve para esperar que el micro seleccione el canal
  lum=(read_adc() * 0.01953); //obtenemos la medicion 
  lcd_gotoxy(5,2);
  printf(lcd_putc,"%1.2f", lum);
  
  
  for (x=0;x<5;x++)
  {
   delay_ms(500);
  }
  
  
  
}

}
