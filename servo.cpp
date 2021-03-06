#include "servo.h"

void stop() {
	pwmWrite(PWM_PIN, STOP);
}

void turn_left() {
  pwmWrite(PWM_PIN, LEFT);
  delay(100);
}

void turn_right() {
  pwmWrite(PWM_PIN, RIGHT);
  delay(100);
}

void close_servo() {
  pwmWrite(PWM_PIN, 0);
  delay(200);
  std::cout << "Closing servo" << std::endl;
}


void init_GPIO() {
	if(wiringPiSetup() == -1) { /* apparently this is superfluous now*/
		exit(1);
	}
	pinMode(PWM_PIN, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(384);
  pwmSetRange(1000);

}
