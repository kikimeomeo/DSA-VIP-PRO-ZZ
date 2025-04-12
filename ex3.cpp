#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str)
{
	if (n == str.length())
	{
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n, str + "0");
	generateBinaryStrings(n, str + "1");
}

int main()
{
	string str;
	int n;
	cin >> n;
	generateBinaryStrings(n, str);
	return 0;
}