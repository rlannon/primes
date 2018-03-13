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
	cout << "Primes" << endl << "A rudimentary prime calculator!" << endl;
	int dec = 0;
	bool q = false;
	while (q == false) {
		cout << "What do you want to do?" << endl;
		cout << "[1] Use Incremental Calculation" << endl << "[2] Use a Sieve" << endl << "[3] Test whether a number is prime" << endl << "[4] Quit" << endl;
		cin >> dec;
		switch(dec){
			case 1:
				vars();
				break;
			case 2:
				cout << "Not yet supported." << endl;
				break;
			case 3:
				cout << "Not yet supported." << endl;
				break;
			case 4:
				q=true;
				break;
			default:
				cout << "Invalid!" << endl;
				break;
		}
	}
	cout << endl << endl;
	return 0;
}

void vars(){

	// Declare and initialize all of our variables

	int i=3;
	int max=0;
	int min=0;
	bool vars_q = false; // stay in loop when false
	bool log = false; //whether to log to file
	bool log_p_num = false;
	int c;

	while (vars_q == false) {
		cout << "Lower limit? ";
		cin >> min;
		cout << "Upper limit? ";
		cin >> max;

		if (min<2){
			i=3;
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

	cout << "Output to log file?" << endl << "[1] Yes" << endl << "[2] Data only, no numbers" << endl << "[3] No" << endl;

	cin >> c;
	switch(c){
		case 1:		// data and numbers
			log = true;
			log_p_num = true;
			break;
		case 2:		// data only, no numbers
			log = true;
			log_p_num = false;
			break;
		case 3:		// no output
			log = false;
			log_p_num = false;
			break;
		default:
			cout << "Invalid; will not log results" << endl;
			log = false;
			log_p_num = false;
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

	int count = 0;	// initialize a variable to keep track of the number of primes we have calculated

	/* For debugging purposes:

	cout << "Debug: " << endl;
	cout << "dividend: " << dividend << endl;
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	cout << "print: " << print << endl;
	cout << "log: " << log << endl;
	cout << "log_p_num: " << log_p_num << endl;

	end debug variable section */

	ofstream logfile;
	logfile.open("new_prime.log");

	clock_t t;	// initialize our clock
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	if (log==true){
		logfile << "Program runtime: ";
		logfile << asctime(timeinfo) << endl;
		logfile << "min: " << min << endl;
		logfile << "max: " << max << endl;
	}

	if (print) cout << endl << "List: " << endl;


	// Without this, our calculation and count do not include 2, even though it is prime
	// All it does is increment the count and print 2 to the screen/to the log
	if (min == 2){
		if (print){
			cout << "2, ";
		}
		if (log && log_p_num){
			logfile << "2, ";
		}
		count=1;
	}

/*

Calculation method:

Test one number for prime-ness; start the divisor at two and increase until we hit the square root of the dividend

Vars:
Have a number, int count, which will count the number of primes we have in our list
Have a number, int dividend, which will be our dividend. It will increase in our loop
Have a number, int max, which is our highest test value
Have a number, int min, which is out lowest test value. It must be greater than or equal to 3.
Have a number, int divisor, which is our divisor
Have a number, int sq, which will be the square root (rounded) of our dividend
	we will make sq sqrt(dividend)+1, because of rounding--just to be safe

So our loop must go as follows:

start the counter--begin dividend at the min, and count up to the max, then stop
for every iteration of the count loop:
	start divisor at 2, because 1 will give us a positive result
	divide dividend by the divisor
	if the dividend divided by the divisor does not give us a remainder, break--the number is not prime
	if dividend%divisor != 0, increment the divisor until it is greater than or equal to the square root of the dividend
		we know that the divisor cannot be greater than the square root of the dividend--because a square root is the highest a factor of a number can be
		additionally, stopping at the square root is *significantly* faster than stopping once divisor reaches dividend
	if ANY number gives us a value of 0, then we break
	if none of the numbers up to sq give us 0, then we print out the current value of the count, or of the dividend, then break

	and on break:
		increment the count,
		increment the dividend
		begin loop again

*/

	t = clock(); //start the clock

	for (int dividend = min; dividend < max;) {		//	set our dividend to min, and loop until it reaches the max
		int sq = sqrt(dividend)+1;			//	set sq to be equal to the divident (rounded) + 1

		for (int divisor=2; divisor <= sq; divisor++){	//	begin the divisor at two, and loop until it reaches sq
			if (dividend%divisor == 0){
				break;
			} else if (dividend%divisor != 0 && divisor >= sq){
				if (print){			//	if the user decides to print numbers to screen, print them in a list
					cout << dividend << ", ";
				}
				if (log_p_num && log){		//	similarly, if the user wants to output numbers to log, print them in a list
					logfile << dividend <<", ";
				}
				count++;			//	and increment the count
			}
		}

		dividend++;	// increment the dividend
	}

	t = clock() - t;

	float t_s = (float)t/CLOCKS_PER_SEC;

	printf("\nThere are %d",count);
	printf(" prime numbers between %d",min);
	printf(" and %d\n\n",max);
	cout << "It took " << t_s << " seconds to calculate";
	cout << " (" << t << ") ticks" << endl;

	if(log){
		logfile << endl << "Number primes: " << count << endl;
		logfile << "Compute time: " << endl;
		logfile << "\tTicks: " << t << endl;
		logfile << "\tSeconds: " << t_s << endl;
	}

	logfile.close();

	return;
}
