#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"
#include "rvms.h"

#define n 10
#define k 4
#define d 2
//confidence level
#define a 0.05

void test(){
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

	for (x=0; x<k; x++)
		o[x] = 0;
	for (i =0; i<n; i++) {
		r = Random();
		for (j=1; j<d; j++) {
			u = Random();
			if (u>r)
				r=u;
		}
		u = exp(d*log(r));
		x = (int) u*k;
		o[x]++;
	}

	//calc v (with e_x as expectation)

	double v=0.00;
	int w=0;
	double o_div = 0.00;
	double e_x = n/k;
	for (w=0; w<=k-1; w++){
		o_div = o[w]-e_x;
		o_div = o_div*o_div;
		o_div = o_div/e_x;
	}

	//critical values

	double v1_s = idfChisquare(k-1,a/2);
	double v2_s = idfChisquare(k-1,1-a/2);

	//proof
	/*
	if (v < v1_s || v > v2_s)
		printf("test failed");
	*/
}
