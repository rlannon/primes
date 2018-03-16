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
#include <string>

// Our includes

#include "primeCalc.h"

// Declare our functions so we can declare main() first...because lazy
void vars();

// we will just declare our standard namespace globally because why not
using namespace std;

// our code
int main(){
	cout << "primes" << endl << "A rudimentary prime calculator" << endl;
	cout << "For help, type 'help'" << endl << endl;
	//our variables for int main()
	string input;			// what the user enters; to be parsed
	int dividend;			// for our "check" command
	int count_dummy;		// dummy variable for the calcMethod function
	int factor=0;			// the factor we wish to calculate
	bool q = false;			// have we quit yet?
	while (q == false) {		// main program loop
		getline(cin, input);
		if (input == "help"){
			cout << "To calculate primes, type:\n\tcalc" << endl;
			cout << "To check if a number is prime, type:\n\tcheck" << endl;
			cout << "To quit, type:\n\tquit" << endl;
		}
		if (input == "calc"){
			vars();
		}
		if (input == "check"){
			cout << "Enter the number you wish to check: ";
			cin >> dividend;
			if(calcMethod(dividend, count_dummy, factor)){
				cout << dividend << " is prime." << endl;
			} else {
				cout << dividend << " is not prime. " << factor << " is a factor." << endl;
			}
		}
		if (input == "sieve"){
			cout << "This function is not yet supported." << endl;
		}
		if (input == "quit"){
			q = true;
		}
		cout << endl;
	}
	cout << endl;
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
	primeCalc(dividend, min, max, vars_q, log, log_p_num);
	return;
}
