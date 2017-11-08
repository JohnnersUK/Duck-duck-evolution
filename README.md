# Snake
Classic 2D game for LLP

## build instructions
Nothing fancy, just open the project in vs(2017) and run
Alternatively, navigate to the builds/debug(x86) and launch snake.exe

## gameplay
Arrow keys to move/navigate menu's
enter to select
esc to pause

The game also supports xbox controllers
D-pad to move
Face buttons to select
Start to pause

## design decisions
The original snake game eventually comes to a conclusion when the player has filled the screen with their snake, I wanted to change this.

Changing the theme from snake to ducks, i've added an area in which the player can save it's trail of ducklings for extra points. This allows the player to continue the game virtually forever as long as they are skilled enough. This means that there is no set score for 'winning' and players can compete with eachother to gain high scores beyond what was possible in the original snake.

With each pickup colected, the snake gets faster and faster making the game harder to control. When the player saves their trail, the game speed resets. However, the longer the trail the player saves the more points, exponentialy, they gain.
This adds a risk/reward element to my game as better players will want to hold off on saving their trail for as long as possible, in order to maximise their score, making the game harder for themselves.

