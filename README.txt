EX3: "Pick Up Sticks"

Names:
Nicole Kazantsev 208258095
Herut Partner 205741333

General explanation of the program:
The purpose of the exercise is to use STL-style data structures, iterators and algorithms and refresh the use of SFML.
The rules of the game are very simple: 
the player is shown a board on which colored sticks are scattered and he must pick them up.
The player can lift a stick only if there are no other stick above it. 
If the player tries to pick up a stick that should not be picked up, the action will not be done.
The game is limited in time that we chosen.
The game ends when the board is empty or when the time is up.
Each stick entitles the player to a different number of points - depends in color.
The number of sticks on the board is randomly drawn from a range.
Scattering sticks at the beginning of a game is done randomly. 
For each stick, we will write values ​​for a starting point, length, angle in it we will rotate it and paint. 
When the player clicks on a stick that can be picked up, the stick will disappear. 
When the player clicks on a stick that is not given pick up, there will be an indication why this stick cannot be picked up.
The indication is flickering the blocking sticks in black color for a short time.
The following data will be displayed on the board:
● How much time is left
● How many sticks are left
● How many sticks have been lifted
● How many sticks can be picked up at the moment
There will be a hint button. This button helps the player find the sticks that can be picked up. 
When the player clicks on this button, sticks that can currently be picked up will flash similar to the indication when a stick cannot be picked up. 
The order of coloring is according to the number of points of each stick. 
Stick with the highest score will color first and stick with the lowest scorewill paint last. 
The game has a start screen with basic menu that containes the options of starting game, continue and exit.
At the end of thr game we will present an end screen that will show the result of the game.
  
Classes we created and the relationship between them:
(For each class there is a header file and a cpp file)
GameControll - a class that responsible for the course of the game.
Board - a class for the board on which the colored sticks are scattered .
Menu - a class for the game menu(the first window).
Resources - a class for all the textures in the game.
Stick - a class for the sticks in the game.
ToolBar - a class for the data that displayed on the board.

Main data structures and their functions:
Vector for saving all the sticks on the board.
Vector for saving the free sticks (by serial number).
For the sticks we used a rectangle shape from the SFML library.

Noteworthy algorithms -
Algorithm for checking whether two segments(sticks) intersect:
Manual implementation of the separation axis principle (Separation Axis Theorem - SAT), 
which is used to locate overlap between rectangles, in a two-dimensional space.
The function uses tools from the SFML library:
SFML's sf::RectangleShape for the rectangular shapes.
SFML's (sf::Transform) to calculate the global vertices of the rectangles.
The function isOverlaped checks if two sticks (or any two rectangular shapes) overlap using SAT.
How the function works:
1. it calculates the four vertices (corners) of each of the rectangles with the help of an internal function called 
   getVertices, which returns the transformed vertices according to the position and rotation of each rectangle.
2. It creates a vector of axes, which are the directions along the sides of the two rectangles.
3. For each axis, it projects the vertices of the two rectangles onto that axis, and finds the minimum and maximum of 
   the projection for each rectangle.
4. If there is an axis where there is no overlap between the projections of the two rectangles, 
   it returns false - that is, there is no overlap between the sticks.
5. If there is no axis that separates the projections, it returns true - that is, 
   there is an overlap between the sticks.

Known bugs - the save button not working
Other notes -