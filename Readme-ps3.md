# PS3b: Sokoban

## Contact
Name: Wilson Van
Section: 202
Time to Complete: 6 hrs


## Description
Explain what the project does.

In part b of this project we gave the Sokoban Game functionality so that the character can move and push boxes according to the rules described in the pdf.

### Features
Describe what your major decisions were and why you did things that way.

I decided that the original state the game was in should be stored so that when to track what spaces were storages and what should be storages if there was already a box over the storage in the beginning state. It also helped when creating the reset function.

### Memory
I decided to store the level data as an array.

### Lambdas
I used std::count to count how many boxes and storages were in the level to begin with and then I used the min function to figure out how many storages were supposed to be filled in order to win the game.

### Issues
I wasn't sure about the autograder checking my test. I didn't know if I was just testing incorrectly or if the auto grader wanted me to create a test of a certain name or functionality.

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
Win Screen: https://www.deviantart.com/chillyboombox2/art/You-Win-Screen-748805655

## Other Notes
The win_screen.png is the sprite I used to create the win screen when you win every other png file is outputs of my code while it is running and after certain events have happened during level 1.
