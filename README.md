# ros2-cmake-example-project

## General

This repository contains a small demo of a C++ project within ROS 2 environment using multiple nodes communicating asynchronously with each other using ROS middleware. Plus an extra Python tool package.

There are two C++ nodes: point creator which creates random points, and point enhancer which, well, randomly enhances points. Additionally, there is one Python node that draws a graph of enhanced points online.

**Note:** usually a name of a directory holding a package should have the same name as the name of the package (i.e., `cpp_package_1` should be `firstcpp` instead), but for clarity reasons (this is an educational repo after all) the name of the directory was different. Exactly the same logic is applied to node names. It is believed that users will understand meaning of certain values better this way.

## ROS packages description

**cpp_package_1/point_enhancer**
- type: subscriber | type: ChannelFloat32 | name: point | general: listens for float points
- type: publisher | type: ChannelFloat32 | name: enhanced_point | general: publishes enhanced float points
- type: publisher | type: UInt32 | name: frame_count | general: publishes the frame counter

**cpp_package_2/point_creator**
- type: subscriber | type: UInt32 | name: frame_count | general: listens for the frame counter
- type: subscriber | type: Bool | name: create | general: listens for a create signal; once a flag with value = 1 is received, float points are created
- type: publisher | type: ChannelFloat32 | name: point | general: publishes float points


**py_package_3/pymodule/plotter_node**
- type: subscriber | type: UInt32 | name: frame_count | general: listens for the frame counter
- type: subscriber | type: ChannelFloat32 | name: enhanced_point | general: listens for enhanced float points

## Requirements
ROS 2 environment installed

cmake version >= 3.16

gcc/g++ version >= 9.0

python 3 version >= 3.8

--------------------------
Please install ROS 2 in advance. You might try installing some of the dependencies running:
```
bash bin/deps-install.sh
```

## Build
Activate ROS environment; for example:
```
source /opt/ros/foxy/setup.zsh
```
Then enter the root directory of the project and do the following:
```
colcon build --base-paths src && . install/setup.sh
```

## Run
First launch nodes
```
ros2 launch launch/launch_example.py
```
Then publish a create signal from the CLI
```
ros2 topic pub create std_msgs/msg/Bool "data: 1"
```