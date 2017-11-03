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

void blink(void) {
    SetPin(PIN_B1, blink_on);
    blink_on = !blink_on;
}

void setLeftMoterSpeed(float speed){
  SetMotor(leftMotor, speed);
  leftSpeed = speed;
}
void setRightMoterSpeed(float speed){
  SetMotor(rightMotor, speed);
  rightSpeed = speed;
}


int main(void) {

    // Initialization part

    //CallEvery(blink, 0, 0.5);

    //Switch
    //InitSwitch();

    //Continuous Servo Motor; true and false make motors
    //turn into opposite directions.
    leftMotor = InitializeServoMotor(PIN_E4, false); //forward with false
    rightMotor = InitializeServoMotor(PIN_E5, true);  // forward

    // Micro Servo Motor
    // tServo *servo = InitializeServo(PIN_XX);
    //
    // LineSensor
    // tLineSensor *line = InitializeGPIOLineSensor(PIN_B0, PIN_B1, PIN_E4, PIN_E5, PIN_B4, PIN_A5, PIN_A6, PIN_A7);
    // float value[8];
    //
    // Infrared Distance Sensor
    // ADC is only supported on a limited number of pins in hardware
    // The following pins are supported:
    // PIN_B4 PIN_B5 PIN_D0  PIN_D1   PIN_D2  PIN_D3  PIN_E0
    // PIN_E1  PIN_E2  PIN_E3  PIN_E4  PIN_E5
    //tADC *IRLeft = InitializeADC(PIN_D1);
    float readIRLeft;
    float error;
    float percentError;
    //float allError = 0;
    float desired = 0.40;
    float kp;
    //float ki;
    tADC *IRRight = InitializeADC(PIN_D0);
    float readIRRight;
    float output;



    while (1) {
        // //Continuous Servo Motor V(left, 0) = V(right0.258)
        // // speed = changing k * speed(set)
        setLeftMoterSpeed(0.8);  //< -0.3: backward
        setRightMoterSpeed(0.8); // 0; 0.3
        //
        //
        // IRSensor
        // readIRLeft = ADCRead(IRLeft);
        // Printf("IR Sensor1 value is %f\n", readIRLeft);
        readIRRight = ADCRead(IRRight);
        error = readIRRight - desired;
        // percentError from -1 to 4; when error = 0, percentError = 0
        percentError = error / desired - 0.5;
        // percent Error from -4 to 4; when error = 0, percentError = 0
        kp = 1 + fabs(0.4 * percentError);
        //output = error * kp;
        if (error > 0.1){
          setLeftMoterSpeed(-0.2 * kp); // -0.4
          setRightMoterSpeed(0.5 * kp);
        }
        else if (error < -0.1){
          setLeftMoterSpeed(0.5 * kp);
          setRightMoterSpeed(-0.2 * kp); //0.2
        }
        // if (error < 0){
        //   Printf("The error is %f,    too far.\n", error);
        // }
        // else {
        //   Printf("The error is %f,    too close.\n", error);
        // }
        Wait(0.01);

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
        //LineSensorReadArray(line, value);
        //Printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t\n", value[0], value[1], value[2],
  //value[3], value[4], value[5], value[6], value[7]);
    }
}
