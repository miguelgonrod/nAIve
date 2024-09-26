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
        
    private:
        rcl_subscription_t cmd_vel_sub;
        geometry_msgs__msg__Twist msg;
        rclc_executor_t executor;
        rclc_support_t support;
        rcl_allocator_t allocator;
        rcl_node_t node;
};

#endif