#ifndef PID_H
#define PID_H

class PID {
  public:
    double GetKp() const;						  // These functions query the pid for internal values.
    double GetKi() const;
    double GetKd() const;
  private:
    void Initialize();
    double kp;
    double ki;
    double kd;
};

#endif /*PID_H*/
