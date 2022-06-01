#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <iomanip>
using namespace std;
template <class T>
int verify(T *sorted, const int n)
{ // verifies function of sorting
	// return number of data sorted (until break point)
	int i = 0;
	int *broken;
	int size = 0;
	while (i < n - 1)
	{
		if (sorted[i] > sorted[i + 1])
			broken[size++] = i + 1;
		i++;
	}
	if (size)
	{
		cout << "the number of broken parts : " << size << endl;
		for (int i = 0; i < size; i++)
			cout << i << "st index : " << sorted[broken[i]] << endl;
		return broken[0]; // the break point (where problem occured)
	}
	else
		return n;
}
// copy input data to preserve the original
template <class T>
void Insert(const T &e, T *a, int i)
{
	a[0] = e;
	while (e < a[i])
	{ // until appropriate position
		// move forward
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}
template <class T>
void InsertionSort(T *data, const int n)
{
	T *a = new int[n + 1];
	a[0] = 0;
	copy(data, data + n, a + 1); // copy input data to preserve the original
	for (int j = 2; j <= n; j++)
	{
		T temp = a[j];			// move to rightward
		Insert(temp, a, j - 1); // time complex : O(j)
	}
	// int check=verify(a,n);
	// cout<<setw(8)<<check;
	delete[] a; // must return memory
				// without this : be disaster if N be greater...
}
template <class T>
void QuickSort(T *a, const int left, const int right)
{
	// ignore performance gap comes from iterative and recursive system
	if (left < right)
	{												  // until left==right
		int i = left, j = right + 1, pivot = a[left]; // pivot be the leftmost value
		do
		{
			do
				i++;
			while (a[i] < pivot);
			do
				j--;
			while (a[j] > pivot);
			if (i < j)
				swap(a[i], a[j]); // coloring areas gray
		} while (i < j);
		swap(a[left], a[j]);
		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right); // sort right area after left done
	}
}
template <class T>
void QuickSort(T *data, const int n)
{
	// separate driver to preserve data and verify performance
	T *a = new int[n];
	copy(data, data + n, a);
	QuickSort(a, 0, n - 1);
	// int check=verify(a,n);
	// cout<<setw(8)<<check;
	delete[] a;
}
template <class T>
void Merge(T *initList, T *mergedList, const int l, const int m, const int n)
{ // mergedList be continuously appended from initList(source of sublists)
	// merge lists where 'l to m' and 'm+1 to n' (sorted)
	int i1, iResult, i2;
	// same method: "polynomial::add" in chap.2 (**)
	for (i1 = l, iResult = l, i2 = m + 1;
		 i1 <= m && i2 <= n;
		 iResult++)
	{ // appending process
		// 'minor of (right, left)' to current pos
		if (initList[i1] <= initList[i2])
		{
			mergedList[iResult] = initList[i1];
			i1++;
		}
		else
		{
			mergedList[iResult] = initList[i2];
			i2++;
		}
	}
	// when : i1<=m||i2<=n
	copy(initList + i1, initList + m + 1, mergedList + iResult);
	copy(initList + i2, initList + n + 1, mergedList + iResult);
}
// Natural Merge Sort
template <class T>
void NMergePass(T *initList, T *resultList, const int n, int *length, int size)
// *length: lengths of sorted sublists stored
{
	Merge(initList, resultList, 0, length[0], length[1]);
	// merge two of adjacent sublists have "size"
	for (int i = 1; i < size - 2; i += 2)
		Merge(initList, resultList, length[i] + 1, length[i + 1], length[i + 2]);
}
template <class T>
void NMergeSort(T *data, const int n)
{
	T *a = new int[n];
	copy(data, data + n, a);
	T *tempList = new T[n + 1];
	int length[n]; // storing lengths of sublists
	fill(length, length + n + 1, 0);
	int pos = 0;
	int size; // size of *length
	for (size = 0; pos < n; size++)
	{ // new sublist (the very first)
		while (a[pos] <= a[pos + 1] && pos < n - 1)
			pos++; // until sorted preserved
		length[size] = pos;
		pos++;
	}
	while (size > 1)
	{ // do until length of merged sublist == 1
		NMergePass(a, tempList, n, length, size);
		// update *length
		for (int i = 0; i < size / 2; i++)
			length[i] = length[2 * i + 1]; // length of merged list be that of rightmost
		// preserve rightmost pos of last level when its size%2==0
		if (size % 2)
			length[size / 2] = length[size - 1];
		size = (size + 1) / 2;
		NMergePass(tempList, a, n, length, size);
	}
	// int check=verify(a,n);
	// cout<<setw(8)<<check;
	delete[] tempList;
	delete[] a;
}
template <class T>
void Adjust(T *a, const int root, const int n)
{ // n : number of left records be sorted
	// max heap processing
	T e = a[root];
	int j;
	for (j = 2 * root; j <= n; j *= 2)
	{ // j*2 : parent of j
		if (j < n && a[j] < a[j + 1])
			j++; // priority between siblings
		if (e >= a[j])
			break; // where appropriate pos
		a[j / 2] = a[j];
	}
	a[j / 2] = e;
}
template <class T>
void HeapSort(T *data, const int n)
{
	T *a = new int[n + 1];
	a[0] = 0;
	copy(data, data + n, a + 1);
	for (int i = n / 2; i >= 1; i--)
		Adjust(a, i, n); // the first max heap
	for (int i = n - 1; i >= 1; i--)
	{
		// swap(last pos, roor) after max heap made and reprocess max heap
		swap(a[1], a[i + 1]);
		Adjust(a, 1, i);
	}
	// int check=verify(a,n);
	// cout<<setw(8)<<check;
	delete[] a;
}
#endif
/* **Fundamentals of Data Structures in C++, Horowitz** */
