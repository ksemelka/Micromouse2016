#ifndef PWM_H
#define PWM_H

#define turnMotorOff     setLeftPwm(0);setRightPwm(0)

void setLeftPwm(int);
void setRightPwm(int);

#endif /*PWM_H*/
