#include <iostream>
using namespace std;

int MinLength(int a[], int n, int t)
{
	int sum = 0, left = 0, right, min;
	for (int i = 0; i < n; ++i) 
	{
		if (sum < t) 
		{
			sum += a[i];
			right = i;
		}
		else break;
	}
	if (sum < t) return 0;
	min = right + 1;
	while (right < n - 1)
	{
		sum += a[++right];
		while (sum - a[left] >= t) sum -= a[left++];
		if (min > right - left + 1) min = right - left + 1;
	}
	return min;
}

int main()
{
	int n, t;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> t;
	cout << MinLength(a, n, t);
	delete[] a;
	return 0;
}