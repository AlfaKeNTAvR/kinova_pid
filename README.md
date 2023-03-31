# ROS PID Package for Kinova Gen3 Joints Control

This package is a modified version of Andrew J Zelenak's ROS PID package, specifically tailored for controlling the joints of a Kinova Gen3 7DoF robot arm. The package provides an implementation of a Proportional-Integral-Derivative (PID) controller to accurately control the robot's joints, ensuring smooth and precise movement. The package is required to run [kinova_positional_control](https://github.com/GOPHER-System-Intergration/kinova_positional_control.git).

The package includes a series of nodes, topics, and services that interact with the Kinova Gen3 robot's joint states and control commands.

## Installation

To install the package, clone the repository into your Catkin workspace:

1. Navigate to your Catkin workspace's `src` directory:

   ```
   cd ~/catkin_ws/src
   ```

2. Clone the repository:

   ```
   git clone https://github.com/GOPHER-System-Intergration/kinova_pid.git
   ```


3. Build the package:

   ```
   cd ~/catkin_ws
   catkin_make
   ```

4. Source the workspace:

   ```
   source ~/catkin_ws/devel/setup.bash
   ```

## Running the Package

To run the package, use the `arm_controller.launch` file:

```
roslaunch pid arm_controller.launch
```

This command will launch the necessary nodes, topics, and services for controlling the Kinova Gen3 robot's joints using the PID controller.