#include <iostream>
using namespace std;

void HanoiTower(int n, char A, char B, char C)
{
	if (n == 1)
	{
		cout << A << "->" << C << endl;
		return;
	}
	HanoiTower(n - 1, A, C, B);
	cout << A << "->" << C << endl;
	HanoiTower(n - 1, B, A, C);
}
