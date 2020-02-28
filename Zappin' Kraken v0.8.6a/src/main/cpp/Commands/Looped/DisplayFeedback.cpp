#include "Commands/Looped/DisplayFeedback.h"
#include "Robot.h"
#include "RobotMap/IDs.h"
#include "RobotMap/Tuning.h"

DisplayFeedback::DisplayFeedback() {}

void DisplayFeedback::Initialize() {
  previous_dpad_input = Robot::m_oi.GetOperatorDPad();
  manual_control_was_pressed = Robot::m_oi.GetOperatorButton(kStorageManualControlButton);
}

void DisplayFeedback::Execute() {
  if (previous_dpad_input != Robot::m_oi.GetOperatorDPad()) {
    switch (Robot::m_oi.GetOperatorDPad()) {
      case kIncrementRPMPOVAngle:
        Robot::m_limelight.IncrementLastRPMProfile(kShooterRPMIncrement);
        break;
      case kDecrementRPMPOVAngle:
        Robot::m_limelight.IncrementLastRPMProfile(-kShooterRPMIncrement);
        break;
      case kIncrementAngleOffsetPOVAngle:
        Robot::m_limelight.IncrementAngleOffset(kShooterAngleIncrement);
        break;
      case kDecrementAngleOffsetPOVAngle:
        Robot::m_limelight.IncrementAngleOffset(-kShooterAngleIncrement);
        break;
    }
  }
  previous_dpad_input = Robot::m_oi.GetOperatorDPad();

  if ((Robot::m_oi.GetOperatorButton(kStorageManualControlButton) == true) && (manual_control_was_pressed == false)) {
    Robot::m_storage.SetManualControl(!Robot::m_storage.GetManualControl());
  }
  manual_control_was_pressed = Robot::m_oi.GetOperatorButton(kStorageManualControlButton);
}

bool DisplayFeedback::IsFinished() {
  return false;
}

void DisplayFeedback::End() {}

void DisplayFeedback::Interrupted() {}
