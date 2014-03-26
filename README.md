ElePotentialNumerical
=====================

This program we wrote can calculate the electrostatic potential in 3-dimensional space numerically by solving Laplace's Equation, using Successive Overrelaxation Method.

Before calculating, we should first set the boundary condition by modifying the file "boundary.cpp". Then compile, and finally run. The program will record the result on hard disk.

Here, the boundary condition we setted is a sphere which is 1V in potential, and 50um in radius. 

Some specific parameters, such as the size of the space and the number of threads the program would utilize, are set in the file "mypara.h".

Though it can run pretty well, the code is actually preliminary, so we always maintain it.

Jingkun Guo
