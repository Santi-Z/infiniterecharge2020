#include "Commands/Looped/TankDrive.h"
#include "Robot.h"
#include "RobotMap/IDs.h"
#include "RobotMap/Constants.h"

TankDrive::TankDrive() {
  Requires(&Robot::m_drivetrain);
}

void TankDrive::Initialize() {
  invert_driving_was_pressed = Robot::m_oi.GetDriverButton(kInvertDrivingButton);
  first_timer = true;
  m_timer.Reset();
  m_timer.Start();
}

void TankDrive::Execute() {
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

  left_input = Robot::m_oi.GetDriverAxis(kLeftDriveAxisY);
  right_input = Robot::m_oi.GetDriverAxis(kRightDriveAxisY);
  Robot::m_drivetrain.SetCurvedTeleOpArcadeSpeed(invert_driving * ((left_input + right_input) / 2), (left_input - right_input) / 2);

  if (first_timer == false) {
    if (m_timer.Get() < kSingleRumbleTime) {
      Robot::m_oi.SetDriverRumble(kSingleRumbleStrength);
    } else {
      Robot::m_oi.SetDriverRumble(0);
      first_timer = true;
    }
  }
}

bool TankDrive::IsFinished() {
  return false;
}

void TankDrive::End() {}

void TankDrive::Interrupted() {}