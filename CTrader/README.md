<<<<<<< HEAD
# CMaze
=======
# IN104

## Introduction
This is a project for IN104 in ENSTA Paris. We used reinforce learing to solve the maze in language C.

## MAKEFILE

We use Makefiles for our project to have a memorable way to install and run the codes.

## How it works?
In termial command line, type down: <br>
### `make`
### `./prog`

## Example
Input file: <br>

		12,20  
		++++++++++++++++++++ 
		+                  +
		+ + + ++++ + +++++ +
		+ + +++ ++ + ++ ++ +
		+ +   +    + ++    +
		+ +++ ++++++ +++++++
		+  s+     ++ +g+   +
		+ +++++++ ++ + + + +
		+ +       ++ +   + +
		++++++++++++ +++++ +
		+                  +
		++++++++++++++++++++

Output:

		+ + + + + + + + + + + + + + + + + + + +
		+ . . . . . . . . . . . .             +
		+ . +   +   + + + +   + . + + + + +   +
		+ . +   + + +   + +   + . + +   + +   +
		+ . +       +         + . + +         +
		+ . + + +   + + + + + + . + + + + + + +
		+ . . s +           + + . + g + . . . +
		+   + + + + + + +   + + . + . + . + . +
		+   +               + + . + . . . + . +
		+ + + + + + + + + + + + . + + + + + . +
		+                       . . . . . . . +
		+ + + + + + + + + + + + + + + + + + + +
>>>>>>> main
