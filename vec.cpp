#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"
#include <thread>   // For threads
#include <future>  // For async tasks 

using namespace vex;

// Robot configuration code.
motor leftMotorA = motor(PORT1, ratio18_1, true);
motor leftMotorB = motor(PORT2, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT3, ratio18_1, false);
motor rightMotorB = motor(PORT4, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1.2);

motor intakeMotorA = motor(PORT5, ratio18_1, false);
motor intakeMotorB = motor(PORT6, ratio18_1, true); 
motor_group intake = motor_group(intakeMotorA, intakeMotorB);

digital_out ClawPiston = digital_out(Brain.ThreeWirePort.A); 
digital_out arm_thingy = digital_out(Brain.ThreeWirePort.B);
motor ClawMotor = motor(PORT8, vex::gearSetting::ratio18_1, false); 

// Function to move the robot forward (time-based)
void goForward(double time, int speed) {
  LeftDriveSmart.spin(forward, speed, pct);
  RightDriveSmart.spin(forward, speed, pct);
  wait(time, sec); 
  LeftDriveSmart.stop();
  RightDriveSmart.stop(); 
}

void goBackward(double time, int speed) {
  LeftDriveSmart.spin(reverse, speed, pct);
  RightDriveSmart.spin(reverse, speed, pct);
  wait(time, sec); 
  LeftDriveSmart.stop();
  RightDriveSmart.stop(); 
}

// Function to turn the robot (time-based)
void turnLeft(double time, int speed) {
  LeftDriveSmart.spin(forward, speed, pct);
  RightDriveSmart.spin(reverse, speed, pct);
  wait(time, sec); 
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

// Function to turn the robot (time-based)
void turnRight(double time, int speed) {
  LeftDriveSmart.spin(reverse, speed, pct);
  RightDriveSmart.spin(forward, speed, pct);
  wait(time, sec); 
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

// Function to run the intake
void runIntake(int speed) {
  intake.spin(forward, speed, pct); 
}

void stopIntake() {
  intake.stop();
}

// Function to score rings
void scoreRings() {
  goForward(-1, 100); 

  ClawMotor.spin(forward, 100, pct); 
  wait(1, sec); 
  ClawMotor.stop(); 
}


void position2Autonomous() {
  goBackward(1, 45);
  ClawPiston.set(false);
  ClawPiston.set(true);
  wait(1, sec); 
  runIntake(70);
  stopIntake();
  turnRight(0.38, 50); 
  wait(1, sec); 
  auto driveForwardWrapper = []() { goForward(0.5, 50); };

  // Use the wrapper function to create the thread
  thread driveThread(driveForwardWrapper);
  driveThread.detach();

  auto runIntakeWrapper = []() { runIntake(70); };

  // Use the wrapper function to create the thread
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(4, sec); 
  stopIntake();

  turnRight(0.38, 50);
  goBackward(0.7, 40); 
  ClawPiston.set(false); 
  // arm_thingy.set(true);
  // arm_thingy.set(false);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  position2Autonomous(); 

  while (true) {
    wait(20, msec);
  }
  
}
