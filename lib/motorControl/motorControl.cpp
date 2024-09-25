#include <motorControl.h>

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
long currentPosition = 0;
long previousPosition = 0;

double setpoint, input, output;
double Kp = 2.0, Ki = 5.0, Kd = 1.0;
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void pidSetup(){
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 255);
}

void applyPID(){
    currentPosition = encoder.read();

    input = currentPosition;

    myPID.Compute();
    analogWrite(MOTOR_PIN, output);
}

void setNewSetpoint(long newSetpoint){
    setpoint = newSetpoint;
}

void adjustPID(double newKp, double newKi, double newKd){
    myPID.SetTunings(newKp, newKi, newKd);
}