# Particles

This project is a simple 2D particle simulator built in C++. It simulates the movement and collision of particles falling through the screen, including interactions with obstacles and borders.

## Demo

https://github.com/user-attachments/assets/a33e5226-51fd-4560-a51a-dbf01eb7a8c2

The video demo is also available [here](./demo.mp4).

## Features

**Particle simulation**: Simulates the movement of particles with basic physics, including gravity.

**Collision Detection**: Detects and handles collisions between the particles and obstacles or boundaries, including a basic approach for handling multi-body collisions using mass splitting ([L136 in simulation.cpp](./src/entities/simulation.cpp)). This doesn't include collision between particles.

**Constant step times**: Ensures that a target physics step size is used by using time accumulator and performing multiple simulation steps if necessary ([L32 in simulation.cpp](./src/entities/simulation.cpp)). This has the downside that if a simulation time + rendering time is greater than the specific simulation step (5 ms), the rendering will slow to wait for the physics to complete.

## Areas to work on

**Improved rest detection**: Often when the particle is resting on an obstacle it will jitter up and down. Visible in the demo with particles resting on top of the obstacles nearest the centre of the screen.

**Better circle rendering**: Right now the circles aren't using antialiasing when rendering, so the look smaller than they are the simulation. This creates visible gaps between the particles and obstacles.
