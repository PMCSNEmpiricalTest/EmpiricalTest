#include<stdio.h>
#include<stdlib.h>



long gcd(long a, long b)
{
    long temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

long g(long x, long m, long a )
{
        long q = m / a;
        long r = m % a;
        long t = a*(x%q) - r * (x/q);
        if(t>0)
        {
                return t;
        }
        else
        {
                return t+m;
        }
}


int main(int argc, char** argv)
{
        if (argc == 2)
        {
                printf("choosen %s as a instead of 7\n", argv[1]);
                strtol(argv[1], NULL, 10);
        }

        //begin of algorhitm pag 52
        long m = 2147483647;
        long i = 1;
        long a = 7;
        long x = a;

        long counter = 0;

        while(x != 1)
        {
                if((m%x < m/x) && (gcd(i, m-1)==1))
                {
                        printf("%li,", x);
                        counter++;
                }

                i++;
                x = g(x, m, a);

        }

        printf("\n\nITERATIONS: %li, m is %li\n\nFOUND %li RESULTS\n\nEND\n", i,m,counter);
        return EXIT_SUCCESS;
}

