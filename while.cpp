#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void Slectionsort(int *a, int n);

void inputarr(string file, int *arr, int &n)
{
    ifstream is(file);
    if (!is)
    {
        cout << "";
        return;
    }
    is.close();
}

void outputarr(string file, int *arr, int &n)
{
    ofstream os(file);
    for (int i = 0; i < n; ++i) os << arr[i] << ' ';
    os.close();
}

int main(int n, char *a[]) 
{
    string thuattoan, i, o;
    if (strcmp(a[1], "-a") == 0) thuattoan = a[2];
    if (strcmp(a[3], "-i") == 0) i = a[4];
    if (strcmp(a[5], "-a") == 0) o = a[6];
    int n, *arr;
    inputarr(i, arr, n);
    if (thuattoan == "Slectionsort") Slectionsort;
    else ();
    outputarr(o, arr, n);
    return 0;
}
