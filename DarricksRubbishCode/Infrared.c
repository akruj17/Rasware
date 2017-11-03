#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here

    tADC *dist = InitializeADC(PIN_xx);
    // Replace PIN_xx with an actual pin
    // ADC is only supported on a limited number of pins in hardware
// The following pins are supported:
// PIN_B4
// PIN_B5
// PIN_D0
// PIN_D1
// PIN_D2
// PIN_D3
// PIN_E0
// PIN_E1
// PIN_E2
// PIN_E3
// PIN_E4
// PIN_E5
float distval;
    while (1) {
      distval = ADCRead(dist);
    Printf("IR sensor value is %f\n", distval); //%f is the escape character for floats

    }
}
