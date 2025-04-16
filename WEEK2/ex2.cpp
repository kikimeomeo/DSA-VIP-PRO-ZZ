#include <iostream>
using namespace std;

int LinearSearchWithSentinel(int a[], int n, int k)
{
	a[n] = k;
	int i = 0;
	while (a[i] != k) ++i;
	if (i < n) return i;
	return -1;
}

int main()
{
	int n, k;
	cin >> n;
	int *a = new int[n + 1];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> k;
	cout << LinearSearchWithSentinel(a, n, k);
	delete[] a;
	return 0;
}