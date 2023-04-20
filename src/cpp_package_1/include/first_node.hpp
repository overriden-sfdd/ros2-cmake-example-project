#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/channel_float32.hpp>
#include <std_msgs/msg/u_int32.hpp>
#include <utility>

class FirstNode : public rclcpp::Node
{
public:
    FirstNode();
    void init();
    void receive_point(sensor_msgs::msg::ChannelFloat32::SharedPtr msg);
    void publish_enhanced_point(const std::pair<float, float> &enhanced_point);
    void publish_frame_counter();

private:
    rclcpp::Subscription<sensor_msgs::msg::ChannelFloat32>::SharedPtr m_point_sub;
    rclcpp::Publisher<sensor_msgs::msg::ChannelFloat32>::SharedPtr m_enhanced_point_pub;
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr m_frame_counter_pub;
    uint32_t m_frame_number = 0;
};
