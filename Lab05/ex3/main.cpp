#include<iostream>
using std::cout;
using std::endl;

// debug: find that i == 1 or i == num, num % i == 0
// is wrong for an algoritm to check prime number

// naive approach to see if num is a prime number
bool isPrime( int num ) {
	for( int i = 1; i <= num; ++ i )
		if( num % i == 0 )
			return false;
	return true;
}

int main() {
	int a = 23;
	cout << isPrime(a) << endl;
    return 0;
}
