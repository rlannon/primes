#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>

//the goal of this program is to calculate prime numbers

void primeCalc(int dividend, int min, int max, bool print, bool log, bool log_p_num);
void vars();

using namespace std;

int main(){
/*	cout << "Primes" << endl << "A rudimentary prime calculator!" << endl;
	int dec = 0;
	bool q = false;
	while (q == false) {
		cout << "What do you want to do?" << endl;
		cout << "[1] Calculate primes" << endl << "[2] Use a sieve" << endl << "[3] Quit" << endl;
		cin >> dec;
		switch(dec){
			case 1:
				vars();
				break;
			case 2:
				cout << "Not supported." << endl;
				break;
			case 3:
				q=true;
				break;
			default:
				cout << "Invalid!" << endl;
				break;
		}
	}
*/
	primeCalc(2,2,100,1,0,0);
	cout << endl;
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
		cout << "Lower limit? ";
		cin >> min;
		cout << "Upper limit? ";
		cin >> max;

		if (min<2){
			i=2;
			min = 2;
			cout << "min set to an integer value lower than 2" << endl << "calculating from min = 2" << endl;
			vars_q = true; // set to true to continue
		}
		if (min == max){
			min = 2;
			i = 3;
			cout << "min cannot equal max" << endl;
			vars_q = false;
		} else if (min > max){
			i=3;
			min = 2;
			cout << "min must be smaller than max" << endl;
			vars_q = false;
		} else if (min < max && min >= 2){
			i=min;
			vars_q = true;
		} else {
			cout << "unexpected error!" << endl;
			return;
		}
	}
	cout << "Print numbers in stream to screen?" << endl;
	cout << "[1] Yes" << endl << "[2] No" << endl;
	cin >> c;
	switch(c){
		case 1:
			vars_q = true;
			break;
		case 2:
			vars_q = false;
			break;
		default:
			cout << "Invalid; will not print" << endl;
			vars_q = false;
	}

	bool log_p_num = true;;
	cout << "Output to log file?" << endl << "[1] Yes" << endl << "[2] Data only, no numbers" << endl << "[3] No" << endl;
	cin >> c;
	switch(c){
		case 1:
			log = true;
			log_p_num = true;
			break;
		case 2:
			log = true;
			log_p_num = false;
		case 3:
			log = false;
			log_p_num = false;
			break;
		default:
			cout << "Invalid; will not log results" << endl;
			log = false;
			break;
	}
	primeCalc(i, min, max, vars_q, log, log_p_num);
	return;
}

void primeCalc(int dividend, int min, int max, bool print, bool log, bool log_p_num) {

/*
	Initialize all of our data
	First, we create our file
	Then we initialize our clock
	Then we output the header data to the log, if the user chooses to save the data to the log
*/

	ofstream logfile;
	logfile.open("prime_log");

	int record = 0;
	//int n = 0;
	clock_t t;

	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	if(log){
		logfile << "Program runtime: ";
		logfile << asctime(timeinfo) << endl;
		logfile << "min: " << min << endl;
		logfile << "max: " << max << endl;
	}

	if (print) cout << endl << "List: " << endl;

/*

Calculation method:

Test one number for prime-ness; start the divisor at two and increase until we hit the square root of the dividend

Have a number, int count, which will be used to count where we are in our for loop
	we will start at the min, and increment until we reach the max
Have a number, i, which will be our dividend--and will be equal to the count
Have a number, int max, which is our highest test value
Have a number, int divisor, which is our divisor
Have a number, sq, which will be the square root (rounded) of our dividend
	we will make sq sqrt(divident)+1, because of rounding--just to be safe

So our loop must go as follows:

start the counter--start at the min, and count up to the max, then stop
for every iteration of the count:
	start divisor at 2, because 1 will give us a positive result
	divide dividend by the divisor
	if the dividend divided by the divisor does not give us a remainder, break--the number is not prime
	if it does, increment the divisor until it is greater than or equal to the square root of the dividend
		we know that the divisor cannot be greater than the square root of the dividend--because a square root is the highest a factor of a number can be
	if ANY number gives us a value of 0, then we break
	if none of the numbers up to sq give us 0, then we print out the current value of the count, or of the dividend, then break

	and on break:
		increment the count,
		increment the dividend

*/

	t = clock();

	for (int count = min; count < max;) {
		int sq = sqrt(dividend)+1;
		for (int divisor=2; divisor <= sq; divisor++){
		}
	}
	if (min > 2){
		record -= 1;
	}

	t = clock() - t;

	float t_s = (float)t/CLOCKS_PER_SEC;

	printf("\nThere are %d",record);
	printf(" prime numbers between %d",min);
	printf(" and %d\n\n",max);
	cout << "It took " << t_s << " seconds to calculate";
	cout << " (" << t << ") ticks" << endl;

	if(log){
		logfile << endl << "Number primes: " << record << endl;
		logfile << "Compute time: " << endl;
		logfile << "\tTicks: " << t << endl;
		logfile << "\tSeconds: " << t_s << endl;
	}

	logfile.close();

	return;
}
