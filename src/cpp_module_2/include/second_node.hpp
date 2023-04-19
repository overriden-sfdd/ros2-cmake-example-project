#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/channel_float32.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/u_int32.hpp>

class SecondNode : public rclcpp::Node
{
public:
    SecondNode();
    void init();
    void receive_frame_count(std_msgs::msg::UInt32::SharedPtr msg);
    void receive_create_signal(std_msgs::msg::Bool::SharedPtr msg);
    void publish_point();

private:
    rclcpp::Subscription<std_msgs::msg::UInt32>::SharedPtr m_frame_count_sub;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr m_create_signal_sub;
    rclcpp::Publisher<sensor_msgs::msg::ChannelFloat32>::SharedPtr m_point_pub;
};
