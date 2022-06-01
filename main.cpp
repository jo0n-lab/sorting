#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
#include "sort.h"
using namespace std;
int main(int argc, char *argv[])
{
	int T = atoi(argv[1]); // number of testcases
	cout << "T=" << T << endl;
	int N;			  // the number of testcase
	int i;			  // iterator
	double result[4]; // estimated time stored here
	struct timeval start_t, end_t;
	double diff_t;
	if (argc < 3)
	{
		cerr << "wrong argument count" << endl;
		return 1;
	}
	cout << "--INS--|--QUICK--|--NATMG--|--HEAP--|" << endl;
	for (i = 2; i < T + 2; i++)
	{

		// read data : N
		fstream fin(argv[i]);
		fin >> N;
		int *data = new int[N];
		for (int j = 0; j < N; j++)
			fin >> data[j];
		fin.close();

		// Insertion sort
		gettimeofday(&start_t, NULL);
		InsertionSort(data, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) +
				 ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[0] = diff_t;
		// quicksort
		gettimeofday(&start_t, NULL);
		QuickSort(data, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) +
				 ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[1] = diff_t;
		// Natural Merge sort
		gettimeofday(&start_t, NULL);
		NMergeSort(data, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) +
				 ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[2] = diff_t;
		// Heapsort
		gettimeofday(&start_t, NULL);
		HeapSort(data, N);
		gettimeofday(&end_t, NULL);
		diff_t = (double)(end_t.tv_sec - start_t.tv_sec) +
				 ((double)(end_t.tv_usec - start_t.tv_usec) / 1000000);
		result[3] = diff_t;

		delete[] data;

		// significant digits at 5
		cout.precision(5);
		cout << fixed;
		for (int j = 0; j < 4; j++)
		{
			cout << result[j] << "|";
		}
		cout << "N=" << N << endl;
	}
}
