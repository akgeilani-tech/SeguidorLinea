#include "Motor.h"
#include "Config.h"

Motor::Motor()
{
}

void Motor::begin()
{
    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);

    pinMode(MOTOR_RIGHT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_RIGHT_IN2, OUTPUT);

    pinMode(MOTOR_STBY, OUTPUT);

    enable();
}

void Motor::enable()
{
    digitalWrite(
        MOTOR_STBY,
        HIGH
    );
}

void Motor::disable()
{
    digitalWrite(
        MOTOR_STBY,
        LOW
    );
}

void Motor::driveMotor(
    uint8_t pwm,
    uint8_t in1,
    uint8_t in2,
    int speed
)
{
    speed = constrain(
        speed,
        MIN_SPEED,
        MAX_SPEED
    );

    if(speed > 0)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);

        analogWrite(
            pwm,
            speed
        );
    }
    else if(speed < 0)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);

        analogWrite(
            pwm,
            -speed
        );
    }
    else
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);

        analogWrite(pwm, 0);
    }
}

void Motor::setSpeed(
    int left,
    int right
)
{
    driveMotor(
        MOTOR_LEFT_PWM,
        MOTOR_LEFT_IN1,
        MOTOR_LEFT_IN2,
        left
    );

    driveMotor(
        MOTOR_RIGHT_PWM,
        MOTOR_RIGHT_IN1,
        MOTOR_RIGHT_IN2,
        right
    );
}

void Motor::brake()
{
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);

    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}