#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <ESP32Encoder.h>
#include <PID_v1.h>

#define ENA 13
#define IN1 12
#define IN2 14

#define ENCODER_PIN_A 34
#define ENCODER_PIN_B 35

void pidSetup();
void applyPID();
void controlMotor(double output);
void setNewSetpoint(long newSetpoint);
void adjustPID(double newKp, double newKi, double newKd);

#endif