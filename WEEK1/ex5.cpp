#include <iostream>
using namespace std;

bool CheckArrSort(int a[], int n)
{
	if (n == 0 || n == 1) return 1;
	if (a[0] > a[1]) return 0;
	return CheckArrSort(a + 1, n - 1);
}