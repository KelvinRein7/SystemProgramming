Name: Khun Thu Rein

Student ID: 101186023

Program Description
-------------------
In this assignment, the program will track the estimated likelihood of the kinds of ghosts and
will let the user choose the option on what data they want to see. For example, user can choose
to see the room data, the kind of ghosts they want to see and even a sorted version (sorted by
likelihood) of ghost data.

List of Files
-------------
1. building.c
2. def.h
3. ghost.c
4. main.c
5. room.c
6. README.txt

How to run the program
----------------------
1. Open the terminal
2. Go to the directory of the folder
3. gcc main.c room.c ghost.c building.c -o main -Wall
4. ./main

To check memory leak
--------------------
1. valgrind --leak-check=yes -s ./main
(-s is used to see more details)