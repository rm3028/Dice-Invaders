# Dice-Invaders
* Project name: Dice Invaders
* Description: Dice Invaders consists of four different objects: the player ship, the aliens, the aliens’ bombs and the player’s rockets. The goal of the game is to shoot as many aliens as possible without being hit by them or their bombs.
  * The player ship
  The player ship is positioned at the bottom of the screen. It can only move horizontally. It can fire rockets at the aliens. The ship can take three hits from aliens or their bombs before it is destroyed and the game is over.
  * The rockets
  The rockets travel straight up. If they hit an alien, the alien and the rocket are destroyed, and the player’s score is increased. Rockets cannot destroy bombs. When the rocket reaches the top of the screen, it disappears.
  * The aliens
  The aliens start out at the top left corner of the screen, organized in rows and columns. They move slowly to the right, until the rightmost alien reaches the border of the screen. Then, they all take one step down, and start travel to the left instead. If the alien collides with the player, the alien is destroyed and the player’s health is decreased. The aliens drop bombs randomly.
  * The bombs
  The bombs travel straight down. If they hit the player, the player’s health is decreased and the bomb is destroyed. When a bomb reaches the bottom of the screen, it disappears. The bombs don’t hurt other aliens.
  * The end of the game
  If the player is hit three times by aliens or their bombs, or an alien reaches the bottom of the screen, the player loses and the game is over. If the player kills all aliens, a new alien army should be created at the top of the screen.
* Environment:
  * IDE: Visual Studio 2019
  * Platform Toolset: Visual Studio 2019 (v142)
  * Windows SDK: 10.0.18362.0
* Author: Wei-Yun
* Email: rm3028@hotmail.com.tw
* Copyright © 2017 Wei-Yun
* All rights reserved.
* Demo: 
  ![image](https://github.com/rm3028/Dice-Invaders/blob/master/Dice-Invaders-Demo.PNG)
