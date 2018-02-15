
The input of the program is a txt file, followed by GA for genetic algorithm or HC for Hill Climbing algorithm.

The output of the program is to print out the following information: 1)Type of Algorithm used, 2) Time consumed, 3)Number of iterations, 4) Final map, 5) Resulting Score

In order to make the program, once you are in the same directory with all the files type in the linux terminal:

linux> make

Then you are ready to run the program.

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@ Example Input for genetic algorithm: @@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



linux> ./urbanplanning example.txt GA




@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@ Example Output for genetic algorithm: @@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


nikolaos@nikolaos-Inspiron-7548:~/Desktop/CS534/Urban_Planning/Urban_Planning$ ./urbanplanning  sample3.txt GA

Calculating the best configuration. Please wait .............

Simulation finished after 10033 ms **********************************

S T A T I S T I C S   O F   T H E   S I M U L A T I O N:

  Algorithm: Genetic Algorithm
  Selection Method: TOURNAMENT
  Crossover Method: RANDOM
  Population:128
  %Elitism: 10% 	 %Mutations: 18%	%Crossover:72%

  Max_Iterations: 10000	Iterations:267

--------- Resulting Map ---------

  . . I . . . . .
  . . I . . . . .
  . . . . . . S I
  . . . . R . . C
  . X . S . . . .
  . . R . C . . .
  . . S . . . . X
  . . S C R . . .

  Score: 63



fitness.txt Generated!: Log of fitness
behavior.txt Generated!: Log of iterations

Exiting of the simulation...




@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@ Example Output for Hill Climbing algorithm: @@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



linux> ./urbanplanning example.txt HC



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@ Example Output for Hill Climbing algorithm: @@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


nikolaos@nikolaos-Inspiron-7548:~/Desktop/CS534/Urban_Planning/Urban_Planning$ ./urbanplanning  sample3.txt HC

Calculating the best configuration. Please wait ...............................................................................................................................................

Simulation finished after 10002 ms **********************************

S T A T I S T I C S   O F   T H E   S I M U L A T I O N:

  Algorithm: Hill Climbing with restarts
  Number of Restarts:415
  Max_Iterations: 10000	Iterations:2870

--------- Resulting Map ---------

  . . . . . I . .
  . . S . . I . .
  . . . . . I S .
  . . . C . . . .
  . X . S . . . .
  . . R R C . . .
  . . S R . . . X
  . . S C . . . .

  Score: 168



fitness.txt Generated!: Log of fitness
behavior.txt Generated!: Log of iterations

Exiting of the simulation...
