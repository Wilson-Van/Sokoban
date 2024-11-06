# Project: Sokoban in C++

# Contact:
Name: Wilson Van

## Description:
This was a project in my computing 4 class at UMass Lowell where I used the SFML to create a window and generate a game of Sokoban based of a txt file. This project was split into two parts the first of which was to create the window and create the layout of the game based on a txt file passed as a parameter of the main function. Using textures made by Kenny Vleugels I would space place the textures on the window such that there were no gaps between the images which were generated from the txt file. The txt file would consist of 'A', 'a', '@', '#' and '.' characters which would correspond to the texture of a given space of the window (a box when there was an 'A', a storage/goal spot where there is an 'a', a player where there was a '@', a wall where there was a '#' and a ground where there was a '.'). In the second part of the assignment took the layout of the game and added functionality. The way I implemented the game allowed the player to use the arrow keys or "WASD" to move the character around the spaces. If the player met a "wall" space that would stop their movement. If the player moved into a "box" space the box would also move in the direction of the player's movement unless their was a "wall" space in the way or there was no space to push the "box" (Off the window) in that case neither the player nor the "box" was able to move. The goal of the game was to place the "box" spaces into the "storage" spaces. In this case the game would be over and a game over screen would pop up.
