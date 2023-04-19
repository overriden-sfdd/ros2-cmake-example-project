from sensor_msgs.msg import ChannelFloat32
from std_msgs.msg import UInt32
from rclpy.node import Node
import matplotlib.pyplot as plt
import numpy as np
import rclpy


class PlotterNode(Node):
    def __init__(self):
        try:
            super().__init__("plotter")
            self.enhanced_point_sub = self.create_subscription(
                ChannelFloat32, "enhanced_point", self.receive_enhanced_point, 1
            )

            self.frame_count_sub = self.create_subscription(
                UInt32, "frame_count", self.receive_frame_count, 1
            )

            self.enhanced_points = np.array([[0.0, 0.0]])

            plt.ion()
            self.plot_boundary = 100

        except Exception as e:
            print(f"Error creating subscription: {e}")
            return

    def receive_enhanced_point(self, enhanced_point_msg):
        self.enhanced_points = np.vstack(
            (self.enhanced_points, np.array(
                [[enhanced_point_msg.values[0], enhanced_point_msg.values[1]]]))
        )

    def receive_frame_count(self, frame_count_msg):
        frame_number = frame_count_msg.data
        print(f"Plotter frame number: {frame_number}")
        plt.clf()
        plt.plot(self.enhanced_points[1:, 0], self.enhanced_points[1:, 1])
        plt.show()
        plt.legend()
        plt.pause(0.01)


def main():
    rclpy.init()
    plotter_node = PlotterNode()
    rclpy.spin(plotter_node)
    plotter_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
