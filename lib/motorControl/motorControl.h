#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <ESP32Encoder.h>
#include <PID_v1.h>

#define IN1 32
#define IN2 33
#define ENA 25

#define IN3 26
#define IN4 27
#define ENB 14

#define ENCODER1_A 34
#define ENCODER1_B 35

#define ENCODER2_A 36
#define ENCODER2_B 39

#define distancia_entre_ruedas 0.2

void pidSetup();
void applyPID(float linearX, float angularZ);
void controlarMotor(int enable_pin, int pin1, int pin2, double pwm_value);
double getMotorSpeed(long encoder_ticks);
void adjustPID(PID myPID, double newKp, double newKi, double newKd);

#endif