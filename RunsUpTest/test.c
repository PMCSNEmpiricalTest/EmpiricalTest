#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include "rvms.h"

#define n 7200
#define k 6
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
	// preliminary test on generator
	assert(TestRandomNotVerbose() == EXIT_SUCCESS);

	// indexes initialization
	int x,i;
	// random variables
	double u,t;
	// array initialization
	int *o;
	o = (int *)calloc(k,sizeof(int));
	if (o == 0)
	{
		perror("error in calloc");
		return EXIT_FAILURE;
	}

	for (i=0; i<n; i++) {
	  x=0;
	  u=Random();
		t=Random();
	  while (t>u) {
	    x++;
	    u=t;
	    t=Random();
	  }
	  if (x>=k)
	    x=k-1;
	  o[x]++;
	}
	int z;
	printf("Here is vector o:\n");
	for (z=0;z<k;z++)
	{
		printf("%d,", o[z]);
	}
	printf("\n\n");

	//calc v (with e_x as expectation)

	double v=0.00;
	int w=0;
	double o_div = 0.00;
	double e_x = 0.00;
	for (w=0; w<k; w++){
		e_x = n*w/Fact(2+w);
		printf("This is e_x : %f\n",e_x);
		o_div = o[w]-e_x;
		printf("This is o[w]-e_x : %f\n",o_div);
		o_div = o_div*o_div;
		printf("This is o_div*o_div : %f\n",o_div);
		o_div = o_div/e_x;
		printf("This is o_div/e_x : %f\n",o_div);
		v = v+o_div;
		printf("This is v+o_div : %f\n",v);
	}
	//critical values

	double v1_s = idfChisquare(k-1,a/2);
	double v2_s = idfChisquare(k-1,1-a/2);

	printf("This is v : %f\n", v);
	return 0;

	//proof
	/*
	if (v < v1_s || v > v2_s)
		printf("test failed");
	*/
}

int main(int argc, char **argv){
	int i=0;
	for (i=0;i<1;i++){
		test();
	}
	return EXIT_SUCCESS;
}
