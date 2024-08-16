#pragma once
#include"Public.h"

namespace binary_search_tree {

	class BST {
	private:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, left_(nullptr)
				, right_(nullptr)
			{}

			int data_;
			Node* left_;
			Node* right_;
		};

		Node* root_;

	public:
		BST()
			:root_(nullptr)
		{}
		~BST() {}

	public:
		void insert(const int& val) { root_ = insert(root_, val); }

		bool query(const int& val) { return query(root_, val) != nullptr; }

		void remove(const int& val) { root_ = remove(root_, val); }

		int number() { return number(root_); }

		int high() { return levelNumb(root_); }

		void preOrder() {
			cout << "递归:前序遍历:";
			preOrder(root_);
			cout << endl;
		}
		void inOrder() {
			cout << "递归:中序遍历:";
			inOrder(root_);
			cout << endl;
		}
		void postOrder() {
			cout << "递归:后序遍历:";
			postOrder(root_);
			cout << endl;
		}
		void levelOrder() {
			cout << "递归:层序遍历:";
			int h = high();

			for (int i = 0; i < h; ++i) { levelOrder(root_, i); }
			cout << endl;
		}

	private:
		Node* insert(Node* node, const int& val) {
			if (node == nullptr) { return new Node(val); }
			if (val < node->data_) { node->left_ = insert(node->left_, val); }
			else if (val > node->data_) { node->right_ = insert(node->right_, val); }
			else { cout << "This element: " << val << "is replicated!"; }
			return node;
		}

		Node* query(Node* node, const int& val) {
			if (node == nullptr) { return nullptr; }
			if (val < node->data_) { return query(node->left_, val); }
			else if (val > node->data_) { return query(node->right_, val); }
			else { return node; }
		}

		Node* remove(Node* node, const int& val) {
			if (node == nullptr) {
				return node;
			}

			if (val < node->data_) { node->left_ = remove(node->left_, val); }
			else if (val > node->data_) { node->right_ = remove(node->right_, val); }
			else {
				if (node->left_ != nullptr && node->right_ != nullptr) {
					Node* pre = node->left_;
					while (pre->right_ != nullptr) { pre = pre->right_; }
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);
				}
				else {	//	关键就是找到孩子节点
					if (node->left_ != nullptr) { node->data_ = node->left_->data_; delete node->left_; node->left_ = nullptr; }
					else if (node->right_ != nullptr) { node->data_ = node->right_->data_; delete node->right_; node->right_ = nullptr; }
					else { delete node; node = nullptr; }
				}
			}
			return node;
		}

		int number(Node* node) {
			if (node == nullptr) { return 0; }
			return number(node->left_) + number(node->right_) + 1;
		}

		int levelNumb(Node* node) {
			if (node == nullptr) { return 0; }
			return max(levelNumb(node->left_), levelNumb(node->right_)) + 1;
		}

		void preOrder(Node* node) {
			if (node == nullptr) { return; }
			cout << node->data_ << " ";
			preOrder(node->left_);
			preOrder(node->right_);
		}

		void inOrder(Node* node) {
			if (node == nullptr) { return; }
			inOrder(node->left_);
			cout << node->data_ << " ";
			inOrder(node->right_);
		}

		void postOrder(Node* node) {
			if (node == nullptr) { return; }
			postOrder(node->left_);
			postOrder(node->right_);
			cout << node->data_ << " ";
		}

		void levelOrder(Node* node, int h) {
			if (node == nullptr) { return; }
			if (h == 0) { cout << node->data_ << " "; return; }

			levelOrder(node->left_, h - 1);
			levelOrder(node->right_, h - 1);
		}


	public:	//	非递归方法
		void n_insert(const int& val) {
			cout << "非递归:插入:";
			if (root_ == nullptr) {
				root_ = new Node(val);
				return;
			}
			Node* pre = nullptr;
			Node* p = root_;

			while (p != nullptr) {

				if (val < p->data_) {
					pre = p;
					p = p->left_;
				}
				else if (val > p->data_) {
					pre = p;
					p = p->right_;
				}
				else {
					cout << "This element: " << val << " is replicated!";
					return;
				}
			}

			//	问题1.插入位置选取
			if (val < pre->data_) { pre->left_ = new Node(val); }
			else if (val > pre->data_) { pre->right_ = new Node(val); }

			return;

		}

		bool empty() { return root_ == nullptr; }

		bool n_query(const int& val)const {
			cout << "非递归:查询:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return false;
			}
			Node* p = root_;

			while (p != nullptr) {
				if (val < p->data_) { p = p->left_; }
				else if (val > p->data_) { p = p->right_; }
				else { return true; }
				if (p == nullptr) { return false; }
			}
		}

		void n_remove(const int& val) {
			cout << "非递归:删除:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return;
			}

			Node* pre = nullptr;
			Node* p = root_;

			while (p != nullptr) {
				if (val < p->data_) {
					pre = p;
					p = p->left_;
				}
				else if (val > p->data_) {
					pre = p;
					p = p->right_;
				}
				else { break; }
			}

			if (p == nullptr) {
				cout << "There not exit this element: " << val << endl;
				return;
			}

			if (p->left_ != nullptr && p->right_ != nullptr) {
				pre = p;
				Node* node = p->left_;
				while (node->right_ != nullptr) { pre = node; node = node->right_; }
				p->data_ = node->data_;
				p = node;
			}

			//	找到待删除节点与孩子节点,父亲节点;
			Node* child = p->left_;
			if (child == nullptr) { child = p->right_; }

			if (pre == nullptr) {
				root_ = child;
				delete p;
				p = nullptr;
			}
			else {
				if (pre->left_ == p) { pre->left_ = child; }
				else if (pre->right_ == p) { pre->right_ = child; }
				delete p;
				p = nullptr;
			}

			return;
		}

		void n_preOrder() {
			cout << "非递归:前序遍历:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return;
			}

			stack<Node*>s;
			queue<int>q;
			s.push(root_);

			while (!s.empty()) {
				Node* cur = s.top();
				s.pop();
				q.push(cur->data_);

				if (cur->right_ != nullptr) { s.push(cur->right_); }
				if (cur->left_ != nullptr) { s.push(cur->left_); }
			}

			while (!q.empty()) { cout << q.front() << " "; q.pop(); }	//	输出并且移除队首元素
			cout << endl;

			return;
		}

		void n_inOrder() {
			cout << "非递归:中序遍历:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return;
			}
			Node* p = root_;

			stack<Node*>s;
			queue<int>q;

			while (p != nullptr) {
				s.push(p);
				p = p->left_;
			}

			while (!s.empty()) {
				Node* cur = s.top();
				s.pop();

				q.push(cur->data_);
				if (cur->right_ != nullptr) {
					p = cur->right_;
					while (p != nullptr) {
						s.push(p);
						p = p->left_;
					}
				}
			}

			while (!q.empty()) { cout << q.front() << " "; q.pop(); }	//	输出并且移除队首元素
			cout << endl;

			return;

		}

		void n_postOrder() {
			cout << "非递归:后序遍历:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return;
			}

			stack<Node*>s;
			stack<int>qs;
			s.push(root_);

			while (!s.empty()) {
				Node* cur = s.top();
				s.pop();

				qs.push(cur->data_);
				if (cur->left_ != nullptr) { s.push(cur->left_); }
				if (cur->right_ != nullptr) { s.push(cur->right_); }
			}

			while (!qs.empty()) {
				cout << qs.top() << " ";
				qs.pop();
			}

			cout << endl;
		}

		void n_levelOrder() {
			cout << "非递归:层序遍历:";
			if (root_ == nullptr) {
				cout << "This BST is empty!" << endl;
				return;
			}

			queue<Node*>q;
			queue<int>qs;
			q.push(root_);

			while (!q.empty()) {
				Node* cur = q.front();
				q.pop();
				qs.push(cur->data_);

				if (cur->left_ != nullptr) { q.push(cur->left_); }
				if (cur->right_ != nullptr) { q.push(cur->right_); }
			}

			while (!qs.empty()) { cout << qs.front() << " "; qs.pop(); }	//	输出并且移除队首元素
			cout << endl;

			return;
		}


	};

	void test_BSTree() {
		int arr[] = { 12,34,13,44,8,35,9,87,76,90,43 };

		BST bst;

		for (int v : arr) { bst.n_insert(v); }
		for (int v : arr) { cout << v << ": " << bst.n_query(v) << endl; }

		bst.n_preOrder();
		bst.n_inOrder();
		bst.n_postOrder();
		bst.n_levelOrder();

		for (int v : arr) { bst.n_remove(v); }
		for (int v : arr) { cout << v << ": " << bst.n_query(v) << endl; }



		for (int v : arr) { bst.insert(v); }
		for (int v : arr) { cout << v << ": " << bst.query(v) << endl; }

		cout << "high:" << bst.high() << "\tnumb:" << bst.number() << endl;

		bst.preOrder();
		bst.inOrder();
		bst.postOrder();
		bst.levelOrder();

		for (int v : arr) { bst.remove(v); }
		for (int v : arr) { cout << v << ": " << bst.query(v) << endl; }
	}

}
