#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void InputArr(int *&a, int &n, string file)
{
    ifstream is(file);
    if (!is)
    {
        cout << "Khong the mo file input";
        return;
    }
    is >> n;
    a = new int[n];
    for (int i = 0; i < n; ++i) is >> a[i];
    is.close();
}

void OutputArr(int *a, int n, string file)
{
    ofstream os(file);
    if (!os)
    {
        cout << "Khong the mo file output";
        return;
    }
    os << n << endl;
    for (int i = 0; i < n; ++i) os << a[i] << ' ';
    os.close();
}

int maxarr(int *a, int n)
{
    if (n < 1) return -1;
    int max = 0;
    for (int i = 1; i < n; ++i)
    {
        if (a[i] > a[max]) max = i;
    }
    return max;
}

int minarr(int *a, int n)
{
    if (n < 1) return -1;
    int min = 0;
    for (int i = 1; i < n; ++i) 
    {
        if (a[i] < a[min])min = i;
    }
    return min;
}

void BubbleSort(int *a, int n)
{
    for (int i = n - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
        }
    }
}

void InsertionSort(int *a, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) 
        {
            
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

void SelectionSort(int *a, int n)
{
    for (int i = 0; i < n - 1; ++i) swap(a[i + minarr(a + i, n - i)], a[i]);
}

void Heapify(int *a, int index, int n)
{
    int cha = index;
    if (index * 2 + 1 < n)
    {
        if (a[index * 2 + 1] > a[cha]) cha = index * 2 + 1;
    }
    if (index * 2 + 2 < n)
    {
        if (a[index * 2 + 2] > a[cha]) cha = index * 2 + 2;
    } 
    if (cha != index)
    {
        swap(a[cha], a[index]);
        Heapify(a, cha, n);
    }
}

void HeapSort(int *a, int n)
{
    for (int i = (n - 2) / 2; i >= 0; i--) Heapify(a, i, n);
    while (n - 1 > 0)
    {
        swap(a[n-- - 1], a[0]);
        Heapify(a, 0, n);
    }
}

void QuickSort(int *a, int left, int right)
{
    if (left >= right) return;
    int i = left - 1;
    for (int j = left; j < right; ++j) 
    {
        if (a[j] < a[right]) swap(a[++i], a[j]);
    }
    swap(a[++i], a[right]);
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}

void Merge(int *a, int low, int mid, int high)
{
    int n = high - low + 1;
    int *temp = new int[n];
    int j = low, k = mid + 1, i = 0;
    while (j <= mid && k <= high)
    {
        if (a[j] < a[k]) temp[i++] = a[j++];
        else temp[i++] = a[k++];
    }
    while (j <= mid) temp[i++] = a[j++];
    while (k <= high) temp[i++] = a[k++];
    for (int t = 0; t < n; ++t) a[t + low] = temp[t];
}

void MergeSort(int *a, int left, int right)
{
    if (left >= right) return;
    MergeSort(a, left, left + (right - left) / 2);
    MergeSort(a, left + (right - left) / 2 + 1, right);
    Merge(a, left, left + (right - left) / 2, right);
}

void CountingSort(int *a, int n)
{
    int n_pos = a[maxarr(a, n)] + 1;
    int* pos= new int[n_pos]{0};
    for (int i = 0; i < n; ++i) ++pos[a[i]];
    int j = 0;
    for (int i = 0; i < n_pos; ++i) while (pos[i] && j < n)
    {
        a[j++] = i;
        --pos[i];
    }
    delete[] pos;
}

void RadixSort(int *a, int n)
{
    int* temp = new int[n];
    int digits = 1, tenth = 10;
    for (int i = 0; i < n; ++i) while (a[i] >= tenth) 
    {
        tenth *= 10;
        ++digits;
    }
    tenth = 1;
    for (int i = 0; i < digits; ++i)
    {
        int count[10]{0}, pos[10]{0};
        for (int j = 0; j < n; ++j) ++count[a[j] / tenth % 10];
        for (int j = 1; j < 10; ++j) pos[j] = pos[j - 1] + count[j - 1];
        for (int j = 0; j < n; ++j) temp[pos[a[j] / tenth % 10]++] = a[j];
        for (int j = 0; j < n; ++j) a[j] = temp[j];
        tenth *= 10;
    }
    delete[] temp;
}

void ShakerSort(int *a, int n)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        for (int i = left; i < right; ++i) 
        {
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        }
        --right;
        for (int i = right - 1; i > left; --i)
        {
            if (a[i - 1] > a[i]) swap(a[i - 1], a[i]);
        }
        ++left;
    }
} 

void ShellSort(int *a, int n)
{
    int gap = n;
    while (gap > 1)
    {
        gap /= 2;
        for (int i = 0; i < n / 2; ++i)
        {
            if (a[i] > a[i + gap]) swap(a[i], a[i + gap]);
        }
    }
    InsertionSort(a, n);
}

void FlashSort(int *a, int n)
{
    if (n <= 1) return;
    int k = max(sqrt(n), 2);
    int *count = new int[k]{0}, *pos = new int[k]{0}, *temppos = new int[n], min = a[minarr(a, n)], max = a[maxarr(a, n)];
    for (int i = 0; i < n; ++i) ++count[(k - 1) * (a[i] - min) / (max - min)];
    for (int i = 1; i < k; ++i) pos[i] = pos[i - 1] + count[i - 1];
    for (int i = 0; i < k; ++i) temppos[i] = pos[i];
    for (int i = 0; i < n; ++i)
    {
        while (i < temppos[(k - 1) * (a[i] - min) / (max - min)] || i >= temppos[(k - 1) * (a[i] - min) / (max - min)] + count[(k - 1) * (a[i] - min) / (max - min)]) 
        {
            swap(a[i], a[pos[(k - 1) * (a[i] - min) / (max - min)]++]);
        }
    }
    for (int i = 0; i < k; ++i) InsertionSort(a + temppos[i], count[i]);
    delete[] count;
    delete[] pos;
    delete[] temppos;
}

int main(int N, char *A[])
{
    int *a, n;
    string thuattoan;
    if (strcmp(A[1], "-a") == 0) thuattoan = A[2];
    if (strcmp(A[3], "-i") == 0) InputArr(a, n, A[4]);
    if (thuattoan == "bubble-sort")
    {
        BubbleSort(a, n);
    }
    else if (thuattoan == "selection-sort")
    {
        SelectionSort(a, n);
    }
    else if (thuattoan == "insertion-sort")
    {
        InsertionSort(a, n);
    }
    else if (thuattoan == "heap-sort")
    {
        HeapSort(a, n);
    }
    else if (thuattoan == "quick-sort")
    {
        QuickSort(a, 0, n - 1);
    }
    else if (thuattoan == "merge-sort")
    {
        MergeSort(a, 0, n - 1);
    }
    else if (thuattoan == "counting-sort")
    {
        CountingSort(a, n);
    }
    else if (thuattoan == "radix-sort")
    {
        RadixSort(a, n);
    }
    else if (thuattoan == "shell-sort")
    {
        ShellSort(a, n);
    }
    else if (thuattoan == "flash-sort")
    {
        FlashSort(a, n);
    }
    else if (thuattoan == "shaker-sort")
    {
        ShakerSort(a, n);
    }
    if (strcmp(A[5], "-o") == 0) OutputArr(a, n, A[6]);
    delete[] a;
    return 0;
}