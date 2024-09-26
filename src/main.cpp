#include <Arduino.h>

#include "motorControl.h"
#include "microROS.h"

microROS micro_ROS;

void setup() { 
  pidSetup();
  micro_ROS.initialize();
  micro_ROS.subscriber_define();
  micro_ROS.executors_start();
}

void loop() {
  micro_ROS.start_receiving_msgs();
}