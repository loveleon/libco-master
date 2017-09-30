#include <iostream>
#include <string>
#include "co_routine.h"
using namespace std;

void A() {
	cout << "1"
	     << " ";
	cout << "2"
	     << " ";
	co_yield_ct();
	cout << "3"
	     << " ";
}

void B() {
	cout << "x"
	     << " ";
	co_yield_ct();
	cout << "y"
	     << " ";
	cout << "z"
	     << " ";
}

int main(int argc, char* argv[]) {
	 A();
	 B();
	//co_resume(A);
	//co_resume(B);
	//co_resume(A);
	//co_resume(B);

	cout << endl;
	return 0;
}