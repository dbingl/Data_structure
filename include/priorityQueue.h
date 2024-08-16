#pragma once
#include"Public.h"

namespace priority_queue {
	//	优先队列实现

	class PriorityQueue {
	public:
		using Comp = function<bool(int, int)>;

		PriorityQueue(Comp comp)
			:size_(0)
			, cap_(20)
			, comp_(comp)
		{
			pQue_ = new int[cap_];
		}

		PriorityQueue(int cap = 20, Comp comp = greater<int>())
			:size_(0)
			, cap_(cap)
			, comp_(comp)
		{
			pQue_ = new int[cap_];
		}

		~PriorityQueue()
		{
			delete[]pQue_;
			pQue_ = nullptr;
		}


	private:
		int* pQue_;
		int size_;
		int cap_;

		Comp comp_;

	public:
		bool empty()const { return size_ == 0; }

		int top()const { return pQue_[0]; }

		int size()const { return size_; }

		void push(int val) {
			if (size_ == cap_) { expand(); }

			if (size_ == 0) { pQue_[size_] = val; }
			else { siftUp(size_, val); }
			++size_;
		}

		void pop() {
			if (size_ == 0) { throw "container is empty!"; }
			--size_;
			if (size_ > 0) { siftDown(0, pQue_[size_]); }
		}

	private:
		void expand() {
			int* p = new int[2 * cap_];
			for (int i = 0; i < cap_; ++i) { p[i] = pQue_[i]; }
			delete[]pQue_;
			pQue_ = p;
			cap_ *= 2;
		}

		void siftUp(int i, int val) {
			while (i > 0) {
				int father = (i - 1) / 2;
				if (comp_(val, pQue_[father])) {
					pQue_[i] = pQue_[father];
					i = father;
				}
				else { break; }
			}
			pQue_[i] = val;

		}

		void siftDown(int i, int val) {
			while (i < size_ / 2) {
				int child = 2 * i + 1;
				if (child + 1 < size_ && comp_(pQue_[child + 1], pQue_[child])) { ++child; }

				if (comp_(pQue_[child], val)) {
					pQue_[i] = pQue_[child];
					i = child;
				}
				else { break; }
			}
			pQue_[i] = val;

		}


	};


	void test_priorityQueue() {
		PriorityQueue que;
		srand(time(NULL));

		for (int i = 0; i < 10; ++i) { que.push(rand() % 100); }
		while (!que.empty()) { cout << que.top() << " "; que.pop(); }
		cout << endl;

		PriorityQueue m_que([](int a, int b) {return a < b; });
		srand(time(NULL));

		for (int i = 0; i < 10; ++i) { m_que.push(rand() % 100); }
		while (!m_que.empty()) { cout << m_que.top() << " "; m_que.pop(); }
		cout << endl;
	}

}
