/*
 * guojk
 * ~35G
 */

#ifndef MYPARA_H_
#define MYPARA_H_

#define Nx 1800
#define Ny 1800
#define Nz 1800
#define dieleConst 7.212e-10  // 8.85*10^(-12)*81.5
#define electron 1.602189e-19
#define E 2.718281828459

#define delta 5e-7    //the length of each cubic (unit:m)
#define ThreadNum 30    //depends on the computer
#define MAXERR 5e-5    //if the gap between two calculation, is smaller than MaxErr, I do think that the numerial result is convincing

double omega = 1.9;

#endif
