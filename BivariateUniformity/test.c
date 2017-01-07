#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"

#define n 10
#define k 4
//confidence level
#define a 0.05

// indexes initialization
int x1,x2, i;
// random variables
double u1,u2;
// array initialization
int **o = (int **)malloc(k * sizeof(int*));
for(int e = 0; e < k; e++) o[e] = (int *)malloc(k * sizeof(int));
if (o == 0)
{
	perror("malloc");
	return 1;
}

for (x1=0; x1<k; x1++)
  for (x2=0; x2<k; x2++)
	 o[x1][x2] = 0;
for (i =0; i<n; i++) {
	u1 = Random();
	x1 = (int) u1*k;
  u2 = Random();
	x2 = (int) u2*k;
	o[x1][x2]++;
}

//calc v (with e_x as expectation)

double v=0.00;
int w1=0;
int w2=0;
double o_div = 0.00;
double e_x = n/(k*k);
for (w1=0; w1<=k-1; w1++){
	for (w2=0; w2<=k-1; w2++){
		o_div = o[w1][w2]-e_x;
		o_div = o_div*o_div;
		o_div = o_div/e_x;
	}
}
//critical values

double v1_s = idfChisquare(k-1,a/2);
double v2_s = idfChisquare(k-1,1-a/2);

//proof
/*
if (v < v1_s || v > v2_s)
	printf("test failed");
*/
