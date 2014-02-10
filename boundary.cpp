/*
 * guojk, leizj
 * circle
 */

#include <iostream>
#include <fstream>
#include "Point.h"
#include "mypara.h"
using namespace std;

void CheckBoundaryCondition(CPoint*** Point)
{
	ofstream filef("FP.txt");
	int i, j;
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			filef << Point[i][j][Nz/2].potentialFix << " ";
		}
		filef << endl;
	}
}

void BoundaryCondition(CPoint*** Point)
{
	cout << "creating boundary condition" << endl;
	int i, j, k;

	//the surface of the aera
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			Point[i][j][0].potential = 0;
			Point[i][j][0].potentialFix = 1;
			Point[i][j][Nz-1].potential = 0;
			Point[i][j][Nz-1].potentialFix = 1;
		}
	}
	for(j = 0; j < Ny; j++)
	{
		for(k = 0; k < Nz; k++)
		{
			Point[0][j][k].potential = 0;
			Point[0][j][k].potentialFix = 1;
			Point[Nx-1][j][k].potential = 0;
			Point[Nx-1][j][k].potentialFix = 1;
		}
	}
	for(i = 0; i < Nx; i++)
	{
		for(k = 0; k < Nz; k++)
		{
			Point[i][0][k].potential = 0;
			Point[i][0][k].potentialFix = 1;
			Point[i][Ny-1][k].potential = 0;
			Point[i][Ny-1][k].potentialFix = 1;
		}
	}

	//inside
	k = Nz/2;
	//the inner circle
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			if( ((i-Nx/2.0)*delta)*((i-Nx/2.0)*delta) +  ((j-Ny/2.0)*delta)*((j-Ny/2.0)*delta) < (15e-6)*(15e-6))
			{
				Point[i][j][k].potential = 0;
				Point[i][j][k].potentialFix = 1;
			}
		}
	}
	//the outer ring
	double tmpr;
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			tmpr = ((i-Nx/2.0)*delta)*((i-Nx/2.0)*delta) +  ((j-Ny/2.0)*delta)*((j-Ny/2.0)*delta);
			if(tmpr < (25e-6)*(25e-6) && tmpr > (20e-6)*(20e-6))
			{
				Point[i][j][k].potential = 10;
				Point[i][j][k].potentialFix = 1;
			}
		}
	}
	CheckBoundaryCondition(Point);
	cout << "BC finiehed" << endl;
}
