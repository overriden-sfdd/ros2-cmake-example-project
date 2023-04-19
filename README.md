# ros2-cmake-example-project

## Requirements
cmake version >= 3.16

gcc/g++ version >= 9.0

## Compile
Enter the root directory of the project and do the following:
```
colcon build --base-paths src && . install/setup.sh
```

## Run
First launch nodes
```
ros2 launch launch/launch_example.py
```
Then publish create signal from the CLI
```
ros2 topic pub create std_msgs/msg/Bool "data: 1"
```