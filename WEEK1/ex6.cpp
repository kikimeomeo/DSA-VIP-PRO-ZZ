#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector <int> hau;
int N, dem = 0;

bool safe(int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		if (hau[i] == col || abs(hau[i] - col) == abs(i - row)) return 0;
	}
	return 1;
}

void solve(int row)
{
	if (row == N)
	{
		++dem;
		return;
	}
	for (int col = 0; col < N; ++col)
	{
		if (safe(row, col))
		{
			hau[row] = col;
			solve(row + 1);
		}
	}
}

int main()
{
	cin >> N;
	hau.resize(N);
	solve(0);
	cout << "So cach xep la " << dem;
	return 0;
}
