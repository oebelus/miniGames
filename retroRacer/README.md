# Retro Racer
This is an ASCII art-based car racing game created in C using the ncurses library. 
The game features a car controlled by a player, and enemy cars that moves down the screen. 
The player's objective is to avoid collisions with the enemy car.

## How to play
Compile the game:
```
gcc cars.c -o cars -lncurses
```
Run the game:
```
./cars
```
- Use the arrow keys to control your car (up-down-left-right) and avoid collisions with the enemy car(s). <br>
- The score increases by 10 points each time the enemy car passes through the bottom of the screen, and by 20 points once the score reaches 20.<br>
- When the score reaches 20, a second enemy car joins the game.
- The game ends when you collide with the enemy car with a score equal to 0, or with the edges of the roads.
## Screenshots
<p float="left">
  <img src="https://github.com/xertendsz/retro-racer/blob/main/image/race.png" width="33%" />
  <img src="https://github.com/xertendsz/retro-racer/blob/main/image/gameover.png" width="66%" />
</p>







