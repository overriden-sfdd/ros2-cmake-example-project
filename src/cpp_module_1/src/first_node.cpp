#include "first_node.hpp"

#include <string>
#include <vector>

FirstNode::FirstNode()
    : Node("point_enhancer")
{
    init();
}

void FirstNode::init()
{
    m_point_sub = create_subscription<sensor_msgs::msg::ChannelFloat32>(
        "point", 1, std::bind(&FirstNode::receive_point, this, std::placeholders::_1));

    m_enhanced_point_pub = create_publisher<sensor_msgs::msg::ChannelFloat32>("enhanced_point", 10);

    m_frame_counter_pub = create_publisher<std_msgs::msg::UInt32>("frame_count", 10);
}

void FirstNode::receive_point(sensor_msgs::msg::ChannelFloat32::SharedPtr msg)
{
    const std::vector<float> point(msg->values);
    if (point.size() >= 2) {
        // Randomly change the coordinates of the point
        publish_enhanced_point({
            point[0] + static_cast<float>(rand() % 255),
            point[1] + static_cast<float>(rand() % 255),
        });
    } else {
        RCLCPP_INFO(this->get_logger(), "Warning: point size must be >= 2, but got %d", point.size());
    }
    publish_frame_counter();
}

void FirstNode::publish_enhanced_point(const std::pair<float, float> &enhanced_point)
{
    sensor_msgs::msg::ChannelFloat32 out_enhanced_point {};
    out_enhanced_point.values.push_back(enhanced_point.first);
    out_enhanced_point.values.push_back(enhanced_point.second);
    RCLCPP_INFO(this->get_logger(), "Publishing enhanced point");
    m_enhanced_point_pub->publish(out_enhanced_point);
}

void FirstNode::publish_frame_counter()
{
    RCLCPP_INFO(this->get_logger(), "Publishing frame number: %d", m_frame_number);
    auto message = std_msgs::msg::UInt32();
    message.data = m_frame_number++;
    m_frame_counter_pub->publish(message);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<FirstNode> first_node = std::make_shared<FirstNode>();
    rclcpp::spin(first_node);
}
