#ifndef SERVO_H
#define SERVO_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#define PWM_PIN 1
#define TURN_RANGE 512
#define STOP 512
#define LEFT 76
#define RIGHT 72

void turn_left(int);
void turn_right(int);
void init_GPIO();
void stop();

#endif
