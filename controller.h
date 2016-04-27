#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#define PWM_PIN 1
#define TURN_RANGE 512
#define STOP 512

void turn_left(int);
void turn_right(int);
void init_GPIO();

#endif
