/* Sistema de medicion de 3 niveles en un tanque.
Puerto C = entradas (PC0 = N1, PC1= N2 y PC2=N3)
Puerto A = Salidas (display de ánodo común: PA0 = a, PA1=b,...,PA6=g)*/

#define ENTRADAS GPIOC_IDR
#define SALIDAS GPIOA_ODR
#define BOMBAS GPIOB_ODR
#define APAGADO  0xff
#define CERO    0x3F
#define UNO     0x06
#define DOS      0x5B
#define TRES     0x4F
#define ERROR    0x79
#define lamp     0x01
#define LEDyled      0x02
#define na 0x00
sbit LED at GPIOB_ODRbits.B1;
sbit LAMPARA at GPIOB_ODRbits.B0;
const unsigned short int nivel[]={CERO,UNO,ERROR,DOS,ERROR,ERROR,ERROR,TRES};
const unsigned short int lev[]={LEDyled ,lamp,na,lamp,na,na,na,na};
int i;
sbit onda at GPIOC_ODRbits.B8;   //Onda para medir tiempo de respuesta

void Conf_ptos(void);
void Proceso(void);

void main()
{ Conf_ptos();
  while(1)
  {
    for(i=0; i<1000; i++)
    {
   Proceso();
    }
    onda=~onda;  // Complementa el bit
  }

}

void Conf_ptos(void)
{ GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_0 | _GPIO_PINMASK_1 | _GPIO_PINMASK_2);
  GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_LOW);
   GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_8);
  SALIDAS=APAGADO;
  GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_0|_GPIO_PINMASK_1);
  //onda=0;
}

void Proceso(void)
{ 
SALIDAS=nivel[ENTRADAS&0X07];
BOMBAS=lev[ENTRADAS&0X07];
}