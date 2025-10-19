#include "Ultrasonic_interface.h"
#include "../../MCAL/SYSTICK/SYSTICK_interface.h"

static u16 distance;
static u16 time;

void Ultrasonic_vInit(void){
	/*Ultrasonic trigger Pin*/
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN7,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN7,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN7,GPIO_OUTSPEED_LOW);
	//////////////////////////////////////////////////////////////////////
	/*TIM1 Echo pin*/
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN8,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN8,GPIO_INPUTTYPE_NPU);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN8,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN8,1);
}
u16 Ultrasonic_Get_Distance(void){
	MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_HIGH);
	MSYSTICK_vSetBusyWait_us(15);
	MGPIO_vSetPinValue(GPIO_PORTA,GPIO_PIN7,GPIO_LOW);
	time = TIM1_InputCapture();
	distance = (time*0.01715);
	return distance;
}


