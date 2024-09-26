#include <motorControl.h>

ESP32Encoder encoder;
long currentPosition = 0;
long previousPosition = 0;

double setpoint = 0, input = 0, output = 0;
double Kp = 2.0, Ki = 5.0, Kd = 1.0;
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void pidSetup(){
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(-255, 255);

    encoder.attachFullQuad(ENCODER_PIN_A, ENCODER_PIN_B);
    encoder.clearCount();

    Serial.begin(115200);
}

void applyPID(){
    input = encoder.getCount();

    myPID.Compute();

    controlMotor(output);

    Serial.print("Setpoint: "); Serial.print(setpoint);
    Serial.print(" | Input: "); Serial.print(input);
    Serial.print(" | Output: "); Serial.println(output);
}

void controlMotor(double output) {
    if(output > 0) {
        // Motor gira en una dirección
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, output);  // Controlar velocidad con PWM
    }
    else if (output < 0){
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(ENA, -output);
    }
    else{
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(ENA, 0);
    }
}

void setNewSetpoint(long newSetpoint){
    setpoint = newSetpoint;
}

void adjustPID(double newKp, double newKi, double newKd){
    myPID.SetTunings(newKp, newKi, newKd);
}