#pragma once
#include"Public.h"

namespace linear_table {
	//	1.线性表
	/*

		(1)Array	动态数组
		特点:内存连续、对内存要求高;有|无序搜索		push_back pop_back insert erase size capacity full empty expand find show
		优点:
			随机访问、末尾插入、相邻元素访问;
		缺点:
			扩容、非末尾插入;

		(2)List		链表(单、单向循环、双、双向循环)
		特点:节点new出来、节点不连续、更好利用内存、数据|地址域;
		优点:
			不需要扩容、插入删除、内存利用;
		缺点:
			内存占用大、不能随机访问|搜索效率不高;

		(3)Stack(依赖于数组、链表)								顺序、链式
		特点:先进后出;									在规定位置插入删除;

		(4)Queue(依赖于数组、链表):								环形,链式
		特点:先进先出

	*/

	//	1.1Array
	class Array {
	private:
		int* mpArr_;
		int mCap_;
		int mCur_;

		void expand() {
			int* ptemp = new int[2 * mCap_];
			memcpy(ptemp, mpArr_, sizeof(int) * mCap_);
			delete[]mpArr_;
			mpArr_ = ptemp;
			ptemp = nullptr;	//	防止临时变量析构导致内存崩溃
		}

	public:
		Array(int size = 10)
			:mCap_(size)
			, mCur_(0)
		{
			mpArr_ = new int[mCap_];
		}
		~Array() { delete[]mpArr_; }

	public:
		void push_back(const int val) {
			if (full()) { expand(); }
			mpArr_[mCur_++] = val;
		}

		void pop_back() { --mCur_; }

		void insert(int pos, int val) {
			if (pos<0 || pos>mCur_) { return; }
			if (full())expand();
			for (int i = mCur_ - 1; i > pos - 1; --i) { mpArr_[i + 1] = mpArr_[i]; }
			mpArr_[pos] = val;
			mCur_++;
		}

		void erase(int pos) {
			if (empty() || pos<0 || pos>mCur_) return;
			for (int i = pos; i < mCur_ - 1; ++i) { mpArr_[i] = mpArr_[i + 1]; }
			mCur_--;
		}

		bool size()const { return mCur_; }
		bool capacity()const { return mCap_; }

		void show()const {
			for (int i = 0; i < mCur_; ++i) {
				cout << mpArr_[i] << "\t";
			}
			cout << endl;
		}

		bool full()const { return mCur_ == mCap_; }

		bool empty()const { return mCur_ == 0; }

		int find(const int val) {
			for (int i = 0; i < mCur_; ++i) {
				if (mpArr_[i] == val) { return i; }
			}
		}
	};

	void test_arr() {
		Array arr;
		for (int i = 0; i < 15; ++i) {
			arr.push_back(i);
		}
		arr.show();
		arr.erase(10);
		arr.erase(1);
		arr.show();

		arr.pop_back();
		arr.show();
	}

	//	1.2SingleList
	class SingleList {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, next_(nullptr)
			{}

			int data_;
			Node* next_;

		};

	private:
		Node* head_;
		int size_;

	public:
		SingleList(int size = 0)
			:head_(new Node())	//	带有参数
			, size_(size)
		{}
		~SingleList() {
			Node* p = head_;
			while (p != nullptr) {
				head_ = head_->next_;
				delete p;
				p = head_;
			}
		}

	public:
		void HeadInsert(const int val) {
			Node* node = new Node(val);
			node->next_ = head_->next_;
			head_->next_ = node;

			++size_;
		}

		void TailInsert(const int val) {
			Node* node = new Node(val);
			Node* p = head_;
			while (p->next_ != nullptr) { p = p->next_; }
			p->next_ = node;

			++size_;
		}

		void remove(const int val) {
			Node* p = head_;
			Node* pre = nullptr;
			while (p->next_ != nullptr) {
				pre = p;
				p = p->next_;
				if (p->data_ == val) { break; }
			}
			if (p->next_ != nullptr) {
				pre->next_ = p->next_;
				delete p;

				--size_;
			}
			return;
		}

		void removeAll(const int val) {
			Node* p = head_;
			Node* pre = nullptr;
			while (p->next_ != nullptr) {
				pre = p;
				p = p->next_;
				if (p->data_ == val) {
					pre->next_ = p->next_;
					delete p;
					p = pre;

					--size_;
				}
			}
			return;
		}

		bool find(const int val)const {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				if (p->data_ == val) { return true; }
			}
			return false;
		}

		void show()const {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				cout << p->data_ << " ";
			}
			cout << endl;
		}

		bool empty()const { return size_ == 0; }

		int size()const { return size_; }

	};

	void test_SingleList() {
		SingleList sl;
		for (int i = 0; i < 15; ++i) {
			sl.TailInsert(i);
		}
		sl.remove(5);
		sl.remove(10);
		sl.remove(9);

		sl.show();
		cout << sl.size() << endl;
	}

	//	1.3DoubleList
	class DoubleList {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, pre_(nullptr)
				, next_(nullptr)
			{}

			int data_;
			Node* pre_;
			Node* next_;
		};

	private:
		int size_;
		Node* head_;

	public:
		DoubleList()
			:head_(new Node())
			, size_(0)
		{}
		~DoubleList() {
			Node* p = head_;
			while (p != nullptr) {
				head_ = head_->next_;
				delete p;
				p = head_;
			}
		}

	public:
		void HeadInsert(const int val) {
			Node* p = new Node(val);

			p->next_ = head_->next_;
			p->pre_ = head_;
			if (!empty()) { p->next_->pre_ = p; }	//	这一步比较关键
			p->pre_->next_ = p;

			++size_;
		}

		void TailInsert(const int val) {
			Node* node = new Node(val);

			Node* p = head_;
			while (p->next_ != nullptr) { p = p->next_; }
			node->next_ = p->next_;
			node->pre_ = p;
			node->pre_->next_ = node;

			++size_;
		}

		void remove(const int val) {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				if (p->data_ == val) { break; }
			}
			if (p->next_ != nullptr) {
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				delete p;
				p = nullptr;

				--size_;
			}

			return;
		}

		void removeAll(const int val) {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				if (p->data_ == val) {
					Node* pre = p->pre_;
					p->pre_->next_ = p->next_;
					p->next_->pre_ = p->pre_;
					delete p;
					p = pre;

					--size_;
				}
			}

			return;
		}

		bool find(const int val)const {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				if (p->data_ == val) { return true; }
			}
			return false;
		}

		bool empty()const { return size_ == 0; }

		int size()const { return size_; }

		void show()const {
			Node* p = head_;
			while (p->next_ != nullptr) {
				p = p->next_;
				cout << p->data_ << " ";
			}
			cout << endl;
		}

	};

	void test_DoubleList() {
		DoubleList dl;
		for (int i = 0; i < 15; ++i) {
			dl.TailInsert(i);
		}
		dl.remove(5);
		dl.remove(10);
		dl.remove(9);

		dl.show();
		cout << dl.size() << endl;
	}

	//	1.4SingleCircularList
	class SingleCircularList {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, next_(nullptr)
			{}

			int data_;
			Node* next_;
		};

	private:
		Node* head_;
		Node* tail_;
		int size_;

	public:
		SingleCircularList() {
			head_ = new Node();
			head_->next_ = head_;
			tail_ = head_;
		}
		~SingleCircularList() {
			Node* p = head_;
			while (p != tail_) {
				head_ = p->next_;
				delete p;
				p = head_;
			}

			delete p;
		}

	public:
		void HeadInsert(const int val) {
			Node* node = new Node(val);
			if (empty()) { tail_ = node; }
			node->next_ = head_->next_;
			head_->next_ = node;

			++size_;
		}

		void TailInsert(const int val) {
			Node* node = new Node(val);
			tail_->next_ = node;
			tail_ = tail_->next_;
			tail_->next_ = head_;

			++size_;
		}

		void remove(const int val) {
			Node* p = head_;
			Node* pre = nullptr;

			while (p->next_ != head_) {
				pre = p;
				p = p->next_;
				if (p->data_ == val) { break; }
			}

			if (p->next_ != head_) {
				pre->next_ = p->next_;
				delete p;
				p = nullptr;

				--size_;
			}
			return;
		}

		void removeAll(const int val) {
			Node* p = head_;
			Node* pre = nullptr;

			while (p->next_ != head_) {
				pre = p;
				p = p->next_;
				if (p->data_ == val) {
					pre->next_ = p->next_;
					delete p;
					p = pre;

					--size_;
				}
			}
			return;
		}

		int size()const { return size_; }

		bool find(const int val)const {
			Node* p = head_;
			while (p->next_ != head_) {
				p = p->next_;
				if (p->data_ == val) { return true; }
			}
			return false;
		}

		bool empty()const { return size_ == 0; }

		void show()const {
			Node* p = head_;
			while (p->next_ != head_) {
				p = p->next_;
				cout << p->data_ << " ";
			}
			cout << endl;
			return;
		}

	};

	void test_SingleCircularList() {
		SingleCircularList scl;

		for (int i = 0; i < 15; ++i) {
			scl.TailInsert(i);
		}
		scl.remove(5);
		scl.remove(10);
		scl.remove(9);

		scl.show();
		cout << scl.size() << endl;
	}

	//	1.5DoubleCircularList
	class DoubleCircularList {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, pre_(nullptr)
				, next_(nullptr)
			{}

			int data_;
			Node* pre_;
			Node* next_;
		};

	private:
		int size_;
		Node* head_;
		Node* tail_;

	public:
		DoubleCircularList()
			:size_(0)
			, head_(new Node())
			, tail_(head_)
		{
			head_->pre_ = head_;
			head_->next_ = head_;
		}
		~DoubleCircularList() {
			Node* p = head_;
			while (p != tail_) {
				head_ = p->next_;
				delete p;
				p = head_;
			}

			delete p;
		}

	public:
		void HeadInsert(const int val) {
			Node* node = new Node(val);
			if (empty()) { tail_ = node; }
			node->next_ = head_->next_;
			node->pre_ = head_;
			node->next_->pre_ = node;
			node->pre_->next_ = node;

			++size_;
		}

		void TailInsert(const int val) {
			Node* node = new Node(val);
			node->next_ = tail_->next_;
			node->pre_ = tail_;
			node->next_->pre_ = node;
			node->pre_->next_ = node;
			tail_ = tail_->next_;

			++size_;
		}

		void remove(const int val) {
			Node* p = head_;
			Node* pre = nullptr;

			while (p->next_ != head_) {
				pre = p;
				p = p->next_;
				if (p->data_ == val) {
					pre->next_ = p->next_;
					pre->next_->pre_ = pre;
					delete p;
					p = nullptr;

					--size_;
					return;
				}
			}

			return;
		}

		void removeAll(const int val) {
			Node* p = head_;
			Node* pre = nullptr;

			while (p->next_ != head_) {
				pre = p;
				p = p->next_;

				if (p->data_ == val) {
					pre->next_ = p->next_;
					pre->next_->pre_ = pre;
					delete p;
					p = pre;

					--size_;
				}
			}

			return;
		}

		int size()const { return size_; }

		bool find(const int val) {
			Node* p = head_;
			while (p->next_ != head_) {
				p = p->next_;
				if (p->data_ == val) { return true; }
			}

			return false;
		}

		bool empty()const { return head_ == tail_; }

		void show()const {
			Node* p = head_;
			while (p->next_ != head_) {
				p = p->next_;
				cout << p->data_ << " ";
			}
			cout << endl;
			return;
		}

	};

	void test_DoubleCircularList() {
		DoubleCircularList dcl;

		for (int i = 0; i < 15; ++i) {
			dcl.HeadInsert(i);
		}
		dcl.remove(5);
		dcl.remove(10);
		dcl.remove(9);

		dcl.show();
		cout << dcl.size() << endl;
	}

	//	1.6SeqStack
	class SeqStack {
	private:
		int top_;
		int cap_;
		int* pstack_;	//	指针永远就是8bytes在64bits下

		void expand() {
			int* ptmp = new int[2 * cap_];
			memcpy(ptmp, pstack_, sizeof(int) * cap_);
			delete pstack_;
			pstack_ = ptmp;
			cap_ = 2 * cap_;
		}

	public:
		SeqStack(int cap = 15)
			:cap_(cap)
			, top_(0)
		{
			pstack_ = new int[cap_];
		}
		~SeqStack() {
			delete[]pstack_;
			pstack_ = nullptr;
		}

	public:
		void push(const int val) {
			if (full()) { expand(); }
			pstack_[top_++] = val;
		}

		void pop() {
			if (top_ == 0) {
				cout << "This Stack is empty!" << endl;
				return;
			}
			--top_;
		}

		int top() { return pstack_[top_ - 1]; }

		int size()const { return top_; }

		bool full()const { return top_ == cap_; }

		bool empty()const { return top_ == 0; }

	};

	void test_SeqStack() {
		SeqStack sta;
		int arr[] = { 11,14,43,25,76,9,22,34,56,78 };
		for (int v : arr) { sta.push(v); }

		cout << sta.size() << endl;

		for (int i = sta.size(); i > 0; --i) {
			cout << sta.top() << " ";
			sta.pop();
		}
		cout << endl;
	}

	//	1.7ListStack
	class ListStack {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, next_(nullptr)
			{}

			int data_;
			Node* next_;
		};

	private:
		Node* head_;
		int size_;

	public:
		ListStack()
			:size_(0)
		{
			head_ = new Node();
		}
		~ListStack() {}

	public:
		void push(const int val) {
			Node* node = new Node(val);
			node->next_ = head_->next_;
			head_->next_ = node;
			++size_;
		}

		void pop() {
			if (empty()) { throw"Stack is empty!"; }
			Node* node = head_->next_;
			head_->next_ = node->next_;
			delete node;
			--size_;
		}

		int top()const {
			if (empty()) { throw"Stack is empty!"; }
			return head_->next_->data_;
		}

		bool empty()const { return head_->next_ == nullptr; }

		int size()const { return size_; }

	};

	void test_ListStack() {
		ListStack sta;
		int arr[] = { 11,14,43,25,76,9,22,34,56,78 };
		for (int v : arr) { sta.push(v); }

		cout << sta.size() << endl;

		for (int i = sta.size(); i > 0; --i) {
			cout << sta.top() << " ";
			sta.pop();
		}
		cout << endl;
	}

	//	1.8CircularQueue
	class CircularQueue {
	private:
		int* pQue_;
		int size_;
		int cap_;
		int _front;
		int _rear;

		void expand() {
			int* ptemp = new int[2 * cap_];

			int k = _front;
			for (int i = 0; k < _rear; ++i, ++k, k %= cap_) { ptemp[i] = pQue_[k]; }

			delete[]pQue_;
			pQue_ = ptemp;
			_front = 0;
			_rear = cap_ - 1;
			cap_ *= 2;
		}

	public:
		CircularQueue()
			:size_(0)
			, cap_(15)
			, _front(0)
			, _rear(0)
		{
			pQue_ = new int[cap_];
		}

		~CircularQueue() {
			delete[]pQue_;
			pQue_ = nullptr;
		}

	public:
		void push(const int val) {
			if (full()) { expand(); }
			pQue_[_rear] = val;
			++_rear;
			_rear %= cap_;
			++size_;
		}

		void pop() {
			if (empty()) { throw"This Queue is empty!"; }
			++_front;
			_front %= cap_;
			--size_;
		}

		int front()const {
			if (empty()) { throw"This Queue is empty!"; }
			return pQue_[_front];
		}

		int back()const {
			if (empty()) { throw"This Queue is empty!"; }
			return pQue_[_rear - 1];
		}

		bool empty()const { return _front == _rear; }
		bool full()const { return (_rear + 1) % cap_ == _front; }
		int size()const { return size_; }


	};

	void test_CircularQueue() {
		CircularQueue cq;
		int arr[] = { 11,14,43,25,76,9,22,34,56,78 };
		for (int v : arr) { cq.push(v); }

		cout << cq.size() << endl;

		for (int i = cq.size(); i > 0; --i) {
			cout << cq.front() << " ";
			cq.pop();
		}
		cout << endl;
	}

	//	1.9ListQueue
	class ListQueue {
	public:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, pre_(nullptr)
				, next_(nullptr)
			{}

			int data_;
			Node* pre_;
			Node* next_;
		};

	private:
		Node* head_;
		int size_;

	public:
		ListQueue()
			:size_(0)
		{
			head_ = new Node();
			head_->pre_ = head_;
			head_->next_ = head_;
		}
		~ListQueue() {
			Node* p = head_->next_;
			while (p != head_) {
				Node* node = p->next_;
				delete p;
				p = node;
			}
			delete head_;
		}

	public:
		void push(const int val) {
			Node* node = new Node(val);
			node->next_ = head_->next_;
			node->pre_ = head_;
			node->pre_->next_ = node;
			node->next_->pre_ = node;
			++size_;
		}

		void pop() {
			if (empty()) { throw"This queue is empty!"; }
			Node* p = head_->pre_;
			head_->pre_ = p->pre_;
			head_->pre_->next_ = head_;
			delete p;
			--size_;
		}

		int front()const {
			if (empty()) { throw"This queue is empty!"; }
			return head_->pre_->data_;
		}

		int back()const {
			if (empty()) { throw"This queue is empty!"; }
			return head_->next_->data_;
		}

		bool empty()const { return head_->next_ == head_; }
		int size()const { return size_; }

		//	1.两个栈实现一个队列
		//	1.两个队列实现一个栈
	};

	void test_ListQueue() {
		ListQueue lq;
		int arr[] = { 11,14,43,25,76,9,22,34,56,78 };
		for (int v : arr) { lq.push(v); }

		cout << lq.size() << endl;

		for (int i = lq.size(); i > 0; --i) {
			cout << lq.front() << " ";
			lq.pop();
		}
		cout << endl;
	}


	//	测试以上数据结构
	void test_linearTable() {
		test_arr();
		test_SingleList();
		test_DoubleList();
		test_SingleCircularList();
		test_DoubleCircularList();

		test_SeqStack();
		test_ListStack();

		test_CircularQueue();
		test_ListQueue();
	}

}
