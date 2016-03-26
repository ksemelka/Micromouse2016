#ifndef PID_H
#define PID_H

class PID {
  public:
  //Constants used in some of the functions below
    #define AUTOMATIC 1
    #define MANUAL  0
    #define DIRECT  0
    #define REVERSE  1

    double GetKp() const;						  // These functions query the pid for interal values.
    double GetKi() const;
    double GetKd() const;
    int GetMode() const;
    int GetDirection() const;
  private:
    void Initialize();
    double kp;
    double ki;
    double kd;
    int controllerDirection;
};

#endif /*PID_H*/
