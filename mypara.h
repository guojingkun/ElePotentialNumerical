/*
 * guojk
 * ~35G
 */

#ifndef MYPARA_H_
#define MYPARA_H_

#include <cmath>

#define Nx 300
#define Ny 300
#define Nz 300
#define InNx 100
#define InNy 100
#define InNz 100
#define dieleConst 7.212e-10  // 8.85*10^(-12)*81.5
#define electron 1.602189e-19
#define E 2.718281828459
#define Pi 3.14159265

#define delta 1e-6    //the length of each cubic (unit:m)
#define ThreadNum 3    //depends on the computer
double MAXERR = 1e-4;    //if the gap between two calculation, is smaller than MaxErr, I do think that the numerial result is convincing
double BOUNDERR = 1e-4;  //If the error of space boundary is smaller than it, the result is converged.
double MAXERR2 = 3e-5;
double MAXERR3 = 1e-5;


double omega = 1.9;
int CtNx = Nx/2;
int CtNy = Ny/2;
int CtNz = Nz/2;
int CtInNx = InNx/2;
int CtInNy = InNy/2;
int CtInNz = InNz/2;
int CntBoundModify = 0;

double EleDist[InNx][InNy][InNz] = {0};
double Q = 0;
double Dip[3] = {0};
double Qr[3][3] = {0};
double delta2 = pow(delta,2);

#endif
