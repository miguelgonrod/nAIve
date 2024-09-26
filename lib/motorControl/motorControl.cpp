#include <motorControl.h>

ESP32Encoder encoder1;
ESP32Encoder encoder2;

double Kp1 = 2, Ki1 = 5, Kd1 = 1;
double Kp2 = 2, Ki2 = 5, Kd2 = 1;

double vel_deseada_motor1, vel_actual_motor1, salida_motor1;
PID pid_motor1(&vel_actual_motor1, &salida_motor1, &vel_deseada_motor1, Kp1, Ki1, Kd1, DIRECT);

double vel_deseada_motor2, vel_actual_motor2, salida_motor2;
PID pid_motor2(&vel_actual_motor2, &salida_motor2, &vel_deseada_motor2, Kp2, Ki2, Kd2, DIRECT);

float vel_linear, vel_angular;

void pidSetup(){
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    ESP32Encoder::useInternalWeakPullResistors = puType::up;
    encoder1.attachFullQuad(ENCODER1_A, ENCODER1_B);
    encoder2.attachFullQuad(ENCODER2_A, ENCODER2_B);

    Serial.begin(115200);

    pid_motor1.SetMode(AUTOMATIC);
    pid_motor2.SetMode(AUTOMATIC);

    pid_motor1.SetOutputLimits(-255, 255);
    pid_motor2.SetOutputLimits(-255, 255);
}

void applyPID(float linearX, float angularZ){
    vel_deseada_motor1 = vel_linear - distancia_entre_ruedas * vel_angular / 2;
    vel_deseada_motor2 = vel_linear + distancia_entre_ruedas * vel_angular / 2;

    vel_actual_motor1 = getMotorSpeed(encoder1.getCount());
    vel_actual_motor2 = getMotorSpeed(encoder2.getCount());

    pid_motor1.Compute();
    pid_motor2.Compute();

    controlarMotor(ENA, IN1, IN2, salida_motor1);
    controlarMotor(ENB, IN3, IN4, salida_motor2);

}

void controlarMotor(int enable_pin, int pin1, int pin2, double pwm_value) {
    if(pwm_value > 0) {
        // Motor gira en una dirección
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    }
    else{
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        pwm_value = -pwm_value;
    }
    analogWrite(enable_pin, constrain(pwm_value, 0, 255));
}

double getMotorSpeed(long encoder_ticks){
    double velocidad = encoder_ticks * 0.00087266; // 0.00087266 = 2 * PI / 3600
    return velocidad;
}

void adjustPID(PID myPID, double newKp, double newKi, double newKd){
    myPID.SetTunings(newKp, newKi, newKd);
}