         // LCD module connections
sbit LCD_RS at GPIOA_ODR.B2;
sbit LCD_EN at GPIOA_ODR.B3;
sbit LCD_D4 at GPIOA_ODR.B4;
sbit LCD_D5 at GPIOA_ODR.B5;
sbit LCD_D6 at GPIOA_ODR.B6;
sbit LCD_D7 at GPIOA_ODR.B7;
// End LCD module connections
void config_ptos(void);
void config_adc(void);
void proceso(void);
void Move_Delay();
unsigned int adc_value;
char txt1[] = " ";
char bim[] = " ";

float B;
float A;
void main()
{
 config_ptos();
config_adc();
Lcd_Init();
while(1)
{
proceso();
}
 }
 void Move_Delay() {                  // Function used for text moving
  Delay_ms(200);                     // You can change the moving speed here
}
 void config_ptos(void)
 {
 GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_ALL);
GPIO_Analog_Input(&GPIOC_BASE,_GPIO_PINMASK_0);
 }
 void config_adc(void)
{
ADC_Set_input_Channel(_ADC_CHANNEL_10);
ADC1_Init();
}
 void proceso()
{
adc_value=ADC1_Get_Sample(10);
A=adc_value;
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out(1,1,"ADC=");
       Lcd_Out(2,1,"VOLT=");
IntTostr(adc_value, txt1); 
 Lcd_Out(1,5,txt1);
  B=((A*2.96)/4095);

FloatTostr(B, bim);

  Lcd_Out(2,6,bim);
  Move_Delay();
}