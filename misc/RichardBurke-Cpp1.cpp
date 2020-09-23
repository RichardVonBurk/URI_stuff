// Richard Burke
// Cpp-2
// Program that asks enduser for input in order to calculate
// a loan with the loan amount, annual interest rate,
// number of payments.

#include <iostream>
#include <cmath> //needed for pow function
#include <string> //needed for strings
#include <iomanip> //needed for setprecision
using namespace std;

int main()
{
	int numPayment;		// Number of Payments
	double loanAmount,
		annualRate,		// Annual Interest Rate
		monthRate,		// Monthly Interest Rate
		monthPayment,	// Monthly Payment
		totalPaid,		// Amount Paid Back
		totalInterest,	// Interest Paid
		monthRateDec;	// Monthly Interest Rate in decimal percent form

	string name;		// Name of client taking the Loan

	cout << "Richard Burke" << endl << endl;
	// Series of input info from the enduser need for calculations later
	// as well as greet the enduser. setw() used for allignment.
	cout << "Enter the loan amount:" << setw(13) << "";
	cin >> loanAmount;
	cout << "Enter the annual interest rate:" << setw(4) << "";
	cin >> annualRate;
	cout << "Enter the number of payments made:" << setw(1) << "";
	cin >> numPayment;
	cin.ignore();
	cout << "Enter the customer's name" << setw(10) << "";
	getline(cin, name);
	cout << endl;

	// Convert [Annual Interest Rate] input to [Monthly Interest Rate]
	monthRate = annualRate / 12;
	// Formula requires rate be in decimal percent form, thus needs to be converted
	monthRateDec = monthRate / 100;
	// Formula: Payment = {[Rate*(1+Rate)^N] / [(1+Rate)^N -1]} * L
	// Rate is monthly interest
	// L is the amount of the loan
	// N is Number of Payments 
	monthPayment = ((((monthRateDec)*(pow(1 + monthRateDec, numPayment))) / (pow(1 + monthRateDec, numPayment) - 1)) * loanAmount);
	// Monthly Payment = Amount Paid Back / Number of Payments
	totalPaid = monthPayment*numPayment;
	totalInterest = totalPaid - loanAmount;

	// Series of output info after calculations setprecision 2 mostly used for currency consistancy,
	// use setw() to allow allignment
	cout << setprecision(2) << fixed;
	cout << "Welcome " << name << "." << endl << "Here is your loan information:" << endl;
	cout << "Loan Amount:" << setw(12) << "$" << setw(10) << loanAmount << endl;
	cout << "Monthly Interest Rate:" << setw(12) << monthRate << "%" << endl;
	cout << "Number of Payments:" << setw(15) << numPayment << endl;
	cout << "Monthly Payment:" << setw(8) << "$" << setw(10) << monthPayment << endl;
	cout << "Amount Paid Back:" << setw(7) << "$" << setw(10) << totalPaid << endl;
	cout << "Interest Paid:" << setw(10) << "$" << setw(10) << totalInterest << endl;
	return 0;
}

/*
Richard Burke

Enter the loan amount:             10000.00
Enter the annual interest rate:    10.5
Enter the number of payments made: 48
Enter the customer's name          Minnie Mouse

Welcome Minnie Mouse.
Here is your loan information:
Loan Amount:           $  10000.00
Monthly Interest Rate:        0.88%
Number of Payments:             48
Monthly Payment:       $    256.03
Amount Paid Back:      $  12289.62
Interest Paid:         $   2289.62
Press any key to continue . . .

Richard Burke

Enter the loan amount:             123456.78
Enter the annual interest rate:    3.7
Enter the number of payments made: 128
Enter the customer's name          Winnie the Pooh

Welcome Winnie the Pooh.
Here is your loan information:
Loan Amount:           $ 123456.78
Monthly Interest Rate:        0.31%
Number of Payments:            128
Monthly Payment:       $   1168.79
Amount Paid Back:      $ 149605.05
Interest Paid:         $  26148.27
Press any key to continue . . .
*/