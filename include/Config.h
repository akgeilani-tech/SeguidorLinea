#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ======================================================
// TB6612FNG
// ======================================================

// MOTOR DERECHO

#define MOTOR_RIGHT_PWM        3 
#define MOTOR_RIGHT_IN2        4 
#define MOTOR_RIGHT_IN1        5 

// STANDBY

#define MOTOR_STBY             6 

// MOTOR IZQUIERDO

#define MOTOR_LEFT_IN1         7 
#define MOTOR_LEFT_IN2         8 
#define MOTOR_LEFT_PWM         9

// ======================================================
// QTR-8A
// ======================================================

#define SENSOR_COUNT           8

// ======================================================
// PID
// ======================================================

#define KP                     0.11f  //0.085
#define KI                     0.00f
#define KD                     1.60f   //2.10

// ======================================================
// SPEED
// ======================================================

#define BASE_SPEED             120 //150
#define MAX_SPEED              255  //255
#define MIN_SPEED              0 //-255

#define CURVE_FACTOR           0.055f //0.060  0.055

// ======================================================
// CONTROL LOOP
// ======================================================

#define LOOP_TIME_US           1000

// ======================================================
// SENSOR
// ======================================================

#define LINE_CENTER            3500

#endif