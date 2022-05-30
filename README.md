# Hybrid Robot
This project has the tools to work on a balancing robot.

It has a simple simulation world and the tools to control the prototype robot.

## Prerequisites
The whole project is though and designed to be used with ROS, it also uses Eigen3.4 to
run the controller and Gazebo for the simulation.
* [ROS](https://www.ros.org/)
* [Eigen3.4](https://gitlab.com/libeigen/eigen/-/releases/3.4.0)
* [Gazebo](https://classic.gazebosim.org/tutorials?tut=guided_i5)
* Setup a [Catkin](http://wiki.ros.org/catkin) environment.

It is important to at least install the velocity controllers for ROS to be able to use
the package.
```sh
# Install all the controllers for the ROS-noetic version
sudo apt install ros-noetic-controller*
```

## Used hardware
The hardware used on this project is the following:
* **Nema 17 stepper motor**: the motors that power the Hybrid Robot.
* **UstepperS**: the control board for the stepper motor.
* **MG90s servo**: the servo that controls the brakes.
* **Raspberry Pi 4 (RPI)**: the onboard computer that controls everything.
* **Arduino UNO**: the board that controls the servos.
* **GY-91**: the IMU used.

## Usage
To be able to use it, it is important to have built the catkin environment.
```sh
cd /path/to/catkin/workspace

# ROS noetic
catkin_make
```
### Simulation
To simulate the robot, it is just a matter of running the launch file: 
```shell
roslaunch hybrid_robot hybrid_robot.launch
```
It can be changed the nodes to run and run other nodes individually through the
terminal or any other IDE.

The needed nodes to run the simulation are:
* The **Vel_node** as it has a way to control the wheels when it receives a message on the topic "_/HJC/Vel_robot/Set_velocity_".
* The **IMU_node** which will provide the needed information from the simulated IMU.
* The controller that it is needed.

### Real world
To be able to run the prototype it is needed to upload the following scripts into the robot:
* **IMU_robot-1.py** into the RPI.
* **mpu9250.py** into the RPI (it is needed for the IMU).
* **registers.py** into the RPI (it is needed for the IMU).
* **wheel_robot.py** into the RPI.
* **wheel_HC_new.ino** into both UstepperS.
* **breakmodeteensy.ino** into the Arduino UNO.