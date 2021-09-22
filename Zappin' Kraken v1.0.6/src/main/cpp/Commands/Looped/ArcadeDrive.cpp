#include "Commands/Looped/ArcadeDrive.h"
#include "Robot.h"
#include "RobotMap/IDs.h"
#include "RobotMap/Constants.h"

ArcadeDrive::ArcadeDrive() {
  Requires(&Robot::m_drivetrain);
}

void ArcadeDrive::Initialize() {
  invert_driving_was_pressed = Robot::m_oi.GetDriverButton(kInvertDrivingButton);
  first_timer = true;
  m_timer.Reset();
  m_timer.Start();
}

void ArcadeDrive::Execute() {
  if (Robot::m_oi.GetDriverButton(kInvertDrivingButton) == true) {
    if (invert_driving_was_pressed == false) {
      invert_driving *= -1;
      m_timer.Reset();
      first_timer = false;
    }
    invert_driving_was_pressed = true;
  } else {
    invert_driving_was_pressed = false;
  }

  left_y_input = Robot::m_oi.GetDriverAxis(kLeftDriveAxisY);
  right_x_input = Robot::m_oi.GetDriverAxis(kRightDriveAxisX);

  Robot::m_drivetrain.SetCurvedTeleOpArcadeSpeed(invert_driving * left_y_input, invert_driving * (right_x_input * kArcadeRotationalModifier));

  if (first_timer == false) {
    if (m_timer.Get() < kSingleRumbleTime) {
      Robot::m_oi.SetDriverRumble(kSingleRumbleStrength);
    } else {
      Robot::m_oi.SetDriverRumble(0);
      first_timer = true;
    }
  }
}

bool ArcadeDrive::IsFinished() {
  return false;
}

void ArcadeDrive::End() {}

void ArcadeDrive::Interrupted() {}