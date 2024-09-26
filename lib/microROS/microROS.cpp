#include "microROS.h"
#include "motorControl.h"

microROS::microROS(){
}

void microROS::initialize(){
    Serial.begin(115200);
    Serial.println("ROS cmd_vel node started");

    // Adding Wifi
    IPAddress agent_ip(192, 168, 0, 8); // change this line to your computer IP
    size_t agent_port = 8888; // Don't change this port unless you know what you are doing and you have 8888 port already in use

    char ssid[] = "FAMILIA GONROD 2.4 ETB "; // change this line with your wifi name
    char psk[]= "MedellinCr20*"; // change this line with your password

    set_microros_wifi_transports(ssid, psk, agent_ip, agent_port);
    // set_microros_serial_transports(Serial);  // uncomment this line if you want to use serial instead of wifi

    delay(2000);

    allocator = rcl_get_default_allocator();
    rclc_support_init(&support, 0, NULL, &allocator);
    rclc_node_init_default(&node, "cmd_vel_sub", "", &support);
}

void microROS::executors_start(){
  rclc_executor_init(&executor, &support.context, 1, &allocator);
  rclc_executor_add_subscription(&executor, &cmd_vel_sub, &msg, &microROS::cmd_vel_callback, ON_NEW_DATA);

  Serial.println("Executors Started");
}

void microROS::subscriber_define(){
    rclc_subscription_init_default(
    &cmd_vel_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/cmd_vel"); // define subcriber topic and datatype

}

void microROS::cmd_vel_callback(const void *msg_recv){
    const geometry_msgs__msg__Twist * recieved_data = (const geometry_msgs__msg__Twist *) msg_recv ;
    
    applyPID(recieved_data->linear.x, recieved_data->angular.z);

}

void microROS::start_receiving_msgs(){
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    delay(100);
}