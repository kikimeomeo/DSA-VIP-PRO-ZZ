#include <iostream>
using namespace std;

int Factorial(int n)
{
	if (n == 0 || n == 1) return 1;
	return Factorial(n - 1) * n;
}