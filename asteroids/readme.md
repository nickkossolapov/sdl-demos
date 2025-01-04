# Asteroids

A classic Asteroids arcade game clone where the player controls a spaceship and must destroy asteroids by shooting them while avoiding collisions. The player can be controlled with either the keyboard or a controller.

## Demo

https://github.com/user-attachments/assets/c83fed73-4f5c-4cfa-bdf4-41da8fcafa5d

The video demo is also available [here](./demo.mp4).

## Features

**Player controls**: The ship can be rotated, thrusted, and fired using keyboard (arrow keys + space) or a controller (analog sticks + buttons).

**Asteroid destruction**: Asteroids break into smaller pieces when shot, with procedurally generated irregular shapes that spin as they move.

**Physics-based movement**: Uses Euler integration with a fixed timestep for consistent physics, including acceleration, angular velocity, and screen-edge wrapping.

**Score and lives**: Points are earned by destroying asteroids. The player has a limited number of lives with a brief invincibility period after taking damage.
