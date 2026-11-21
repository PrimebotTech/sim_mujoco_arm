// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandCommand_damping
{
public:
  explicit Init_HandCommand_damping(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandCommand damping(::aimdk_msgs::msg::HandCommand::_damping_type arg)
  {
    msg_.damping = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_stiffness
{
public:
  explicit Init_HandCommand_stiffness(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_damping stiffness(::aimdk_msgs::msg::HandCommand::_stiffness_type arg)
  {
    msg_.stiffness = std::move(arg);
    return Init_HandCommand_damping(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_effort
{
public:
  explicit Init_HandCommand_effort(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_stiffness effort(::aimdk_msgs::msg::HandCommand::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return Init_HandCommand_stiffness(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_velocity
{
public:
  explicit Init_HandCommand_velocity(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_effort velocity(::aimdk_msgs::msg::HandCommand::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HandCommand_effort(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_position
{
public:
  explicit Init_HandCommand_position(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_velocity position(::aimdk_msgs::msg::HandCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HandCommand_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_name
{
public:
  Init_HandCommand_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandCommand_position name(::aimdk_msgs::msg::HandCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HandCommand_position(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandCommand>()
{
  return aimdk_msgs::msg::builder::Init_HandCommand_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_
