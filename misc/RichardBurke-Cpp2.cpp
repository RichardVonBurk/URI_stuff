// Richard Burke
// Cpp-1
// This program calculates amount paid for stocks and displays it

#include <iostream>
using namespace std;

int main()
{
	//600shares, $21.77each, 2% percent		#1
	//750shares, $35.00each, 1.7% percent	#2

	//Variable holds and values, Use float to avoid integer+float problem

	float	paid4stock,	//hold
			commission,	
			totalPaid,
			shares,
			each,
			percent;

		shares = 750;		//Number of Shares
		each = 35.00;		//Price of each Share
		percent = 0.017;	//Percent value of Commission cost
		  

	//Calulate

	paid4stock = shares * each;

	commission = paid4stock * percent;
	
	totalPaid = paid4stock + commission;


	//Printing
	cout << "Richard Burke" << endl;	
	
	cout << endl << "Paid for Stock:  $" << paid4stock << endl;

	cout << "Commission:  $" << commission << endl;

	cout << "Total Amount Paid:  $" << totalPaid << endl;

	return 0;

}

/*
Richard Burke

Paid for Stock:  $13062
Commission:  $13323.2
Total Amount Paid:  $26385.2
Press any key to continue . . .



Richard Burke

Paid for Stock:  $26250
Commission:  $446.25
Total Amount Paid:  $26696.3
Press any key to continue . . .




*/