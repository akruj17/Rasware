#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <stdio.h>

tBoolean value = false;

void InitSwitch(void){
  InitializeGPIO();
}

void PrintSwitch(tPin Pin){
  value = GetPin(Pin);
  printf("The Switch value is %d\n", value);
}
