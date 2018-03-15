/////////////////////////////////////
/////	MAIN.CPP		/////
/////	PRIME_PROJECT		/////
/////	copyright 2018		/////
/////////////////////////////////////

// Standard headers and libraryes

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>

// Our includes

#include "primeCalc.h"

// Declare our functions so we can declare main() first...because lazy
void vars();

// we will just declare our standard namespace globally because why not
using namespace std;

// our code
int main(){
	cout << "Primes" << endl << "A rudimentary prime calculator!" << endl;
	int dec = 0;
	int y=0;
	int factor=0;
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
				cout << "Number to test: ";
				cin >> dec;
				if (primeCalc::calcMethod(dec, y, factor)) cout << "\n" << dec << " is prime\n" << endl;
				else cout << "\n" << dec << " is not prime -- " << factor << " is a factor\n" << endl;
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

	int dividend=3;
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
			dividend=3;
			min = 2;
			cout << "min set to an integer value lower than 2" << endl << "calculating from min = 2" << endl;
			vars_q = true; // set to true to continue
		}
		if (min == max){
			min = 2;
			dividend = 3;
			cout << "min cannot equal max" << endl;
			vars_q = false;
		} else if (min > max){
			dividend=3;
			min = 2;
			cout << "min must be smaller than max" << endl;
			vars_q = false;
		} else if (min < max && min >= 2){
			dividend=min;
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
	primeCalc::primeCalc(dividend, min, max, vars_q, log, log_p_num);
	return;
}
