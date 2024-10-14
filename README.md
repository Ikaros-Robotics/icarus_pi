# Icarus 🪽

Icarus is an open-source project that students or hobbyists can use as a base to gain experience with ROS2, SLAM, and Nav2. It is also a way for us to share our love of robotics! 

Icarus is a four-wheeled, mecanum-drive robot capable of manual and autonomous navigation. This is the project's main repository and contains all of the information and code to create the physical robot. Our sub-repo ([Icarus Jetson Nano Repository](https://github.com/Ikaros-Robotics/icarus_nano)) contains all of the information required to add autonomous navigation to the robot and can be used without recreating Icarus.

<br />

![Icarus Video](/docs/Icarus_Video.gif "Video of Icarus Operating Autonomously")

<br />
<br />

# Initial Run

>[Install the pigpio library](https://abyz.me.uk/rpi/pigpio/download.html)

>To install all of the required dependencies from the package.xml run:

    rosdep update --include-eol-distros    
<br />

    rosdep install --from-paths src -y --ignore-src --rosdistro foxy

<br />
<br />

# To Launch Icarus

>On startup, launch the PiGPIO Daemon using:

    sudo pigpiod

>Launch the robot!

    ros2 launch icarus_pi launch_robot.launch.py 

<br />
<br />

# To Launch Icarus in Simulation

>With Planar Controller:

    ros2 launch icarus_pi launch_sim_planar.launch.py 

>With Mecanum Controller:

    ros2 launch icarus_pi launch_sim_mecanum.launch.py 

<br />
<br />

# Materials List

Some of our core components include:

- Jetson Nano
- Raspberry Pi 4
- Motors with Quadrature Encoders
- Motor Controllers (L298N)
- 2-D LiDAR
- Raspberry Pi Camera V2
- Mecanum Wheels

<br />

A full list of our materials can be found on our [Materials List ](/docs/Materials%20List.pdf).

<br />
<br />

# Software

The Software for the Icarus Project is split between two devices, which requires having two different Ros2 workspaces.  The Raspberry Pi uses the Icarus_pi workspace in this repo, which contains the three main custom ROS2 packages: icarus_interface, icarus_pi, and mech_drive_controller.  Icarus_pi is the starting point for Icarus architecture and contains the robot description, launch files, and robot configuration files.  Except for PID tuning, all unique robot intrinsics are stored here and can be modified to fit different setups.  Icarus_interface is the Ros2 interface to the motor and encoders.  It leverages the PiGPIOd library to control GPIO signals on the Raspberry Pi, and will perform PID control when the interface is written to.  Finally, the mech_drive_controller is a custom ROS2 controller which allows two linear and one rotational movements.  These three packages work in tandem to manage all movement of the Icarus Robot and can run independent of icarus_nano. Icarus_nano contains three main ROS2 packages: autonomy, rplidar_ros, and camera_publisher. The autonomy package extends the slam_toolbox and Nav2 packages to enable support for holonmonic drive roborts. The rplidar_ros is cloned from the official Slamtec repository, (linked in the References section), and takes data from the physical LiDAR and translates it into a laser scan topic. The camera_publisher topic takes in information from our camera stream and publishes it so that we can see what the robot sees through RVIZ. 

![Icarus Software Diagram](/docs/Icarus_Software_Diagram.png "Icarus Software Design")

<br />
<br />

# Mechanical

The design of this robot was inspired by the turtlebot-burger educational platform. This design allows for a high degree of flexibility in the placement of components. Additionally, due to the modular design philosophy here, its possible to add, remove, or swap out new parts and sensors as you see fit. If desired, you can create your own custom fixtures and components to mount onto your robot as you see fit.
The mounting holes on the base plates have an initial diameter of 4.5mm in order for m3 flathead screws to sit flush within the plate, and then we have a 3.5mm diameter hole that's also designed for m3 screws; with a center-to-center distance of 20mm between each hole.
for a more vibration-resistant fit, add in threaded brass inserts to your mounting components by melting them in via soldering iron.

<br />

#### Mechanical Assembly

![Icarus Mechanical Design](/docs/Mechanical/Mechanical%20Assembly.png "Icarus Mechanical Design")

<br />

A more in-depth description of our mechanical design, as well as our STL files, can be found in our [Mechanical Documentation](/docs/Mechanical/Mechanical%20README.md).

<br />
<br />

# Electrical

Our electrical design was formulated around the core components that we wanted to use. These core components are listed above in the Material List section. We wanted to be able to operate the robot for a good amount of time before we needed to swap out or charge the batteries so that we could work on the project or test things for hours at a time. Because of this, and the fact that we used 12V motors, we opted for 
two 11.1 V, 5000 milli-amp hour batteries, one to power the motors, and one to power the rest of our electronics. We decided to solder as many of the components as we could for durability. The motors used jumper cable connections and since these could not be soldered easily, we decided to secure the connections with a layer of kapton tape. Our electrical diagram below shows how all of our components interact with each other.

<br />

#### Electrical Diagram

![Icarus Electrical Diagram](/docs/Electrical/Icarus%20Electrical%20Diagram.png "Icarus Electrical Diagram")

<br />

A more in-depth description of our electrical design, as well as our [electrical schematic](docs/Electrical/Icarus%20Electrical%20Schematic.pdf) and [pinout descriptions](/docs/Electrical/Motor%20Connections%20Table.pdf), can be found in our [Electrical Documentation](/docs/Electrical/Electrical%20README.md).

<br />
<br />

# Mecanum Wheels

The Icarus Robot was created with the goal of controlling four Mecanum wheels.  Mecanum wheels that contain a circular array of smaller angled wheels.  This wheel arrangement allows movement in both the x and y linear directions, while still allowing a yaw rotation.  This also allows the robot to diagonally strafe or rotate while moving based on precise control of wheel speed and direction.  This required creating a custom controller package based on Ros2 control diff drive to allow the additional degree of movement.

<br />

#### Mecanum Wheel Kinematic Model

![Mecanum Wheel Kinematic Model](docs/Mecanum%20wheel%20Kinematic%20Model.png "Mecanum Wheel Kinematic Model")


#### Mecanum Wheel CAD Model

![Mecanum Wheel CAD Model](docs/Mecanum%20Wheel%20CAD%20Model.png "Mecanum Wheel CAD Model")

<br />

A more in-depth description of the various software challenges we faced with mecanum wheels can be found in our [Mecanum Wheel Documentation](/docs/Mecanum%20Wheel%20README.md).

<br />
<br />

# Lessons Learned & Future Improvements

Overall, we are quite happy with how Icarus turned out! However, looking back on our implementation, there are some things we would have done differently to achieve similar results while making our lives a little easier in the process. Some items that would have provided some relief to our major pain points include a more modular mechanical design, specifically for our component mounts, a simplified electrical design, and a change in the microcontrollers used. Addressing these issues would have allowed us to better utilize our time spent on Icarus. Below, we have detailed more improvements we would make in our 3 major categories: software, electrical, and mechanical. 

<br />

### Software

Our software design went through many iterations and required countless hours of discussion and design to get to our final product.  We learned three main lessons throughout the project's timeline when it came to our software process.  First, we should have filled out and shored up the project's foundational code before adding more software layers.  Debugging Nav2 and controller issues took significantly longer due to errors in our robot description and odometry calculation.  These could have been caught earlier and saved time later in the project if they had been a step at a time instead of simultaneously with the higher level software.  More early development in simulation would have been one way to catch these early issues.  The next lesson learned was that the group could have been more careful when researching embedded software version limits before progressing too far into setup.  The Jetson Nano cannot run Foxy or Humble natively, and Xubuntu on the Jetson Nano could only run up to Foxy.  This caused a version mismatch between some of our devices and the embedded system that led to errors later in the development cycle.  Finally, establish a common workflow for group members.  Our personal devices were setup independently, which caused members to not have the same tools or organization.  More communication on this area of the project would have made certain areas of our workflow run smoother.

-Be extra careful when reading hardware documentation.  Our LiDAR was mounted backwards, and caused the robot to move in unexpected directions.

<br />

### Electrical

The thing that we would like to improve upon in the future would be to simplify our electrical design. Our design greatly exceeds what was needed for the project, in terms of things like processing power and battery life. This is beneficial because we could easily integrate more features or sensors into the base design without worrying too much about power considerations or having to swap out the batteries too often. However, this also made the design take longer to assemble, which was detrimental to our objectives since we wanted to focus more on the software side of this project.

The switches were a nice addition, however, they could be removed to simplify the power and ground connections. Since the battery connectors are easily accessible, the system can be quickly de-energized without switches by simply disconnecting the connectors. There were also a couple of instances where wires had to be spliced 3 or more times. Creating these splices took us a little longer than initially expected, so using terminal blocks for connections instead of solder could make the assembly process quicker. Smaller milli-amp hour batteries could also be used to save on cost.

The biggest electrical change we would make would be to switch out our microcontrollers. Having the processing power of the Raspberry Pi and the Jetson Nano was nice, however, we could have accomplished everything we did with an Arduino and either a Raspberry Pi or Jetson Nano. The Arduino would control our motors and the rest of the processing would be offloaded onto the other microcontroller.

<br />

### Mechanical

It was never a wise decision to design something with the idea that we would never move the component from its position, or that it would need to be removed from its mounting area. Always design with ease of assembly and disassembly in mind

Make use of not only the horizontal space available on a given surface. If it's more convenient for assembly, create designs that take advantage of the vertical space given,
i.e.: mounting this vertically, upside down, stacked, etc.
<br />
<br />

# References

- [ROS2 Foxy Official Documentation](https://docs.ros.org/en/foxy/index.html)
- [The PiGPIO Library](https://abyz.me.uk/rpi/pigpio/index.html)
- [Articulated Robotics - Build a Mobile Robot with ROS](https://articulatedrobotics.xyz/tutorials/mobile-robot/project-overview)
- [ECAM Eurobot - Mecanum Wheels](https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html)
- [Turtlebot3](https://www.turtlebot.com/turtlebot3/)
