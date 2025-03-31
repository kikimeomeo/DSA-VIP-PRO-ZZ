#include <iostream>
using namespace std;

int RotateArr(int a[], int n)
{
	if (n <= 1) return a[n];
	int left = 0, right = n - 1, mid;
	while (a[mid] <= a[mid + 1])
	{
		mid = (left + right) / 2;
		if (a[mid] < a[0]) right = mid - 1;
		else left = mid + 1;
	}
	return a[mid + 1];
}

int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cout << RotateArr(a, n);
	delete[] a;
	return 0;
}