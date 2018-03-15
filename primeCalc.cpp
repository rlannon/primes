/* primeCalc.cpp -- our file for defining the methods in primeCalc.h */

#include "primeCalc.h"

void primeCalc(int dividend, int min, int max, bool print, bool log, bool log_p_num) {

/*
	Initialize all of our data
	First, we create our file
	Then we initialize our clock
	Then we output the header data to the log, if the user chooses to save the data to the log
*/

	int count = 0;	// initialize a variable to keep track of the number of primes we have calculated
	int factor=0;	// dummy variable for the calcMethod(int dividend, int& count, int& factor) function.
			// might eliminate the dummy variable 'int factor' by making a copy of 'bool calcMethod' with no factor option

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
	logfile.open("primes.log");

	clock_t t;	// initialize our clock
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	//check to see if our file opened successfully; if not, set log and log_p_num to false
	if(logfile.is_open()){
		cout << "File opened successfully" << endl;
	} else {
		cout << "Error opening file" << endl;
		log = false;
		log_p_num = false;
	}

	//If we are writing to the logfile, write in some header data
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
		if (calcMethod(dividend, count, factor)){	//	call our calcMethod function to test whether a given number is prime
			if (print) cout << dividend << ", ";
			if (log && log_p_num) logfile << dividend << ", ";
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

bool calcMethod(int dividend, int& count, int &factor){
	int sq = sqrt(dividend)+1;			//	set sq to be equal to the divident (rounded) + 1
	for (int divisor=2; divisor <= sq; divisor++){	//	begin the divisor at two, and loop until it reaches sq
		if (dividend%divisor == 0){
			factor = divisor;		
			return false;			//	return false; number is not prime			
			break;
		} else if (dividend%divisor != 0 && divisor >= sq){
			count++;
			return true;			//	return true; number is prime
		}
	}
}
