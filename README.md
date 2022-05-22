# IN104

## Introduction
This is a project for IN104 in ENSTA Paris. We used reinforce learing to solve the maze in language C.

## MAKEFILE

We use Makefiles for all our projects to have a memorable way to install and run them.

## How it works?

## Example
Input file: <br>
    12,20  <br>
++++++++++++++++++++ <br>
    +                  +
    \+ + + ++++ + +++++ +
\+ + +++ ++ + ++ ++ +
\+ +   +    + ++    +
\+ +++ ++++++ +++++++
\+  s+     ++ +g+   +
\+ +++++++ ++ + + + +
\+ +       ++ +   + +
\++++++++++++ +++++ +
\+                  +
\++++++++++++++++++++

Output:
+ + + + + + + + + + + + + + + + + + + +
+ . . . . . . . . . . . .             +
+ . +   +   + + + +   + . + + + + +   +
+ . +   + + +   + +   + . + +   + +   +
+ . +       +         + . + +         +
+ . + + +   + + + + + + . + + + + + + +
+ . . . +           + + . + x + . . . +
+   + + + + + + +   + + . + . + . + . +
+   +               + + . + . . . + . +
+ + + + + + + + + + + + . + + + + + . +
+                       . . . . . . . +
+ + + + + + + + + + + + + + + + + + + +
