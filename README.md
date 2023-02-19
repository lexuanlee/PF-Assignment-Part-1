# PF-Assignment-Part-1

# Alien vs. Zombie

*radio intercom*
Captain Al: Dear Aliens of planet Ali3n, Zombies from planet Waking D3AD
            are invading Planet Ali3n in 5 minutes. Calling for all heroes
            out there to regain back our peace and STOP THE ZOMBIES. 
            PREPARE FOR WAR! ALL HAIL KING E.T.!!!

The game is a type of board game where you, as an alien is tasked to defeat all the zombies. Alien would move up, down, left and right with the help of arrows to direct and kill the zombies. Once all zombies are defeated, Alien Wins!

https://youtu.be/5vXGo0El1T8

## Compilation Instructions
1. Download all the files in a folder, open the folder in vsc and then 

for part 1:
```
g++ main.cpp -o main
```

for part 2
```
g++ mainpart2.cpp -o main
```

2. Then in the file will appear an application, you can choose to run in:

   -  Cmd by clicking the file
   
   - ./main in vsc




# User Manual

## How to play

When the user starts the game, it will show the default settings for rows, columns and the number of zombies. If the user wishes to edit the game setting, he can enter the number of rows, columns and zombies that he wants. After that, a game board with the input entered by the user will be displayed. The game objects are randomized and located on the game board as well. Then, the user will see the character info of alien and zombies. There is a “command” word below the character info, user can start playing the game by entering the user command:

## List of user commands:

1.  up - Alien moves up.
2.  down - Alien moves down.
3.  left - Alien moves left.
4.  right - Alien moves right.
5.  arrow - Change the direction of an arrow.
6.  help - Display user commands.
7.  new - Generates new board.
8.  save - Save the game.
9. load - Load a game.
10. quit - Quit the game.

## Alien Movement:

After the user enters the command, Alien will follow the command and move in the game board. Alien will move continuously in the same direction until it encounters objects such as boundary of the game board, rock objects, and when it attacks zombie. The Alien will leave a dotted trail along the way it moves, the dotted trail indicates that the path has been passed by the Alien. Once it stops, the dotted trail will reset. If the alien has encountered an arrow, it will change the direction of its movement. Below shows the descriptions of game objects available on the game board that will change the Alien behavior:

## Game Objects:

Arrow (^ v < >)
-Changes the direction of movement of alien such as upward or downward,left or right

Health (h)
-Adds 20 life to alien if the alien’s life is not full.

Pod (p)
-Instantly inflicts 10 damage to Zombie when Alien encounters it.

Rock (r)
-Reveals randomised game objects beneath it when encountered by the alien

Poison (o)
-Instantly inflicts 10 damage to Alien Life when Alien encounters it.

Empty
-Empty space on the board

Trail (.)
-Left by Alien when it moves 

-Being reset when the Alien stops and its turn ends.

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)


## Contributors

Teoh Ren Nee

Lee Le Xuan

Jackter Un Chia Te




