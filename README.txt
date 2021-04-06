-> Objective:
   The program is designed to simulate the working of an airport with three runways with the following conditions:
1. Runway 1 can only be used for landings.
2. Runway 2 can only be used for take offs.
3. Runway 3 can be used for landings, and susequently for take-offs if and only if landing queue is empty.
4. Planes can be ready to land or take off at any random unit of time.
   
The program has been written using C language.
It consists of a client file client.c, a server file server.c, a header file head.h, and a makefile makefile.mk
The program has used random function to ensure randomness in generation of planes.
The program uses linked lists to generate queues for landing and take-offs respectively.
Arrays have been used to ensure poisson's distribution.

-> Procedure for execution:
1. Open command prompt
2. Ensure gcc has been installed
3. Go to the respective directory via command prompt where the files have been saved
4. Type mingw32-make -f makefile.mk and press enter
5. Type a/a.out and press enter

-> Inputs:
   The program will require user input to decide the following:
1. Total units of time that the simulation should run for.
2. Maximum number of planes that can be queued for landing and take off respectively.
3. Average rate of landing and take-off expected.
   Since there are three runways, a total rate exceeding 3.00 is considered as a high activity rate and beyond 4.00 is considered saturated.
Note:
Valid inputs -
Time > 0 (positive integer)
Maximum number of planes in queue > 0 (positive integer)
Average expected activity rate > 0 and < 2 (decimal number, preferably < 1.5) 
Invalid inputs -
Time < 0
Maximum number of planes in queue < 0
Average expected activity rate < 0 or > 2
The program is designed to handle such invalid inputs and allows the user to re-enter the values.
Do not enter floating point numbers for time or maximum planes in queue.

-> Output:
1:
Plane 1 is ready to land
Plane 2 is ready to land
Plane 3 is ready to land
Plane 4 is ready to take-off
Runway 1: Plane 1 has landed
Runway 2: Plane 4 has taken off
Runway 3: Plane 2 has landed
2:
Plane 5 is ready to take off
Runway 1: Plane 3 has landed
Runway 2: Plane 5 has taken off
Runway 3 idle: Both queues empty

...and so on

End statistics:
Total number of planes: s
Number of planes arrived: m
Number of planes ready to depart: r
Number of planes successfully landed: u
Number of planes successfully taken-off: t
Number of planes redirected before landing: h
Number of planes cancelled from take-off: i
Number of planes still in landing queue: g 
Number of planes still in take-off queue: o
 

   
