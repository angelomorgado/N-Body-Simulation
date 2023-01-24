#  N-Body Simulation
#  ================
## Made by:
Ângelo Morgado   - [github](https://github.com/angelomorgado)

Henrique Jesus   - [github](https://github.com/Henistein)

Manuel Magalhães - [github](https://github.com/manuelM123)

## Introduction

This projects aims to simulate the movement of a group of bodies in space. In order to do that an highly costumizable particle system was conceived. This project was made using C++ and OpenGL.

---

## Requirements

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [Assimp](https://www.assimp.org/)
- [GLM](https://glm.g-truc.net/0.9.9/index.html)
- [GLEW](http://glew.sourceforge.net/)

### Windows

In order to run the program in Windows you need to install the g++ compiler. This project was made using the MinGW compiler. The preferred way to run the program is to use the visual studio code IDE. The instalation tutorial can be found in [this link](https://code.visualstudio.com/docs/cpp/config-mingw).

### Linux

In order to run the program in Linux you need to install the g++ compiler. To install the dependencies run the following commands:
 - sudo apt-get install libglfw3
 - sudo apt-get install assimp-utils

---

## How to run

### Windows

To run the program in Windows you need to open the project in visual studio code and press the run button. The program will be compiled and run due to the *tasks.json* file. Alternatively you can also compile it in the command line. To run it simply open the the Main.exe file or any executables already compiled for windows.

### Linux

To run the program in Linux you need to open the terminal in the project folder and use the makefile. To compile the program run the following command:
 - make

To run the program run the following command:
- ./Main

---

## Movement

To give more freedom to the user, the camera can be moved using the following keys:

- `W` : Move forward
- `S` : Move backward
- `A` : Move left
- `D` : Move right
- `Space` : Move up (In the direction of the up vector)
- `C` : Move down (In the direction of the up vector)
- `Scroll Up` : Zoom in
- `Scroll Down` : Zoom out
- `P` : Check the vertices of the world

---

## Scenarios

To properly visualize the simulation we created 6 scenarios. Each scenario tries to identify a different aspect of the n body simulation and its uses. 

To change the scenario you need to change the value of the scenario variable in the *Main.cpp* file.

The scenarios are:

### 1 - Physics Simulation

This scenario aims to simulate the real interaction between celestial bodies in space. To do that, each particle will interact with the other particles in the system. The interaction is based on the gravitational force. There are 3 types of particles: red(heavy), yellow(medium), white(light); this was done to check how mass will impact the simulation.

In order to improve the simulation input was included:
- `Right Arrow` : Increase the mass of the particles
- `Left Arrow` : Decrease the mass of the particles
- `Up Arrow` : Increase the force between the particles
- `Down Arrow` : Decrease the force between the particles

![](Gifs/Physics.gif)

### 2 - Simple Black Hole

This scenario aims to simulate the interaction between a black hole and a group of particles. The black hole is represented by a custom kirby object. The force between the particles and the black hole is based on the gravitational force. The particles have different masses.

![](Gifs/Simple_BH.gif)

### 3 - Complex Black Hole

Like the previous scenario, however there are two black holes in the system and they are moving. To improve the simulation, input was included:

- `Left Arrow` : Only the first black hole will exert a force on the particles
- `Right Arrow` : Only the second black hole will exert a force on the particles
- `Up Arrow` : Default mode, both black holes will exert a force on the particles
- `Down Arrow` : Increase the force between the particles and the black holes

![](Gifs/Complex_BH.gif)

### 4 - Big Bang

This scenario aims to simulate the big bang. To do that, the particles are created in a random position and with a random velocity. The particles are created in a sphere with a radius of 100 units. The particles have different masses. They are then pulled into the center for 5 seconds, and then they are released using an explosion force.

![](Gifs/Big_Bang.gif)

### 5 - Spiral

This scenario aims to simulate the movement of a group of particles in a spiral. To make it more interesting, the color of the particles are also changing using the sin and cos functions; this gives the illusion that the colors never change.

![](Gifs/Spiral.gif)

### 6 - Point Cloud

This scenario tries to create point clouds using the particles. Firstly a file containing the positions and colors for each vertex is read. Then the particles are moved into the correct position. The available point clouds and their input are:

- `B` : Boat
- `R` : Rose
- `H` : Sphere

![](Gifs/Point_Cloud.gif)