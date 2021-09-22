#pragma once

#include "Util/Libraries.h"

class TankDrive : public frc::Command {
  private:
    frc::Timer m_timer;
    double left_input, right_input;
    int invert_driving = 1;
    bool invert_driving_was_pressed, first_timer;

  public:
    TankDrive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};