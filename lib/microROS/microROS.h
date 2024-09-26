#ifndef MICROROS_H
#define MICROROS_H

#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>


class microROS{
    public:
        microROS();
        void initialize();
        void executors_start();
        void subscriber_define();
        static void cmd_vel_callback(const void *msg_recv);
        void start_receiving_msgs();
};

#endif