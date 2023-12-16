# Snake Game in C

This is a simple implementation of the Snake game in C using the ncurses library. It provides a rectangular play area where you can control a snake that... / bla bla bla / we all know the famous Snake Game 😉 <br>
- So here is how to Compile and Run (pretend you don't and follow instructions):

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
