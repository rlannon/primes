#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//the goal of this program is to calculate prime numbers

void primeCalc(int i, int min, int max, bool print, bool log);
void vars();

int main(){
	printf("primes\n");
	printf("A rudimentary program for prime number calculation\n\n");
	int dec = 0;
	bool q = false;
	while (q == false) {
		printf("What do you wish to do? \n");
		printf("[1] Calculate using trial division method\n");
		printf("[2] Calculate using sieve of Eratosthenes\n");
		printf("[3] Quit\n");
		scanf("%d",&dec);
		switch(dec){
			case 1:
				vars();
				break;
			case 2:
				printf("currently not supported.\n\n");
				break;
			case 3:
				q=true;
				break;
			default:
				printf("Invalid selection.\n\n");
				break;
		}
	}
	return 0;
}

void vars(){
	int i=2;
	int max=0;
	int min=0;
	bool vars_q = false; // stay in loop when false
	bool log = false; //whether to log to file
	int c;

	while (vars_q == false) {
		printf("Lower limit? ");
		scanf("%d",&min);
		printf("Upper limit? ");
		scanf("%d",&max);

		if (min<2){
			i=2;
			min = 2;
			printf("\nmin was set to an integer lower than 2\n");
			printf("Calculating from 2\n");
			vars_q = true; // set to true to continue
		}
		if (min == max){
			min = 2;
			i = 2;
			printf("\nlower and upper limits cannot be the same\n");
			vars_q = false;
		} else if (min > max){
			i=2;
			min = 2;
			printf("\nlower limit cannot be greater than upper limit\n");
			vars_q = false;
		} else if (min < max && min >= 2){
			i=min;
			vars_q = true;
		} else {
			printf("\nUnexpected error!\n");
			return;
		}
	}
	printf("\nPrint resultant numbers?\n");
	printf("[1] Yes\n[2] No\n");
	scanf("%d",&c);
	switch(c){
		case 1:
			vars_q = true;
			break;
		case 2:
			vars_q = false;
			break;
		default:
			printf("invalid selection -- will NOT print\n");
			vars_q = false;
	}
	printf("Output to file 'log'?\n[1] Yes\n[2] No\n");
	scanf("%d",&c);
	switch(c){
		case 1:
			log = true;
			break;
		case 2:
			log = false;
			break;
		default:
			printf("Invalid selection. Will NOT output to file.\n");
			log = false;
			break;
	}
	primeCalc(i, min, max, vars_q, log);
	return;
}

void primeCalc(int i, int min, int max, bool print, bool log) {

	FILE *logfile, *fopen();
	logfile = fopen("primes_log","w");
	if ((logfile = fopen("primes_log","w")) == NULL){
		printf("Couldn't open file!\n");
		exit(1);
	} else {
			if(log) printf("File opened successfully\n");
	}

	int record = 1;
	int n = 0;
	clock_t t;

	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	if(log){
		fprintf(logfile,"Program runtime: ");
		fprintf(logfile,"%s\n", asctime(timeinfo));
		fprintf(logfile,"min: %d\n",min);
		fprintf(logfile,"max: %d\n",max);
		fprintf(logfile,"\n");
	}

	if (print) {
		printf("\nList:\n\n2, ");
	} else if (!print) {
		printf("\nCalculating--this may take a moment...\n");
	}

	if (log) {
		fprintf(logfile,"\nList:\n\n2, ");
	}
/*

It is inefficient to cycle through every integer when testing whether
a number is prime. For example, why test any even number when we already know
the number we are testing does not divide by two?

*/

	t = clock();
	for (int count = min; count < max;) {
		for (n=2; n <= (i-1); n++){
			if (i%n == 0){
				break;
			} else if (i%n != 0 && n==(i-1)){
				if (print) printf("%d, ",i);
				if (log) fprintf(logfile,"%d, ",i);
				record++;
			}
		}
		count++;
		i++;
	}
	if (min > 2){
		record -= 1;
	}

	t = clock() - t;
	float seconds=(((float)t)/CLOCKS_PER_SEC);
	float milliseconds = seconds*1000;

	printf("\nThere are %d",record);
	printf(" prime numbers between %d",min);
	printf(" and %d\n\n",max);
	printf("It took %d ticks to calculate\n",t);
	if (seconds < 1){
		printf("It took %f milliseconds to calculate\n\n",milliseconds);
	} else if( seconds >= 1){
		printf("It took %f seconds to calculate\n\n",seconds);
	}
	if(log){
		fprintf(logfile,"\nNumber of primes: %d\n\n",record);
		fprintf(logfile,"Compute time:\n");
		fprintf(logfile,"\tticks: %d\n",t);
		if (seconds < 1){
			fprintf(logfile,"\tmilliseconds: %f\n",milliseconds);
		} else if (seconds >= 1) {
			fprintf(logfile,"\tseconds: %f\n", seconds);
		}
	}

	fclose(logfile);

	return;
}
