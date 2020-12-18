#include<stdio.h>
#include<time.h>
#include "mt.h"

int main ( void ){
	int i, m, slotmachine;
	double rnd;
	unsigned long long seed;

	seed = (unsigned long long)time(NULL);
	init_genrand64( seed );

	m = 5;

	for( i = 0; i < 10; i++ ){
		slotmachine = genrand64_int63() % m;
		rnd = genrand64_real1();
		printf( "%d\t%lf\n", slotmachine, rnd );
	}

	return 0;
}
