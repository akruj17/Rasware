#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include "Switch.h"
#include <RASLib/inc/linesensor.h>
#include <RASLib/inc/adc.h>
#include <math.h>

// Blink the LED to show we're on
tBoolean blink_on = true;

tMotor *leftMotor;
tMotor *rightMotor;

float leftSpeed;
float rightSpeed;

void setLeftMoterSpeed(float speed){
  SetMotor(leftMotor, speed);
  leftSpeed = speed;
}
void setRightMoterSpeed(float speed){
  SetMotor(rightMotor, speed);
  rightSpeed = speed;
}


int main(void) {

    //Continuous Servo Motor; true and false make motors
    //turn into opposite directions.
    // leftMotor = InitializeServoMotor(PIN_F4, false); //forward with false
    // rightMotor = InitializeServoMotor(PIN_D7, true);  // forward

    //
    //LineSensor
     tLineSensor *line = InitializeGPIOLineSensor(PIN_B0, PIN_B1, PIN_E4, PIN_E5, PIN_B4, PIN_A5, PIN_A6, PIN_A7);
     float value[8];
    //
    // Infrared Distance Sensor
    // ADC is only supported on a limited number of pins in hardware
    // The following pins are supported:
    // PIN_B4 PIN_B5 PIN_D0  PIN_D1   PIN_D2  PIN_D3  PIN_E0
    // PIN_E1  PIN_E2  PIN_E3  PIN_E4  PIN_E5
    float errorL;
    float errorR;
    float percentErrorL;
    float percentErrorR;
    float desired = 0.40;
    float kpL;
    float kpR;
    tADC *IRLeft = InitializeADC(PIN_D1);
    tADC *IRRight = InitializeADC(PIN_D0);
    float readIRLeft;
    float readIRRight;
    int flag = 0;

    while (1) {
        // //Continuous Servo Motor V(left, 0) = V(right0.258)
        // // speed = changing k * speed(set)
        // setLeftMoterSpeed(0.8);  //< -0.3: backward
        // setRightMoterSpeed(0.8); // 0; 0.3
        //
        //
        // readIRLeft = ADCRead(IRLeft);
        // errorL = readIRLeft - desired;
        // percentErrorL = errorL / desired - 0.5;
        // kpL = 1 + fabs(0.4 * percentErrorL);

        // readIRRight = ADCRead(IRRight);
        // errorR = readIRRight - desired;
        // percentErrorR = errorR / desired - 0.5;
        // kpR = 1 + fabs(0.4 * percentErrorR);

        // // Which IR sensor to use?
        // if ((errorL - errorR < 0.1 || errorR - errorL < 0.1) && (errorL < 0.1 && errorR < 0.1)){
        //   setLeftMoterSpeed(0.8);  //< -0.3: backward
        //   setRightMoterSpeed(0.8);
        // }
        //
        // //if L - R > 0.05 : use L
        // if ((errorL - errorR < 0.1 || errorR - errorL < 0.1) && (errorL > 0.1 || errorR > 0.1)){
        //   //turn Left
        //   int flag = 0;
        //   while (flag < 6 ){
        //     setLeftMoterSpeed(- 0.2 * kpR);
        //     setRightMoterSpeed(0.5 * kpR);
        //     Wait(0.2);
        //     flag++;
        //   }
        // }
        //
        // //if R - L > 0.05 : use R
        //
        //
        // //Left IR Sensor
        // if (errorL > 0.1){
        //   setLeftMoterSpeed(0.5 * kpL); // -0.4
        //   setRightMoterSpeed(-0.2 * kpL);
        // }
        // else if (errorL < - 0.1){
        //   if (errorL < - 0.3){
        //     int flag = 0;
        //     while (flag < 6 ){
        //       setLeftMoterSpeed(0.8);
        //       setRightMoterSpeed(0.8);
        //       Wait(0.2);
        //       flag++;
        //     }
        //   }
        //   setLeftMoterSpeed(-0.2 * kpL);
        //   setRightMoterSpeed(0.5 * kpL); //0.2
        // }

        //Right IR sensor
        // if (errorR > 0.1){
        //   setLeftMoterSpeed(-0.2 * kpR); // -0.4
        //   setRightMoterSpeed(0.5 * kpR);
        // }
        // else if (errorR < - 0.1){
        //   if (errorR < - 0.3){
        //     flag = 1;
        //     while (flag){
        //       setLeftMoterSpeed(0.8);
        //       setRightMoterSpeed(0.8);
        //       Wait(1.5);
        //       setLeftMoterSpeed(0.5 * kpR);
        //       setRightMoterSpeed(-0.2 * kpR);
        //       Wait(0.7);  //
        //       flag = 0;
        //     }
        //   }
        //   setLeftMoterSpeed(0.5 * kpR);
        //   setRightMoterSpeed(-0.2 * kpR); //0.2
        // }

        // Micro Servo Motor
        // float a;
        // for (a = 0.0; a < 1.0; a += 0.1){
        //   SetServo(servo, a);
        //   wait(0.5);
        // }
        // for (a = 1.0; a > 0.0; a _= 0.1){
        //   SetServo(servo, a);
        //   wait(0.5);
        // }

        //LineSensor
        int max1 = 0;
        int max2 = 0;
        int index1, index2, sum;
        LineSensorReadArray(line, value);
        // find Max
        // for (int i = 0; i <= 7; i++){
        //   if (value[i] >= max1) {
        //     max1 = value[i];
        //     index1 = i;
        //   }
        // }
        // // find second Max
        // for (int i = 0; i <= 7; i++){
        //   if (value[i] >= max2 && value[i] < max1){
        //     max2 = value[i];
        //     index2 = i;
        //   }
        // }
        // for (int i = 0; i <= 7; i++){
        //   if (i == index1 || i == index2){
        //     value[i] = 1;
        //   }
        //   else{
        //     value[i] = 0;
        //   }
        // }
        // // reset value
        //
        int weight[8] = {-4,-3,-2,-1,1,2,3,4};
        int outputArr[8];
        for (int i=0; i<8; i++){
          if (value[i] == INFINITY){
            value[i] = 1;
          }
          else{
            value[i] = 0;
          }
        }
        for(int i = 0; i < 8; i++){
          outputArr[i] = weight[i]*value[i];
        }
        for (int i = 0; i <= 7; i++){
          sum += outputArr[i];
        }
        // setLeftMoterSpeed(0.8 + 0.04 * sum);
        // setRightMoterSpeed(0.8 - 0.04 * sum);

        //Printf("%d\n", sum);
        Printf("%d\n", sum);
  //       Printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t\n", value[0], value[1], value[2],
  // value[3], value[4], value[5], value[6], value[7]);
        //Wait(0.01);
        Wait(0.5);
    }
}
