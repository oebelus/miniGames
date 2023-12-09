# Snake Game in C

This is a simple implementation of the classic Snake game in C using the ncurses library for terminal-based graphics. The game provides a rectangular play area where the player controls a snake that moves around to eat fruits and grow longer. The objective is to eat as many fruits as possible without colliding with the boundaries or the snake's own body.
How to Compile and Run

To compile the game, make sure you have the gcc compiler and the ncurses library installed. You can compile the game using the following command:

```
gcc snake.c -o snake -lncurses
```
After compiling, you can run the game with:

```
./snake
```
## Controls

-  Use the arrow keys to control the direction of the snake (Up, Down, Left, Right).
-  Press 'x' to exit the game.

## Gameplay

- The snake starts at the center of the play area.
- The snake grows longer by 1 unit each time it eats a fruit.
- Eating a fruit increases the player's score by 10 points.
- The score is decremented by 10 if the snake collides with the boundaries of the play area or its own body.

## Code Overview

The code is structured into several functions:

- shifter: Shifts the elements of an array to simulate the snake's movement.
- position: Initializes game variables and positions the snake and fruit.
- boundary: Draws the game's play area, snake, and fruit using ncurses.
- keyboard: Handles keyboard input to change the snake's direction or exit the game.
- game: Updates the game state, including moving the snake and checking for collisions.
- main: The main game loop, where the game logic is executed repeatedly.
