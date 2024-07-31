# Particles

This project is a simple 2D particle simulator built in C++. It simulates the movement and collision of particles
falling through the screen, including interactions with obstacles and borders.

## Demo

The video demo is also available [here](./demo.mp4).

## Features

**Particle simulation**: Simulates the movement of particles with basic physics, including gravity.

**Collision Detection**: Detects and handles collisions between particles, obstacles, and boundaries, including a basic
approach for handling multi-body collisions using mass
splitting ([L136 in simulation.cpp](./src/entities/simulation.cpp)).

**Constant step times**: Ensures that a target physics step size is used by using time accumulator and performing
multiple
simulation steps if necessary ([L32 in simulation.cpp](./src/entities/simulation.cpp)). This has the downside that if a
simulation time + rendering time is greater than the specific simulation step (5 ms), the rendering will slow to wait
for the physics to complete.

## Areas to work on

**Improved rest detection**: Often when the particle is resting on an obstacle it will jitter up and down.

**Better circle rendering**: Right now the circles aren't using antialiasing when rendering, so the look smaller than
they are the simulation. This creates visible gaps between the particles and obstacles.
