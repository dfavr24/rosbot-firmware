#pragma once
#include <Arduino.h>
#include <std_msgs/msg/u_int32.h>
#include "publisher_interface.hpp"

struct ActuatorFbPublisher {
  const char* topic;
  QueueHandle_t queue;
};

class ActuatorFbPublisher : public PublisherInterface {
 public:
  ActuatorFbPublisher(ActuatorFbPublisherConfig cfg)
      : PublisherInterface(cfg.topic), cfg_(cfg) {}
  rcl_ret_t init(rcl_node_t& node, rcl_allocator_t& allocator) override {
    std_msgs__msg__UInt32__init(&msg_);
    return rclc_publisher_init_best_effort(
        &pub_, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt32), topic_);
  }
  rcl_ret_t publish() override {
      uint32_t pulse_count = 0;
      if (xQueueReceive(cfg_.queue, &pulse_count, 0) == pdTRUE) {
          msg_.data = pulse_count;
          return rcl_publish(&pub_, &msg_, NULL);
      }
      return RCL_RET_OK;
  }
  rcl_ret_t fini(rcl_node_t& node) override {
    std_msgs__msg__UInt32__fini(&msg_);
    return rcl_publisher_fini(&pub_, &node);
  }
 private:
  ActuatorFbPublisher cfg_;
  rcl_publisher_t pub_;
  std_msgs__msg__UInt32 msg_;
};