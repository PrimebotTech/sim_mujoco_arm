// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandState_motor_vol
{
public:
  explicit Init_HandState_motor_vol(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandState motor_vol(::aimdk_msgs::msg::HandState::_motor_vol_type arg)
  {
    msg_.motor_vol = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_motor_temp
{
public:
  explicit Init_HandState_motor_temp(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_motor_vol motor_temp(::aimdk_msgs::msg::HandState::_motor_temp_type arg)
  {
    msg_.motor_temp = std::move(arg);
    return Init_HandState_motor_vol(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_coil_temp
{
public:
  explicit Init_HandState_coil_temp(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_motor_temp coil_temp(::aimdk_msgs::msg::HandState::_coil_temp_type arg)
  {
    msg_.coil_temp = std::move(arg);
    return Init_HandState_motor_temp(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_effort
{
public:
  explicit Init_HandState_effort(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_coil_temp effort(::aimdk_msgs::msg::HandState::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return Init_HandState_coil_temp(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_velocity
{
public:
  explicit Init_HandState_velocity(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_effort velocity(::aimdk_msgs::msg::HandState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HandState_effort(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_position
{
public:
  explicit Init_HandState_position(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_velocity position(::aimdk_msgs::msg::HandState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HandState_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_name
{
public:
  Init_HandState_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandState_position name(::aimdk_msgs::msg::HandState::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HandState_position(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandState>()
{
  return aimdk_msgs::msg::builder::Init_HandState_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_
