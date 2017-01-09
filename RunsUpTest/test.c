#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include "rvms.h"

#define n 14400
#define k 6
//confidence level
#define a 0.05

int DEBUG = 0;

int Fact (int u)
{
	int r = 1;
	for (int i=2; i<=u; i++)
		r *= i;
	return r;
}

double test(int stream){
	// preliminary test on generator
	assert(TestRandomNotVerbose() == EXIT_SUCCESS);

	if(DEBUG) printf("\n\n -----  BEGIN OF TEST -----\n");

	//this is the stream to select for each test
	SelectStream(stream);
	long test_initial_seed;
	GetSeed(&test_initial_seed);

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

	if(DEBUG)
	{
		printf("Here is vector o:\n");
		for (z=0;z<k;z++)
		{
			printf("%d,", o[z]);
		}
		printf("\n");
	}

	//calc v (with e_x as expectation)

	double v=0.00;
	int w=0;
	double o_div = 0.00;
	double e_x = 0.00;
	for (w=0; w<k; w++){
		e_x = n*(w+1)/Fact(2+w);
		if(DEBUG) printf("This is e_x : %f\n",e_x);
		o_div = o[w]-e_x;
		if(DEBUG) printf("This is o[w]-e_x : %f\n",o_div);
		o_div = o_div*o_div;
		if(DEBUG) printf("This is o_div*o_div : %f\n",o_div);
		o_div = o_div/e_x;
		if(DEBUG) printf("This is o_div/e_x : %f\n",o_div);
		v = v+o_div;
		if(DEBUG) printf("This is v+o_div : %f\n",v);
	}
	//critical values

	double v1_s = idfChisquare(k-1,a/2);
	double v2_s = idfChisquare(k-1,1-a/2);

	printf("%d;%f;%ld\n", stream+1, v,test_initial_seed);


	if(DEBUG) printf(" -----  END OF TEST -----\n\n");
	return v;

	//proof
	/*
	if (v < v1_s || v > v2_s)
		printf("test failed");
	*/
}

int main(int argc, char **argv){
	if(argc == 2)
	{
		DEBUG = strtol(argv[1] , NULL, 10);
    if (errno != 0)
    {
      fprintf(stderr, "Error in conversion\n");
      return EXIT_FAILURE;
    }
	}

	double v1_s = idfChisquare(k-1,a/2);
	double v2_s = idfChisquare(k-1,1-a/2);
	int disp[3] = {0,0,0};

	int i=0;
	double temp = 0;
	printf("Test -> v1_s: %f ; v2_s: %f\n", v1_s, v2_s);
	printf("(stream, v, initial seed)\n");
	for (i=0;i<256;i++){
		temp = test(i);
		if(temp<v1_s) disp[0]++;
		if(temp>v2_s) disp[2]++;
		if(temp>=v1_s && temp<=v2_s) disp[1]++;
	}
	printf("\nDispersion is:\n%d;%d;%d\n", disp[0], disp[1], disp[2]);
	return EXIT_SUCCESS;
}
