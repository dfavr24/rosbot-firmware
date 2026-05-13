#pragma once
#include <Arduino.h>
#include <std_msgs/msg/u_int8_multi_array.h>
#include "rosbot_xl/config.hpp"

inline void actuatorCommandCallback(const void* msg_in) {
  // g_comm_mgr.debugSerial()->printf("GPIO CALLBACK TRIGGERED");

  if (!msg_in) return;
  const auto* msg = static_cast<const std_msgs__msg__UInt8MultiArray*>(msg_in);
  // g_comm_mgr.debugSerial()->printf("\r\n%u", msg->data.size);
  if (msg->data.size >= 3) {
    // g_comm_mgr.debugSerial()->printf("\r\nGPIO1 (DIR) = %u", msg->data.data[0]);
    // g_comm_mgr.debugSerial()->printf("\r\nGPIO2 (EN) = %u", msg->data.data[1]);
    // g_comm_mgr.debugSerial()->printf("\r\nPWM1 = %u\r\n", msg->data.data[2]);

    digitalWrite(EXT_GPIO1, msg->data.data[0] ? HIGH : LOW);
    digitalWrite(EXT_GPIO2, msg->data.data[1] ? HIGH : LOW);
    analogWrite(EXT_PWM1, msg->data.data[2]);
  }
}