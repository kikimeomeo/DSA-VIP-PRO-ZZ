#include <iostream>
using namespace std;

bool CheckArrSort(int a[], int n)
{
	if (n == 0 || n == 1) return 1;
	if (a[0] > a[1]) return 0;
	return CheckArrSort(a + 1, n - 1);
}

int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	if (CheckArrSort(a, n)) cout << "Mang da duoc sap xep theo thu tu tang dan";
	else cout << "Mang chua duoc sap xep theo thu tu tang dan";
	delete[] a;
	return 0;
}