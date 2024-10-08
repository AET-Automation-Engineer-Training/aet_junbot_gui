# JunBotGUI

## TODO

   - [X] Refactor Code
   - [x] Ui for MainWindow, QLoginWidget
   - [x] Database Module
         
        - [x] User
         
        - [x] Delivery Target 
        
   - [x] Mission Module
   - [x] Robot State Module
   - [x] User permission
   - [ ] Total test

## Install QtMqtt

```
git clone git://code.qt.io/qt/qtmqtt.git
cd qtmqtt
git checkout <version of Qt> # version of Qt: v5.12.5
sudo apt-get install qtbase5-private-dev
qmake 
make 
sudo make install
```

## Config ROS plugin for QtCreator

1. Config workspace

- Install catkin_tools

```
sudo sh \
    -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" \
        > /etc/apt/sources.list.d/ros-latest.list'

wget http://packages.ros.org/ros.key -O - | sudo apt-key add -

sudo apt-get update

sudo apt-get install python3-catkin-tools

sudo apt-get install -y ros-noetic-move-base-msgs

sudo apt install libqt5svg5-dev
```

2. Run test with TurtleBot 3 simulation

2.1. Run Turtlebot 3 simulation

<b> Note </b>: You need to run SLAM before this step (if you do not have a map)

```
# Terminal 1: Simulation Node 
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_gazebo turtlebot3_world.launch

# Terminal 2: Navigation Node
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml
```

2.2. Run app

```
rosrun junbot_gui junbot_gui
```

## App detail

### Use case

![Fig.1](https://github.com/lacie-life/junbot_planner/blob/main/junbot_gui/doc/details.jpg?raw=true)

### Main Class

- <b> class AppModel </b> : App Manager 
    
- <b> class QNode </b> : Ros Interface
    
- <b> class QDatabaseManager, QUserDAO, QDeliveryTargetDAO </b> : SQLite Interface
    
- <b> UI Classes </b> : QRobotItem, MainWindow, QLoginWidget, QCustomWidget

- <b> Object Classes </b> : QUser, QRobotMission, QDeliveryTarget

- <b> Other Classes </b> : AppConstants, QRobotMission, QRobotUtils
    

