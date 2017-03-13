#ifndef SERVO_H
#define SERVO_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#define PWM_PIN 1
#define TURN_RANGE 512
#define STOP 0
#define LEFT 77
#define RIGHT 70

void turn_left();
void turn_right();
void init_GPIO();
void stop();
void close_servo();

#endif
