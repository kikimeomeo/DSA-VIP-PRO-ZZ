#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SumTriplets(int a[], int n)
{
    int printed[1000][3];
    int count = 0;
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 3; ++j) printed[i][j] = 1;
    }
    cout << '[';
    for (int i = 0; i < n - 2; ++i)
    {
        for (int j = i + 1; j < n - 1; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                if (a[i] + a[j] + a[k] == 0)
                {
                    int x = a[i], y = a[j], z = a[k];
                    if (x > y) swap(x, y);
                    if (y > z) swap(y, z);
                    if (x > y) swap(x, y);
                    bool tontai = 0;
                    for (int q = 0; q < count; ++q)
                    {
                        if (x == printed[q][0] && y == printed[q][1] && z == printed[q][2])
                        {
                            tontai = 1;
                            break;
                        }
                    }
                    if (!tontai)
                    {
                        cout << '[' << x << ',' << y << ',' << z << "]";
                        printed[count][0] = x;
                        printed[count][1] = y;
                        printed[count][2] = z;
                        ++count;
                    }
                }
            }
        }
    }
    cout << ']';
}

int main()
{
    int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
    SumTriplets(a, n);
	delete[] a;
	return 0;
}