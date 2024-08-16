#pragma once
#include"Public.h"

namespace hash_table {

	/*
	哈希表:解决查询问题(有序、无序);散列结果离散比较好;但是对内存占用大;
		散列函数进行映射;
			散列函数:
				直接定址、数字分析、平方取中、随机数、除留余数、md5|sha加密算法;
			冲突:
				线性、二次、链地址

	除留余数
		线性探测法:
			特点:
				哈希冲突:质数、装载因子(扩容)
				插入、删除、查询
			缺点:
				占用整块内存、哈希冲突导致效率O(n)、多线程不安全;
		链地址法:
			特点:
				通过在每个桶中设置独特的数据结构,进而解决哈希冲突;

			优点:
				效率高、充分利用内存、线程安全;

			优化:
				长度变大时,直接转化为rbt;
				分段锁,可以并发执行;
	*/

	//	1.1LinearHashTable
	class LinearHashTable {
	private:
		enum State {
			UNUSING,
			USED,
			DELETED
		};

		struct Bucket {
			Bucket(int data = 0, State state = UNUSING)
				:key_(data)
				, state_(state)
			{}

			int key_;
			State state_;
		};

		Bucket* table_;
		int tableSize_;
		int useBucketNum_;
		double loadFactor_;

		static const int PRIME_SIZE = 10;
		static int primes_[PRIME_SIZE];
		int primeIdx_;

		void expand() {
			++primeIdx_;
			if (primeIdx_ == PRIME_SIZE) { throw"HashTable is too large, can not expand anymore!"; }

			Bucket* newTable_ = new Bucket[primes_[primeIdx_]];

			for (int i = 0; i < tableSize_; ++i) {
				if (table_[i].state_ == USED) {
					int idx = table_[i].key_ % primes_[primeIdx_]; int k = idx;

					do {
						if (newTable_[k].state_ != USED) {
							newTable_[k].state_ = USED;
							newTable_[k].key_ = table_[i].key_;
							break;
						}
						k = (k + 1) % tableSize_;
					} while (k != idx);
				}
			}

			delete[]table_;
			table_ = newTable_;
			newTable_ = nullptr;
			tableSize_ = primes_[primeIdx_];
		}

	public:
		LinearHashTable(int size = primes_[0], double loadFactor = 0.75)
			:useBucketNum_(0)
			, loadFactor_(loadFactor)
			, primeIdx_(0)
		{
			if (size != primes_[0]) {
				for (; primeIdx_ < PRIME_SIZE; ++primeIdx_) {
					if (size < primes_[primeIdx_]) { break; }
				}
				if (primeIdx_ == PRIME_SIZE) { --primeIdx_; }
			}

			tableSize_ = primes_[primeIdx_];
			table_ = new Bucket[tableSize_];
		}
		~LinearHashTable() { delete[]table_; table_ = nullptr; }

	public:
		void insert(const int val) {
			loadFactor_ = useBucketNum_ * 1.0 / tableSize_;

			if (loadFactor_ > 0.75) { expand(); }

			int k = val % tableSize_;

			do {
				if (table_[k].state_ != USED) {
					table_[k].key_ = val;
					table_[k].state_ = USED;

					++useBucketNum_;

					loadFactor_ = useBucketNum_ * 1.0 / tableSize_;
					return;
				}
				else {
					++k;
					k %= tableSize_;
				}

			} while (k < val % tableSize_);

			cout << "There exits a error!" << endl;
		}

		void erase(const int val) {
			if (useBucketNum_ == 0) {
				cout << "This hashTable is empty!" << endl;
				return;
			}

			int k = val % tableSize_;

			do {
				if (table_[k].state_ == USED && table_[k].key_ == val) {
					table_[k].key_ = 0;
					table_[k].state_ = DELETED;

					--useBucketNum_;
					loadFactor_ = useBucketNum_ * 1.0 / tableSize_;
					return;
				}
				else if (table_[k].state_ == UNUSING) {
					cout << "There doesn't exit the element!" << endl;
					return;
				}
				else {
					++k;
					k %= tableSize_;
				}

			} while (k < val % tableSize_);

			cout << "There doesn't exit the element!" << endl;

			return;

		}

		bool find(const int val)const {
			int k = val % tableSize_;

			do {
				if (table_[k].state_ == UNUSING) { return false; }
				else if (table_[k].state_ == USED) { if (table_[k].key_ == val) { return true; } }
				else {
					++k;
					k %= tableSize_;
				}

			} while (k < val % tableSize_);

			return false;
		}

		int count(const int val)const {
			int count = 0;
			int k = val % tableSize_;

			do {
				if (table_[k].state_ == UNUSING) { return false; }
				else if (table_[k].state_ == USED) { if (table_[k].key_ == val) { ++count; } }
				else {
					++k;
					k %= tableSize_;
				}

			} while (k < val % tableSize_);

			return count;
		}


	};

	int LinearHashTable::primes_[PRIME_SIZE] = { 3, 23, 97, 467, 1153, 2971, 5501, 9949,  23251, 49999 };

	void test_linearHashTable() {
		LinearHashTable ht;

		for (int i = 0; i < 1000; ++i) { ht.insert(i); }

		cout << ht.find(3) << endl;

		cout << ht.count(5) << endl;

		for (int i = 0; i < 1000; ++i) { ht.erase(i); }
	}

	//	1.2ListHashTable
	class ListHashTable {
	private:
		vector<list<int>>table_;

		int useBucketNum_;
		double loadFactor_;

		static const int PRIME_SIZE = 10;
		static int primes_[PRIME_SIZE];	//	静态成员变量的初始化
		int primeIdx_;

		void expand() {
			if (primeIdx_ + 1 == PRIME_SIZE) { throw"hashtable can not expand anymore!"; }

			++primeIdx_;

			vector<list<int>>oldtable_;
			table_.swap(oldtable_);	//	交换容器的成员变量,空间配置器需要一样
			table_.resize(primes_[primeIdx_]);

			for (auto list : oldtable_) {
				for (auto val : list) {
					int k = val % table_.size();
					if (table_[k].empty()) { ++useBucketNum_; }
					table_[k].emplace_front(val);
				}
			}
		}

	public:
		ListHashTable(int size = primes_[0], double loadFactor = 0.75)
			:useBucketNum_(0)
			, loadFactor_(loadFactor)
			, primeIdx_(0)
		{
			if (size != primes_[0]) {
				for (; primeIdx_ < PRIME_SIZE; ++primeIdx_) {
					if (size < primes_[primeIdx_]) { break; }
				}
				if (primeIdx_ == PRIME_SIZE) { --primeIdx_; }
			}

			table_.resize(primes_[primeIdx_]);
		}
		~ListHashTable() {}	//	容器自动析构

	public:
		void insert(const int val) {
			loadFactor_ = useBucketNum_ * 1.0 / table_.size();

			if (loadFactor_ > 0.75) { expand(); }

			int k = val % table_.size();
			if (table_[k].empty()) {
				++useBucketNum_;
				table_[k].emplace_front(val);	//	头插
			}
			else {
				//	全局find方法,去掉重复;
				auto it = ::find(table_[k].begin(), table_[k].end(), val);
				if (it == table_[k].end()) {
					table_[k].emplace_front(val);
				}
			}

			loadFactor_ = useBucketNum_ * 1.0 / table_.size();

		}

		void erase(const int val) {
			int k = val % table_.size();

			auto it = ::find(table_[k].begin(), table_[k].end(), val);
			if (it == table_[k].end()) { return; }
			else {
				table_[k].erase(it);
				if (table_[k].empty()) { --useBucketNum_; }
			}

			loadFactor_ = useBucketNum_ * 1.0 / table_.size();
		}

		bool find(const int val)const {
			int k = val % table_.size();

			auto it = ::find(table_[k].begin(), table_[k].end(), val);
			return it != table_[k].end();
		}

	};

	int ListHashTable::primes_[PRIME_SIZE] = { 3, 23, 97, 467, 1153, 2971, 5501, 9949,  23251, 49999 };

	void test_listHashTable() {
		LinearHashTable ht;

		for (int i = 0; i < 1000; ++i) { ht.insert(i); }

		cout << ht.find(3) << endl;

		cout << ht.count(5) << endl;

		for (int i = 0; i < 1000; ++i) { ht.erase(i); }
	}

	void test_hashTable() {

		test_linearHashTable();
		test_listHashTable();

		return;
	}

}
