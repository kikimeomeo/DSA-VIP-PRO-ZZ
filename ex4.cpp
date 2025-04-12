#include <iostream>
using namespace std;

int kilogram(int *w, int n, int days)
{
	int left = w[n - 1], right = 0, mid, max, sum, dem;
	for (int i = 0; i < n; ++i) right += w[i];
	int min = right;
	while (left <= right)
	{
		mid = (left + right) / 2;
		max = dem = 0;
		for (int i = 0; i < n;)
		{
			sum = 0;
			while (i < n && sum + w[i] <= mid) sum += w[i++];
			if (max < sum) max = sum;
			++dem;
		}
		if (dem > days) left = mid + 1;
		else
		{
			right = mid - 1;
			if (min > max) min = max;
		}
	}
	return min;
}

int main()
{
	int n, days;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> days;
	cout << kilogram(a, n, days);
	delete[] a;
	return 0;
}