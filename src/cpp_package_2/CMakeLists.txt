cmake_minimum_required(VERSION 3.16)
project(secondcpp)

set(NODE_NAME "point_creator_node")

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(${NODE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/second_node.cpp)

ament_target_dependencies(${NODE_NAME}
    rclcpp
    ament_index_cpp
    sensor_msgs
)

install(TARGETS
    ${NODE_NAME}
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
