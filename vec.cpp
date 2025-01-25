#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"
#include <thread>   // For threads
#include <future>  // For async tasks 
#include <iostream>

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

void redPositiveAutonomous() {
  turnRight(0.2, 50);
  goBackward(1, 20);
  turnLeft(0.3, 50); 
  goBackward(0.6, 40);
  ClawPiston.set(true);
  wait(1, sec); 
  runIntake(70);
  stopIntake();
  turnRight(0.46, 50); 
  auto driveForwardWrapper = []() { goForward(1.6, 50); };
  thread driveThread(driveForwardWrapper);
  driveThread.detach();
  auto runIntakeWrapper = []() { runIntake(70); };
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(1, sec); 
  turnRight(0.1, 50);
  wait(1, sec);
  goBackward(1.5, 50);
  wait(3, sec);
  stopIntake(); 
}

void bluePositiveAutonomous() {
  turnLeft(0.2, 50);
  goBackward(1.5, 20);
  turnRight(0.3, 50); 
  goBackward(0.7, 40);
  ClawPiston.set(true);
  wait(1, sec); 
  runIntake(70);
  stopIntake();
  turnLeft(0.6, 50); 
  auto driveForwardWrapper = []() { goForward(1.6, 50); };
  thread driveThread(driveForwardWrapper);
  driveThread.detach();
  auto runIntakeWrapper = []() { runIntake(70); };
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(1, sec); 
  turnLeft(0.1, 50);
  wait(1, sec);
  goBackward(1.5, 50);
  wait(3, sec);
  stopIntake(); 
}

void RedNegativeAutonomous() {
  goBackward(1.03, 25);
  turnLeft(0.16, 50);
  goBackward(0.43, 30);
  ClawPiston.set(true);
  wait(1, sec); 
  runIntake(70);
  wait(1, sec);
  stopIntake();
  turnLeft(0.28, 50); 
  auto driveForwardWrapper = []() { goForward(1.13, 40); };
  thread driveThread(driveForwardWrapper);
  driveThread.detach();
  auto runIntakeWrapper = []() { runIntake(70); };
  thread intakeThread(runIntakeWrapper);
  intakeThread.detach();
  wait(1, sec); 
  goBackward(.53, 25);
  turnLeft(0.46, 50); 
  auto driveForwardWrapper2 = []() { goForward(0.75, 40); };
  thread driveThread2(driveForwardWrapper2);
  driveThread2.detach();
  auto runIntakeWrapper2 = []() { runIntake(70); };
  thread intakeThread2(runIntakeWrapper2);
  intakeThread2.detach();
  wait(1, sec); 
  goForward(.53, 25);
  turnLeft(0.56, 50); 
  goBackward(1.53, 25);
  /*wait(1, sec); 
  stopIntake(); */

}

void autonomousRunner(const std::string& input) {
    switch (input[0]) { 
        case '0':
            bluePositiveAutonomous(); 
            break;
        case '1':
            redPositiveAutonomous();
            break;
    }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  autonomousRunner("0")
}
