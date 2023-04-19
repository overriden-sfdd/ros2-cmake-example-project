# launch module includes elements to launch all types of processes and actions
from launch import LaunchDescription

# launch_ros module includes elements to launch ROS 2 processes and actions
from launch_ros.actions import Node

# This function is always needed


def generate_launch_description():

    # Declare a variable Node for each node
    firstcpp_node = Node(
        package="firstcpp",
        executable="point_enhancer_node",
    )
    secondcpp_node = Node(
        package="secondcpp",
        executable="point_creator_node",
    )
    plotter_node = Node(
        package="pymodule",
        executable="plotter_node"
    )

    # Add the nodes and the process to the LaunchDescription list
    ld = [firstcpp_node, secondcpp_node]
    return LaunchDescription(ld)
