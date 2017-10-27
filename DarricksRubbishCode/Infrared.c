#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>

// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here

    tADC *dist = InitializeADC(PIN_xx);
    // Replace PIN_xx with an actual pin
float distval;
    while (1) {
      distval = ADCRead(dist);
    Printf("IR sensor value is %f\n", distval); //%f is the escape character for floats

    }
}
