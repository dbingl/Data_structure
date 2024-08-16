#pragma once
#include"Public.h"

namespace avl {
	/*
	二叉平衡搜索树,
		左节点的左子树比右子树高:右旋转;
		左节点的右子树比左子树高:左平衡(左旋转+右旋转);

		右节点的右子树比左子树高:左旋转;
		右节点的左子树比右子树高:右平衡(右旋转+左旋转);

	*/

	class AVL {
	private:
		struct Node {
			Node(int data = 0)
				:data_(data)
				, height_(1)
				, left_(nullptr)
				, right_(nullptr)
			{}

			int data_;
			int height_;
			Node* left_;
			Node* right_;
		};

		Node* root_;

	public:
		AVL() { root_ = nullptr; }
		~AVL() {}

	public:
		void insert(const int& val) { root_ = insert(root_, val); }

		void remove(const int& val) { root_ = remove(root_, val); }

		int high()const { return high(root_); }


	public:

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


	private:
		int high(Node* node)const { return node == nullptr ? 0 : node->height_; }

		Node* rightRotate(Node* node) {
			Node* child = node->left_;
			node->left_ = child->right_;
			child->right_ = node;

			node->height_ = max(high(node->left_), high(node->right_)) + 1;
			child->height_ = max(high(child->left_), high(child->right_)) + 1;

			return child;
		}

		Node* leftRotate(Node* node) {
			Node* child = node->right_;
			node->right_ = child->left_;
			child->left_ = node;

			node->height_ = max(high(node->left_), high(node->right_)) + 1;
			child->height_ = max(high(child->left_), high(child->right_)) + 1;

			return child;
		}

		Node* leftBalance(Node* node) {
			Node* child = node->left_;
			child = leftRotate(child);
			node = rightRotate(node);

			return node;
		}

		Node* rightBalance(Node* node) {
			Node* child = node->right_;
			child = rightRotate(child);
			node = leftRotate(node);

			return node;
		}

		Node* insert(Node* node, const int& val) {
			//	考察递归以及回溯的功底
			if (node == nullptr) { return new Node(val); }

			if (val < node->data_) {
				node->left_ = insert(node->left_, val);
				//	再此进行回溯操作
				if (high(node->left_) - high(node->right_) > 1) {	//	左子树较高
					if (high(node->left_->left_) >= high(node->left_->right_)) {
						node = rightRotate(node);
					}
					else {
						node->left_ = leftRotate(node->left_);
						node = rightRotate(node);
					}
				}
			}
			else if (val > node->data_) {
				node->right_ = insert(node->right_, val);
				//	再此进行回溯操作
				if (high(node->right_) - high(node->left_) > 1) {	//	右子树较高
					if (high(node->right_->right_) >= high(node->right_->left_)) {
						node = leftRotate(node);
					}
					else {
						node->right_ = rightRotate(node->right_);
						node = leftRotate(node);
					}
				}
			}
			else { cout << "This element: " << val << "is replicated!" << endl; }
			//	再此进行回溯操作
			node->height_ = max(high(node->left_), high(node->right_)) + 1;

			return node;

		}

		Node* remove(Node* node, const int& val) {
			//	考察递归以及回溯的功底
			if (node == nullptr) { return nullptr; }
			if (val < node->data_) {
				node->left_ = remove(node->left_, val);
				//	再此进行回溯操作
				if (high(node->right_) - high(node->left_) > 1) {	//	右子树较高
					if (high(node->right_->right_) >= high(node->right_->left_)) {
						node = leftRotate(node);
					}
					else {
						node->right_ = rightRotate(node->right_);
						node = leftRotate(node);
					}
				}
			}
			else if (val > node->data_) {
				node->right_ = remove(node->right_, val);
				//	再此进行回溯操作
				if (high(node->left_) - high(node->right_) > 1) {	//	左子树较高
					if (high(node->left_->left_) >= high(node->left_->right_)) {
						node = rightRotate(node);
					}
					else {
						node->left_ = leftRotate(node->left_);
						node = rightRotate(node);
					}
				}
			}
			else {
				if (node->left_ != nullptr && node->right_ != nullptr) {
					//	为了避免删除节点造成节点失衡;谁高删除谁;
					if (high(node->left_) >= high(node->right_)) {//	删除前驱节点
						Node* pre = node->left_;
						while (pre->right_ != nullptr) { pre = pre->right_; }

						node->data_ = pre->data_;
						node->left_ = remove(node->left_, pre->data_);
					}
					else {//	删除后继节点
						Node* post = node->right_;
						while (post->left_ != nullptr) { post = post->left_; }

						node->data_ = post->data_;
						node->right_ = remove(node->right_, post->data_);
					}
				}
				else {//	最多有一个孩子
					if (node->left_ != nullptr) {
						Node* left = node->left_;
						delete node;
						return left;
					}
					else if (node->right_ != nullptr) {
						Node* right = node->right_;
						delete node;
						return right;
					}
					else { return nullptr; }
				}
			}
			//	再此进行回溯操作
			node->height_ = max(high(node->left_), high(node->right_)) + 1;

			return node;
		}


	};

	void test_AVL() {
		AVL avl;
		for (int i = 0; i < 10; ++i) { avl.insert(i); }

		cout << avl.high() << endl;

		avl.n_preOrder();
		avl.n_inOrder();
		avl.n_postOrder();
		avl.n_levelOrder();

		for (int i = 0; i < 10; ++i) { avl.remove(i); }

		cout << avl.high() << endl;

		avl.n_preOrder();
		avl.n_inOrder();
		avl.n_postOrder();
		avl.n_levelOrder();

	}


}
