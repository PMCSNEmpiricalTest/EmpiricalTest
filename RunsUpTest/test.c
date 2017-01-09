#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "rngs.h"
#include "rvms.h"

#define n 10
#define k 4
//confidence level
#define a 0.05

int Fact (int u)
{
	int r = 1;
	for (int i=2; i<=u; i++)
		r *= i;
	return r;
}

int test(){
	TestRandom();
	// indexes initialization
	int x, i, j;
	// random variables
	double u,r,t;
	// array initialization
	int *o;
	o = (int *)malloc(sizeof(int)*k);
	if (o == 0)
	{
		perror("malloc");
		return EXIT_FAILURE;
	}

	for (x=1; x<=k; x++)
	  o[x] = 0;
	for (i=0; i<n; i++) {
	  x=1;
	  u=Random();
		t=Random();
	  while (t>u) {
	    x++;
	    u=t;
	    t=Random();
	  }
	  if (x>k)
	    x=k;
	  o[x]++;
	}

	//calc v (with e_x as expectation)

	double v=0.00;
	int w=0;
	double o_div = 0.00;
	for (w=1; w<=k; w++){
		double e_x = n*w/Fact(1+w);
		o_div = o[w]-e_x;
		o_div = o_div*o_div;
		o_div = o_div/e_x;
	}
	//critical values

	double v1_s = idfChisquare(k-1,a/2);
	double v2_s = idfChisquare(k-1,1-a/2);

	return 0;

	//proof
	/*
	if (v < v1_s || v > v2_s)
		printf("test failed");
	*/
}

int main(int argc, char **argv){
	test();
	return EXIT_SUCCESS;
}
