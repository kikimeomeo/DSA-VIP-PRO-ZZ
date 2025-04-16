#include <iostream>
using namespace std;

bool SumTwoElement(int a[], int n, int t)
{
	int *left = a, *right = a + n - 1;
	while (right != left)
	{
		if (*left + *right > t) --right;
		else if (*left + *right < t) ++left;
		else return 1;
	}
	return 0;
}

int main()
{
	int n, t;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> t;
	if (SumTwoElement(a, n, t)) cout << "YES";
	else cout << "NO";
	delete[] a;
	return 0;
}