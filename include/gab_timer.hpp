#pragma once

class Timer {
  public:
    Timer();

    void setTimePeriod(int t);
    void setEnabled(bool e);
    bool canRun();

    
    
  private:
    int timePeriod;
    bool enabled;
    int previousRunTime;
};