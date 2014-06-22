#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <unistd.h>

#include "mypara.h"
#include "Point.h"
#include "boundary.h"

mutex m0;

void ElectronDist(CPoint*** Point)
{
	Q = 0;
	int i, j, k;
	for(i = 0; i < 3; i++)
	{
		Dip[i]=0;
		for(j = 0; j < 3; j++)
		{
			Qr[i][j] = 0;
		}
	}
	int NxBeg = CtNx - InNx/2;
	int NyBeg = CtNy - InNy/2;
	int NzBeg = CtNz - InNz/2;
	for(i = NxBeg; i < NxBeg + InNx; i++)
	{
		for(j = NyBeg; j < NyBeg + InNy; j++)
		{
			for(k = NzBeg; k < NzBeg + InNz; k++)
			{
				if(Point[i][j][k].potentialFix)
				{
					EleDist[i-NxBeg][j-NyBeg][k-NzBeg] = - dieleConst * (Point[i+1][j][k].potential+Point[i-1][j][k].potential+Point[i][j+1][k].potential+Point[i][j-1][k].potential+Point[i][j][k+1].potential+Point[i][j][k-1].potential - 6 * Point[i][j][k].potential)/delta2;

					Q += EleDist[i-NxBeg][j-NyBeg][k-NzBeg] * delta2 * delta;
					Dip[0] += (i-CtNx)*EleDist[i-NxBeg][j-NyBeg][k-NzBeg] * delta2 * delta2;
					Dip[1] += (j-CtNy)*EleDist[i-NxBeg][j-NyBeg][k-NzBeg] * delta2 * delta2;
					Dip[2] += (k-CtNz)*EleDist[i-NxBeg][j-NyBeg][k-NzBeg] * delta2 * delta2;
				}
			}
		}
	}
	cout << Q << " " << Dip[0] << " " << Dip[1] << " " << Dip[2] << endl;
}

double ModifyBound(CPoint*** Point)
{
	int i, j, k;
	//the surface of the area
	double r[4];    //r[3]=|r|
	double MaxE = 0;
	double tmp;
	CntBoundModify ++;
	printf("Modifying boundary: %d\n", CntBoundModify);
	
	ElectronDist(Point);
	m0.lock();
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			tmp = Point[i][j][0].potential;
			r[0] = (i-CtNx) * delta;
			r[1] = (j-CtNy) * delta;
			r[2] = -CtNz * delta;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[i][j][0].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[i][j][0].potential - tmp ) > MaxE)
				MaxE = abs(Point[i][j][0].potential - tmp );
			tmp = Point[i][j][Nz-1].potential;
			r[2] = (Nz-1-CtNz) * delta;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[i][j][Nz-1].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[i][j][Nz-1].potential - tmp ) > MaxE)
				MaxE = abs(Point[i][j][Nz-1].potential - tmp );
		}
	}
	for(j = 0; j < Ny; j++)
	{
		for(k = 0; k < Nz; k++)
		{
			tmp = Point[0][j][k].potential;
			r[0] = -CtNx * delta ;
			r[1] = (j-CtNy) * delta ;
			r[2] = (k-CtNz) * delta ;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[0][j][k].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[0][j][k].potential - tmp ) > MaxE)
				MaxE = abs(Point[0][j][k].potential - tmp );
			tmp = Point[Nx-1][j][k].potential;
			r[0] = (Nx-1-CtNx) * delta;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[Nx-1][j][k].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[Nx-1][j][k].potential - tmp ) > MaxE)
				MaxE = abs(Point[Nx-1][j][k].potential - tmp );
		}
	}
	for(i = 0; i < Nx; i++)
	{
		for(k = 0; k < Nz; k++)
		{
			tmp = Point[i][0][k].potential;
			r[0] = (i-CtNx) * delta ;
			r[1] = -CtNy * delta ;
			r[2] = (k-CtNz) * delta ;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[i][0][k].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[i][0][k].potential - tmp ) > MaxE)
				MaxE = abs(Point[i][0][k].potential - tmp );
			tmp = Point[i][Ny-1][k].potential;
			r[1] = (Ny-1-CtNz) * delta;
			r[3] = pow(r[0]*r[0] + r[1]*r[1] + r[2]*r[2], 0.5);
			Point[i][Ny-1][k].potential = (1/(4*Pi*dieleConst)) * (Q / r[3] + (Dip[0]*r[0]+Dip[1]*r[1]+Dip[2]*r[2])/(r[3]*r[3]*r[3]));
			if(abs(Point[i][Ny-1][k].potential - tmp ) > MaxE)
				MaxE = abs(Point[i][Ny-1][k].potential - tmp );
		}
	}
	m0.unlock();
	return MaxE;
}
