#pragma once
#include"Public.h"

namespace search_sort {
	//	1.对有序数组的二分搜索(假定为递增数组)		O(log n)
	//	递归算法
	int binarySearch(int arr[], int i, int j, int val) {
		if (i > j)return -1;
		int mid = (i + j) / 2;
		if (arr[mid] == val) { return mid; }
		else if (arr[mid] > val) { return binarySearch(arr, i, mid - 1, val); }
		else { return binarySearch(arr, mid + 1, j, val); }
	}

	//	非递归算法
	int n_binarySearch(int arr[], int size, int val) {
		int i = 0;
		int j = size - 1;
		int mid = (i + j) / 2;

		while (i <= j) {
			mid = (i + j) / 2;
			if (arr[mid] == val) { return mid; }
			else if (arr[mid] < val) { i = mid + 1; }
			else { j = mid - 1; }

		}

		return -1;
	}

	void test_binarySearch() {
		int arr[] = { 1,2,3,4,5,6,7,8,9,10,12,23,45,67 };
		int size = sizeof(arr) / sizeof(arr[0]);

		int k = 7;

		cout << binarySearch(arr, 0, size - 1, k) << endl;
		cout << n_binarySearch(arr, size, k) << endl;

	}

	//	性能对比
	/*
					稳定		复杂度
		冒泡		1			O(n^2)
		插入		1			O(n^2)在较为有序时最有效
		选择		0			n^2
		希尔		0			n^1.3
	*/
	//	2.冒泡排序
	void bubbleSort(int arr[], int size) {
		/*
		主要是通过交换相邻元素的大小关系,每次都可以将极值放在合适的位置;
		稳定排序,不改变同样大小元素的位置;
		O(n^2)
		*/
		for (int i = size - 1; i > 1; --i) {
			for (int j = 0; j < i; ++j) {
				if (arr[j] > arr[j + 1]) {
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	void test_bubbleSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }
		for (int v : arr) { cout << v << " "; }
		cout << endl;

		int size = sizeof(arr) / sizeof(arr[0]);
		bubbleSort(arr, size);

		for (int v : arr) { cout << v << " "; }
		cout << endl;

	}


	//	3.选择排序
	void choiceSort(int arr[], int size) {
		/*
		本质就是将最值放在最前面;
		O(n^2);
		因为涉及到交换,所以不稳定;
		*/
		int min = 0;
		int k = 0;
		for (int i = 0; i < size; ++i) {
			min = arr[i];
			k = i;

			for (int j = i + 1; j < size; ++j) {
				if (arr[j] < min) {
					min = arr[j];
					k = j;
				}
			}

			if (i != k) {
				int temp = arr[i];
				arr[i] = arr[k];
				arr[k] = temp;
			}
		}

	}

	void test_choiceSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		choiceSort(arr, SIZE);

		for (int v : arr) { cout << v << " "; }
		cout << endl;

	}


	//	4.插入排序
	void insertSort(int arr[], int size) {
		/*
		就是选择一个合适的位置将最后一个元素的后一个元素插入;
		O(n^2);
		稳定排序;
		*/

		for (int i = 1; i < size; ++i) {
			int val = arr[i];
			int j = i - 1;
			for (; j >= 0; --j) {
				if (arr[j] <= val) { break; }
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = val;
		}

	}

	void test_insertSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		insertSort(arr, SIZE);

		for (int v : arr) { cout << v << " "; }
		cout << endl;
	}


	//	5.希尔排序
	void shellSort(int arr[], int size) {
		/*
			主要是针对插入排序进行的改进;
			稳定排序;
			O(n^1.3);
		*/

		for (int gap = size / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < size; ++i) {
				int val = arr[i];
				int j = i - gap;

				for (; j >= 0; j -= gap) {
					if (arr[j] <= val) { break; }
					arr[j + gap] = arr[j];
				}
				arr[j + gap] = val;
			}
		}
	}

	void test_shellSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		shellSort(arr, SIZE);

		for (int v : arr) { cout << v << " "; }
		cout << endl;
	}


	//	6.快速排序
	int Partation(int arr[], int i, int j) {
		int val = arr[i];
		while (i < j) {
			while (i < j && arr[j] >= val) { --j; }
			if (i < j) { arr[i] = arr[j]; ++i; }

			while (i < j && arr[i] <= val) { ++i; }
			if (i < j) { arr[j] = arr[i]; --j; }
		}

		arr[i] = val;
		return i;

	}

	void quickSort(int arr[], int begin, int end) {
		if (begin >= end) { return; }

		if (begin < end) {
			int pos = Partation(arr, begin, end);

			quickSort(arr, begin, pos - 1);
			quickSort(arr, pos + 1, end);
		}
	}

	void test_quickSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		quickSort(arr, 0, SIZE - 1);

		for (int v : arr) { cout << v << " "; }
		cout << endl;

	}


	//	7.归并排序
	void merge(int arr[], int l, int m, int r) {
		int* p = new int[r - l + 1];
		int idx = 0;
		int i = l;
		int j = m + 1;

		while (i <= m && j <= r) {
			if (arr[i] <= arr[j]) { p[idx++] = arr[i++]; }
			else { p[idx++] = arr[j++]; }
		}

		while (i <= m) { p[idx++] = arr[i++]; }
		while (j <= r) { p[idx++] = arr[j++]; }

		for (i = l, j = 0; i <= r; ++i, ++j) { arr[i] = p[j]; }
		delete[]p;

	}

	void mergeSort(int arr[], int begin, int end) {
		if (begin >= end) { return; }
		int mid = (begin + end) / 2;

		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);

		merge(arr, begin, mid, end);

	}

	void test_mergeSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		mergeSort(arr, 0, SIZE - 1);

		for (int v : arr) { cout << v << " "; }
		cout << endl;
	}


	//	8.堆排序

	/*
		1.从第一个非叶子节点开始,把二叉堆调整为大根堆;
		2.堆顶元素与末尾元素进行交换,0号位继续进行堆下沉调整;
	*/

	void siftDown(int arr[], int i, int size) {
		int val = arr[i];

		while (i < size / 2) {
			int child = 2 * i + 1;
			if (child + 1 < size && arr[child + 1] > arr[child]) { ++child; }
			if (arr[child] > val) {
				arr[i] = arr[child];
				i = child;
			}
			else { break; }
		}
		arr[i] = val;
	}

	void heapSort(int arr[], int size) {
		for (int i = (size - 2) / 2; i >= 0; --i) { siftDown(arr, i, size); }

		for (int n = size - 1; n > 0; --n) {
			int temp = arr[0];
			arr[0] = arr[n];
			arr[n] = temp;

			siftDown(arr, 0, n);
		}
	}

	void test_heapSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		heapSort(arr, SIZE);

		for (int v : arr) { cout << v << " "; }
		cout << endl;
	}


	//	9.桶排序

	void radixSort(int arr[], int size) {
		int maxData = arr[0];
		for (int i = 1; i < size; ++i) { if (maxData < abs(arr[i])) { maxData = abs(arr[i]); } }

		int len = to_string(maxData).size();

		vector<vector<int>>vecs;
		int mod = 10;
		int dev = 1;

		//	由每一位进行排序,逐步过滤;
		for (int i = 0; i < len; mod *= 10, dev *= 10, ++i) {
			vecs.resize(20);
			for (int j = 0; j < size; ++j) {
				int index = arr[j] % mod / dev + 10;
				vecs[index].push_back(arr[j]);
			}

			int idx = 0;
			for (auto vec : vecs) {
				for (int v : vec) { arr[idx++] = v; }
			}
			vecs.clear();
		}

	}

	void test_radixSort() {
		const int SIZE = 20;
		int arr[SIZE];
		srand(time(NULL));

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 100 + 1; }
		arr[9] = -19;
		arr[6] = -17;

		for (int v : arr) { cout << v << " "; }
		cout << endl;

		int size = sizeof(arr) / sizeof(arr[0]);
		radixSort(arr, size);

		for (int v : arr) { cout << v << " "; }
		cout << endl;
	}

	//	测试代码
	void test_searchSort() {
		test_binarySearch();
		test_bubbleSort();
		test_choiceSort();
		test_insertSort();
		test_shellSort();
		test_quickSort();
		test_mergeSort();
		test_heapSort();
		test_radixSort();
	}
}
