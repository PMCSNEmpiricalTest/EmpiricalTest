#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"

#define n 10
#define k 4
#define d 2
//define confidence level
#define alpha 0.05

//define gap (a,b)
#define a 0.10
#define b 0.90

// gap length is a Geometric(1-sigma)
int compute_e (int val, double sigma)
{
	if (val == k-1)
		return n*pow(1-sigma,k-1);
	else
		return n*sigma*pow(1-sigma,val);
}

// indexes initialization
int x, i, j;
// random variables
double u,r;
// array initialization
int *o;
o = (int *)malloc(sizeof(int)*k);
if (o == 0)
{
	perror("malloc");
	return 1;
}

for (x=0; x<k; x++) {
  o[x]=0;
}
for (i=0;i<n;i++) {
  x=0;
  u=Random();
  while (u<a || u>b) {
    x++;
    u=Random();
  }
  if (x>k-1)
    x=k-1;
  o[x]++;
}

//calc v (with e_x as expectation)

double v=0.00;
// subinterval length
double sigma = b-a;
int w=0;
double o_div = 0.00;
for (w=0; w<=k-1; w++){
	double e_x = compute_e(w,sigma);
	o_div = o[w]-e_x;
	o_div = o_div*o_div;
	o_div = o_div/e_x;
}
//critical values

double v1_s = idfChisquare(k-1,alpha/2);
double v2_s = idfChisquare(k-1,1-alpha/2);

//proof
/*
if (v < v1_s || v > v2_s)
	printf("test failed");
*/
