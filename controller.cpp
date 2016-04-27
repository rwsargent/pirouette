#include "controller.h"

void write(int value) {
  pwmWrite(PWM_PIN, value);
}
void stop() {
	pwmWrite(PWM_PIN, STOP);
}

void turn_left(int speed) {
	int pwm_value = STOP - speed;
  pwmWrite(PWM_PIN, pwm_value);
}

void turn_right(int speed) {
  
}

void close_servo(int signal) {
  pwmWrite(PWM_PIN, 0);
  delay(200);
  exit(0);
}


void init_GPIO() {
	if(wiringPiSetup() == -1) { /* apparently this is superfluous now*/
		exit(1);
	}
	pinMode(PWM_PIN, PWM_OUTPUT);
  (void)signal(SIGINT, close_servo);
  (void)signal(SIGQUIT, close_servo);
}
