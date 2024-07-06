# MazeRace (Final Project for CIS 25)

Race against the clock to escape as many mazes as you can before time runs out. Challenge yourself to beat your own high score and see if you can rank among the top 3 players!

Gameplay:

Navigate through a series of randomly generated mazes.
Each time you find the exit, a new maze appears, and your map count increases.
You have 1 minute to escape as many mazes as possible.
Your final score is the number of mazes you successfully escape within the given time.

Features:

- Countdown Timer: Keep an eye on the countdown timer as it ticks down from 1 minute. The game ends when the timer reaches zero.
- Score Tracking: Your current score (map count) is displayed on the screen.

- Top 3 Scores: If your final score is among the top 3, it will be recorded and displayed on the leaderboard.

- Customizable: Change tile colors and background settings to personalize your gameplay experience. (TBD)

Controls:

- Use the arrow keys to move your player through the maze.
- Press `Enter` to start the game from the start screen.
- Press `S` to view the end screen and check your score.
- Press `Escape` to exit the game.


## Build
```bash
mkdir build
cd build
cmake ..
make
```

