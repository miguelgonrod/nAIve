#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Encoder.h>
#include <PID_v1.h>

#define MOTOR_PIN 33

#define ENCODER_PIN_A 34
#define ENCODER_PIN_B 35

void pidSetup();

#endif