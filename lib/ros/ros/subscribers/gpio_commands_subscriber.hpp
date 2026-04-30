#pragma once
#include <Arduino.h>
#include <std_msgs/msg/u_int8_multi_array.h>
#include "include/rosbot_xl/config.hpp"

inline void gpioCommandCallback(const void* msg_in) {
  if (!msg_in) return;
  const auto* msg = static_cast<const std_msgs__msg__UInt8MultiArray*>(msg_in);
  if (msg->data.size >= 3) {
    digitalWrite(EXT_GPIO1, msg->data.data[0] ? HIGH : LOW);
    digitalWrite(EXT_GPIO2, msg->data.data[1] ? HIGH : LOW);
    analogWrite(EXT_PWM1, msg->data.data[2]);
  }
}