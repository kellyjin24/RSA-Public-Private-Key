/* Name: Kai Li Jin
 * Date: October 1, 2018
 * Description: This program employs the RSA algorithm to encrypt and decrypt messages using a public key and a private key.
 */

#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

int setModulus(int, int);
int gcd(int, int, int&, int&);
int relativePrime(int);
int inverse(int, int);
int encode(int, int, int);
int decode(int, int, int);
int rsa(int, int, int);
int modExponent(int, int, int);

int s, t;

int main() {

	int M = 0, P = 0, Q = 0; // Initialize

	cout << "Welcome to the RSA program! To begin, enter a message and it will encrypted, then decrypted in order ensure message confidentiality." << endl;

	cout << "Enter a message: ";
	cin >> M;

	cout << "Enter a P value: "; // Step 1A
	cin >> P;
	
	cout << "Enter a Q value: "; // Step 1B
	cin >> Q;

	int h = rsa(M, P, Q);
	cout << "After encryption and decryption, the message is: " << h << endl;

	return 0;
}

// Calculate modulo
int setModulus(int a, int b) {
	int m = 0, r = 0;
	
	if (a > 0) {
		m = a % b; // remainder when a is divided by n
	}

	else {
		r = a; // set the value of a to r;

		do {
			a = a + b; // continue adding n to the value of a, and update the new value of a, until a is positive

		} while (a < 0 );

		m = a;
	}

	return m;
}

// Extended Euclidean Algorithm
int gcd(int a, int b, int& s, int& t) {
	if (b == 0) {
		s = 1;
		t = 0;

		return a; // a = (a*s) + (b*t)
	}
	
	else {
		int q = a/b;
		int r = setModulus(a, b); 

		int s1, t1;

		int d = gcd(b, r, s1, t1);

		s = t1;
		t = s1 - (t1*q);

		return d;
	}
}

// Relative Prime
int relativePrime(int a) {

	for (int y = 3; y < a - 1; y++) {	
		if ((gcd(a, y, s, t)) == 1) {
			return y;
		}
	}
}

// Inverse modulo
int inverse(int a, int y) {
	int d = gcd(y, a, s, t);

	if (d == 1) {
		return setModulus(t, y);
	}

	else {
		return 0;

		//cout << a << " and " << b << " are NOT relative primes." << endl;
	}
}

// Function that calculates only the exponent result
int modExponent(int M, int d, int PQ) {

	if (d == 0) {
		return 1;
	}

	int result = modExponent(M, d/2, PQ); // Recursion

	if (d % 2 == 0) {
		return setModulus((result * result), PQ);
	}

	else {
		return setModulus((setModulus(result * result, PQ) * M), PQ);
	}
}

// Called by RSA function
int encode(int M, int d, int PQ) { // return M^d mod PQ
	return modExponent(M, d, PQ);
}

// Called by RSA function
int decode(int C, int e, int PQ) { // return C^e mod PQ
	return modExponent(C, e, PQ);
}

// RSA algorithm
int rsa(int M, int P, int Q) {
	int PQ = P * Q; // Step 2
	int l = (P - 1) * (Q - 1); // Step 3

	// Step 4
	int d = relativePrime(l); // d is relatively prime with (P - 1)(Q - 1)

	// Step 5
	int e = inverse(d, l); // e and d are inverse modulo of each other

	assert (setModulus((e * d), l) == 1);

	cout << "Calculating..." << endl;
	cout << "d = " << d << endl;
	cout << "e = " << e << endl;
	cout << "l = " << l << endl;
	cout << "...Done!" << endl;

	int C = encode(M, d, PQ);
	int M1 = decode(C, e, PQ);

	assert (M == M1);

	return M1;
}
