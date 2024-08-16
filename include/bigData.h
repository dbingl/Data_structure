#pragma once
#include"Public.h"

namespace big_data {
	/*
		查重、去重、top_k;
		map、set、queues;
	*/

	//	1.找到第一个、所有重复、统计重复次数、去重复、字符串次数统计(找到第一个不重复的)
	void test_findRe_1() {
		vector<int>vec;
		srand(time(NULL));
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_set<int>s1;

		for (auto v : vec) {
			auto it = s1.find(v);
			if (it == s1.end()) { s1.emplace(v); }
			else {
				cout << v;
				cout << endl;
				return;
			}
		}
	}

	void test_findRe_all() {
		vector<int>vec;
		srand(time(NULL));
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_map<int, int>m1;

		//	for (auto v : vec) { m1[v]++; }

		for (auto v : vec) {
			auto it = m1.find(v);
			if (it == m1.end()) { m1[v] = 1; }
			else { m1[v] += 1; }
		}

		//	对哈希表容器的遍历
		for (auto it = m1.begin(); it != m1.end(); ++it) {
			if (it->second > 1) { cout << "Key: " << it->first << endl; }
		}

	}

	void test_Re_num() {
		vector<int>vec;
		srand(time(NULL));
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_map<int, int>m1;

		//	for (auto v : vec) { m1[v]++; }

		for (auto v : vec) {
			auto it = m1.find(v);
			if (it == m1.end()) { m1[v] = 1; }
			else { m1[v] += 1; }
		}

		for (auto it = m1.begin(); it != m1.end(); ++it) { cout << "Key: " << it->first << ", Value: " << it->second << endl; }

	}

	void test_RemoveRe() {
		vector<int>vec;
		srand(time(NULL));
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_set<int>s1;

		for (auto v : vec) { s1.emplace(v); }
	}

	void string_Re() {
		string str = "qwertywer1342321dwgwdsdt";
		unordered_map<char, int>map1;

		for (auto c : str) { ++map1[c]; }
		for (auto c : str) {
			if (map1[c] == 1) {
				cout << c << endl;
				return;
			}
		}
		cout << endl;
	}

	//	2.top_k,heap,partation(灵活运用函数模板,function.algorithm)
	void minheap_k() {
		vector<int>vec;
		srand(time(NULL));
		int k = 10;
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }

		std::priority_queue<int, vector<int>, greater<int>>minheap;
		for (int i = 0; i < 10; ++i) { minheap.push(vec[i]); }

		for (auto v : vec) {
			if (v < minheap.top()) {
				minheap.pop();
				minheap.push(v);
			}
		}

		while (!minheap.empty()) {
			cout << minheap.top() << " ";
			minheap.pop();
		}
		cout << endl;
	}

	void maxheap_k() {
		vector<int>vec;
		srand(time(NULL));
		int k = 10;
		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }

		std::priority_queue<int, vector<int>, less<int>>maxheap;
		for (int i = 0; i < 10; ++i) { maxheap.push(vec[i]); }

		for (auto v : vec) {
			if (v > maxheap.top()) {
				maxheap.pop();
				maxheap.push(v);
			}
		}

		while (!maxheap.empty()) {
			cout << maxheap.top() << " ";
			maxheap.pop();
		}
		cout << endl;

	}

	void min_Re_k() {
		vector<int>vec;
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_map<int, int>m1;

		for (auto v : vec) { ++m1[v]; }
		using Type = pair<int, int>;
		using Comp = function<bool(Type, Type)>;

		std::priority_queue<Type, vector<Type>, Comp> minheap([](Type t1, Type t2) { return t1.second > t2.second; });

		int count = 0;
		for (auto it = m1.begin(); it != m1.end() && count < k; ++it, ++count) { minheap.push(*it); }

		for (auto& entry : m1) {
			if (entry.second < minheap.top().second) {
				minheap.pop();
				minheap.push(entry);
			}
		}

		while (!minheap.empty()) {
			Type t = minheap.top();
			cout << t.first << ": " << t.second << endl;
			minheap.pop();
		}
		cout << endl;
	}

	void max_Re_k() {
		vector<int>vec;
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < 10000; ++i) { vec.push_back(rand() % 10); }
		unordered_map<int, int>m1;

		for (auto v : vec) { ++m1[v]; }
		using Type = pair<int, int>;
		//	对于函数指针变量的利用
		using Comp = function<bool(Type, Type)>;

		std::priority_queue<Type, vector<Type>, Comp> maxheap([](Type t1, Type t2) { return t1.second < t2.second; });

		int count = 0;
		for (auto it = m1.begin(); it != m1.end() && count < k; ++it, ++count) { maxheap.push(*it); }

		for (auto& entry : m1) {
			if (entry.second < maxheap.top().second) {
				maxheap.pop();
				maxheap.push(entry);
			}
		}

		while (!maxheap.empty()) {
			Type t = maxheap.top();
			cout << t.first << ": " << t.second << endl;
			maxheap.pop();
		}
		cout << endl;

	}

	/*
	//	partation
	int Partition(int arr[], int begin, int end) {
		int i = begin;
		int j = end;
		int val = arr[i];

		while (i < j) {
			while (i < j && arr[j] >= val) { --j; }
			if (i < j) {
				arr[i] = arr[j];
				++i;
			}

			while (i < j && arr[i] < val) { ++i; }
			if (i < j) {
				arr[j] = arr[i];
				--j;
			}
		}

		arr[i] = val;
		return i;
	}

	void max_Ptop_k() {
		const int SIZE = 1000;
		int arr[SIZE];
		srand(time(NULL));
		int k = 10;
		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 10; }

		int size = sizeof(arr) / sizeof(arr[0]);
		int pos = size;
		cout << pos << endl;

		do {
			if (pos == size) { pos = ::Partation(arr, 0, size - 1); }
			else if (pos > k - 1) { pos = ::Partation(arr, 0, pos - 1); }
			else if (pos < k - 1) { pos = ::Partation(arr, 0, pos + 1); }

		} while (pos != k - 1);

		for (int i = 0; i < pos; ++i) { cout << pos << " "; }
		cout << endl;

	}
	*/

	//	使用函数模板或者比较器进行传递(使用algorithm本身具有的算法,自定义的lambda算法)
	/*
	//	1.比较器
	using Comp = std::function<bool(int, int)>;

	int Partition(int arr[], int begin, int end, Comp comp) {
		int i = begin;
		int j = end;
		int val = arr[i];

		while (i < j) {
			while (i < j && comp(arr[j], val)) { --j; }
			if (i < j) {
				arr[i] = arr[j];
				++i;
			}

			while (i < j && !comp(arr[i], val)) { ++i; }
			if (i < j) {
				arr[j] = arr[i];
				--j;
			}
		}

		arr[i] = val;
		return i;
	}

	void max_Ptop_k() {
		const int SIZE = 10000;
		int arr[SIZE];
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < SIZE; ++i) {
			arr[i] = rand() % 10000;
		}

		int size = SIZE - 1;
		int pos = size;


		Comp greaterThan = [](int a, int b) { return a < b; };
		do {
			if (pos == size) {
				pos = Partition(arr, 0, size - 1, greaterThan);
			}
			else if (pos > k - 1) {
				pos = Partition(arr, 0, pos - 1, greaterThan);
			}
			else if (pos < k - 1) {
				pos = Partition(arr, pos + 1, size - 1, greaterThan);
			}

		} while (pos != k - 1);

		cout << "前 " << k << " 大的元素：";
		for (int i = 0; i <= pos; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	// 2.函数模板lambda 表达式
	template<typename Compare>
	int Partition(int arr[], int begin, int end, Compare comp) {
		int i = begin;
		int j = end;
		int val = arr[i];

		while (i < j) {
			while (i < j && comp(arr[j], val)) { --j; }
			if (i < j) {
				arr[i] = arr[j];
				++i;
			}

			while (i < j && !comp(arr[i], val)) { ++i; }
			if (i < j) {
				arr[j] = arr[i];
				--j;
			}
		}

		arr[i] = val;
		return i;
	}

	void max_Ptop_k() {
		const int SIZE = 10000;
		int arr[SIZE];
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < SIZE; ++i) {
			arr[i] = rand() % 10;
		}

		int size = SIZE - 1;
		int pos = size;

		auto greaterThan = [](int a, int b) { return a > b; };
		do {
			if (pos == size) {
				pos = Partition(arr, 0, size - 1, greaterThan);
			}
			else if (pos > k - 1) {
				pos = Partition(arr, 0, pos - 1, greaterThan);
			}
			else if (pos < k - 1) {
				pos = Partition(arr, pos + 1, size - 1, greaterThan);
			}

		} while (pos != k - 1);

		cout << "前 " << k << " 大的元素：";
		for (int i = 0; i <= pos; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}


	4.普通方法
	int Partition(int arr[], int begin, int end) {
		int i = begin;
		int j = end;
		int val = arr[i];

		while (i < j) {
			while (i < j && arr[j] >= val) { --j; }
			if (i < j) {
				arr[i] = arr[j];
				++i;
			}

			while (i < j && arr[i] < val) { ++i; }
			if (i < j) {
				arr[j] = arr[i];
				--j;
			}
		}

		arr[i] = val;
		return i;
	}

	void max_Ptop_k() {
		const int SIZE = 10000;
		int arr[SIZE];
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < SIZE; ++i) { arr[i] = rand() % 10000; }

		int size = SIZE - 1;
		int pos = size;

		do {
			if (pos == size) { pos = Partition(arr, 0, pos); }
			else if (pos > k - 1) { pos = Partition(arr, 0, pos - 1); }
			else if (pos < k - 1) { pos = Partition(arr, pos + 1, size - 1); }
		} while (pos != k - 1);

		for (int i = 0; i <= pos; ++i) { cout << arr[i] << " "; }
		cout << endl;
	}

	*/

	//	使用algorithm算法模板
	template<typename Compare>
	int Partition(int arr[], int begin, int end, Compare comp) {
		int i = begin;
		int j = end;
		int val = arr[i];

		while (i < j) {
			while (i < j && comp(arr[j], val)) { --j; }
			if (i < j) {
				arr[i] = arr[j];
				++i;
			}

			while (i < j && !comp(arr[i], val)) { ++i; }
			if (i < j) {
				arr[j] = arr[i];
				--j;
			}
		}

		arr[i] = val;
		return i;
	}

	void max_Ptop_k() {
		const int SIZE = 10000;
		int arr[SIZE];
		srand(time(NULL));
		int k = 10;

		for (int i = 0; i < SIZE; ++i) {
			arr[i] = rand() % 10;
		}

		int size = SIZE - 1;
		int pos = size;

		do {
			if (pos == size) { pos = Partition(arr, 0, size - 1, std::less<int>()); }
			else if (pos > k - 1) { pos = Partition(arr, 0, pos - 1, std::less<int>()); }
			else if (pos < k - 1) { pos = Partition(arr, pos + 1, size - 1, std::less<int>()); }
		} while (pos != k - 1);

		cout << "前 " << k << " 大的元素：";
		for (int i = 0; i <= pos; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void test_bigData() {
		test_findRe_1();
		test_findRe_all();
		test_Re_num();
		test_RemoveRe();
		string_Re();

		minheap_k();
		maxheap_k();

		min_Re_k();
		max_Re_k();

		max_Ptop_k();
	}

}
