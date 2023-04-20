#include "second_node.hpp"

#include <iostream>
#include <string>
#include <vector>

SecondNode::SecondNode()
    : Node("point_creator")
{
    init();
}

void SecondNode::init()
{
    m_frame_count_sub = create_subscription<std_msgs::msg::UInt32>(
        "frame_count", 1, std::bind(&SecondNode::receive_frame_count, this, std::placeholders::_1));

    m_create_signal_sub = create_subscription<std_msgs::msg::Bool>(
        "create", 1, std::bind(&SecondNode::receive_create_signal, this, std::placeholders::_1));

    m_point_pub = create_publisher<sensor_msgs::msg::ChannelFloat32>("point", 10);
}

void SecondNode::receive_frame_count(std_msgs::msg::UInt32::SharedPtr msg)
{
    const auto frame_number = msg->data;
    if (frame_number % 50) {
        RCLCPP_INFO(this->get_logger(), "Received frame number %d", frame_number);
    }
}

void SecondNode::receive_create_signal(std_msgs::msg::Bool::SharedPtr msg)
{
    const auto signal = msg->data;
    RCLCPP_INFO(this->get_logger(), "Received create signal %d", signal);
    if (signal) {
        publish_point();
    }
}

void SecondNode::publish_point()
{
    sensor_msgs::msg::ChannelFloat32 out_point {};
    // Create a random point
    out_point.values.push_back(static_cast<float>(rand() % 1023));
    out_point.values.push_back(static_cast<float>(rand() % 127));
    RCLCPP_INFO(this->get_logger(), "Publishing initial point");
    m_point_pub->publish(out_point);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<SecondNode> second_node = std::make_shared<SecondNode>();
    rclcpp::spin(second_node);
}
