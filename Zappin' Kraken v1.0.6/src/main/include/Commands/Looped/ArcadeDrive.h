#pragma once

#include "Util/Libraries.h"

class ArcadeDrive : public frc::Command {
  private:
    frc::Timer m_timer;
    double left_y_input, right_x_input;
    int invert_driving = 1;
    bool invert_driving_was_pressed, first_timer;

  public:
    ArcadeDrive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};