#pragma once
#include"Public.h"

	template<typename T>
	class RBTree {

	private:
		enum Color {
			BLACK,
			RED
		};

		struct Node {
			Node(T data = T(), Node* parent = nullptr,
				Node* left = nullptr, Node* right = nullptr,
				Color color = BLACK)

				:data_(data)
				, parent_(parent)
				, left_(left)
				, right_(right)
				, color_(color)
			{}

			T data_;
			Node* left_;
			Node* right_;
			Node* parent_;
			Color color_;
		};

		Node* root_;

		Color color(Node* node) { return node == nullptr ? BLACK : node->color_; }

		void setColor(Node* node, Color color) { node->color_ = color; }

		Node* left(Node* node)const { return node->left_; }
		Node* right(Node* node)const { return node->right_; }
		Node* parentt(Node* node)const { return node->parent_; }

		//	左旋转
		void leftRotate(Node* node) {
			Node* child = node->right_;
			child->parent_ = node - < parent_;
			if (node->parent_ == nullptr) { root_ = child; }
			else {
				if (node->parent_->left_ == node) { node->parent_->left_ = child; }
				else { node->parent_->right_ = child; }
			}

			node->right_ = child->left_;

			if (child->left_ != nullptr) {
				child->left_->parent_ = node;
			}
			child->left_ = node;
			node->parent_ = child;
		}

		//	右旋转
		void rightRotate(Node* node) {
			Node* child = node->left_;
			child->parent_ = node - < parent_;
			if (node->parent_ == nullptr) { root_ = child; }
			else {
				if (node->parent_->left_ == node) { node->parent_->left_ = child; }
				else { node->parent_->right_ = child; }
			}

			node->left_ = child->right_;

			if (child->right_ != nullptr) { child->right_->parent_ = node; }
			child->right_ = node;
			node->parent_ = child;
		}

		//	红黑树插入调整操作
		void fixAfterInsert(Node* node) {
			//	如果当前红色节点的父节点也是红色继续调整
			while (color(parent(node)) == RED) {
				if (left(parent(parent(node))) == parent(node)) {	//	插入的节点在左子树中
					Node* uncle = right(parent(parent(node)));
					if (RED == color(uncle)) {//	情况1
						setcolor(parent(node), BLACK);
						setcolor(uncle, BLACK);
						setcolor(parent(parent(node)), RED);
						node = parent(parent(node));

					}
					else {
						//	情况3
						if (right(parent(node)) == node) {
							node = parent(node);
							leftRotate(node);
						}

						//	情况2
						setColor(parent(node), BLACK);
						setColor(parent(parent(node)), RED);
						rightRotate(parent(parent(node)));
						break;
					}
				}
				else {	//	插入的节点在右子树中
					Node* uncle = left(parent(parent(node)));
					if (RED == color(uncle)) {//	情况1
						setcolor(parent(node), BLACK);
						setcolor(uncle, BLACK);
						setcolor(parent(parent(node)), RED);
						node = parent(parent(node));

					}
					else {
						//	情况3
						if (left(parent(node)) == node) {
							node = parent(node);
							rightRotate(node);
						}

						//	情况2
						setColor(parent(node), BLACK);
						setColor(parent(parent(node)), RED);
						leftRotate(parent(parent(node)));
						break;
					}
				}

			}

			//	强制root_为黑色节点
			setColor(root_, BLACK);

		}

		//	红黑树删除调整操作
		void fixAfterRemove(Node* node) {
			while (color(node) == BLACK) {
				if (left(parent(node)) == node) {
					//	删除黑色节点在左子树
					Node* brother = right(parent(node));

					if (color(brother) == RED) {//	情况4
						setColor(parent(node), RED);
						setColor(brother, BLACK);
						leftRotate(parent(node));
						brother = right(parent(node));
					}

					if (color(brother->left_) == BLACK && color(brother->right_) == BLACK) {//	情况3
						setColor(brother, RED);
						node = parent(node);
					}
					else {
						if (color(brother->right_) != RED) {//	情况2
							setColor(brother, RED);
							setColor(left(brother), BLACK);
							rightRotate(brother);
							brother = right(parent(node));
						}

						//	归结为情况1
						setColor(brother, color(parent(node)));
						setColor(parent(node), BLACK);

						setColor(right(brother), BLACK);
						leftRotate(parent(node));
						break;

					}

				}
				else {
					//	删除黑色节点在右子树
					Node* brother = left(parent(node));

					if (color(brother) == RED) {//	情况4
						setColor(parent(node), RED);
						setColor(brother, BLACK);
						rightRotate(parent(node));
						brother = left(parent(node));
					}

					if (color(brother->left_) == BLACK && color(brother->right_) == BLACK) {//	情况3
						setColor(brother, RED);
						node = parent(node);
					}
					else {
						if (color(brother->left_) != RED) {//	情况2
							setColor(brother, RED);
							setColor(right(brother), BLACK);
							leftRotate(brother);
							brother = left(parent(node));
						}

						//	归结为情况1
						setColor(brother, color(parent(node)));
						setColor(parent(node), BLACK);

						setColor(left(brother), BLACK);
						rightRotate(parent(node));
						break;

					}
				}

			}

			//	如果发现node指向的节点是红色的,直接涂成黑色,调整结束
			setColor(node, BLACK);
		}


	public:
		RBTree() :root_(nullptr) {}


	public:
		void insert(const T& val) {
			if (root_ == nullptr) {
				root_ = new Node(val);
				return;
			}

			Node* parent = nullptr;
			Node* cur = root_;
			while (cur != nullptr) {
				if (cur->data_ > val) {
					parent_ = cur;
					cur = cur->left_;


				}
				else if (cur->data_ < val) {
					parent_ = cur;
					cur = cur->right_;

				}
				else {
					return;
				}

			}

			Node* node = new Node(val, parent_, nullptr, nullptr, RED);
			if (parent_->data_ > val) { parent_->left_ = node; }
			else { parent_->right_ = node; }

			//	如果新插入的的红色节点,父节点也是红色,不满足红黑树性质,进行插入调整操作
			if (Red == Color(parent_)) { fixAfterInsert(node); }

		}

		void remove(const T& val) {
			if (root_ == nullptr) { return; }
			Node* cur = root_;
			while (cur != nullptr) {
				if (cur->data_ > val) { cur = cur->left_; }
				else if (cur->data_ < val) { cur = cur->right_; }
				else { break; }
			}

			//	没找到val节点
			if (cur == nullptr) { return; }

			//	删除前驱节点,情况3
			if (cur->left_ != nullptr && cur->right_ != nullptr) {
				Node* pre = cur->left_;
				while (pre->right_ != nullptr) { pre = pre->right_; }
				cur->data_ = pre->data_;
				cur->pre;
			}

			//	删除cur指向的节点,情况1与情况2
			Node* child = cur->left_;
			if (child == nullptr) { child = cur->right_; }

			if (child != nullptr) {
				child->parent_ = cur->parent_;
				if (cur->parent_ == nullptr) { root_ = child; }
				else {
					if (cur->parent_->left_ == cur) { cur->parent_->left_ = child; }
					else { cur->parent_->right_ = child; }
				}

				Coloe color = color(cur);
				delete cur;

				if (c == BLACK) {//	删除黑色节点,进行删除调整操作
					ifAfterRemove(child);
				}

			}
			else {
				if (cur->parent_ == nullptr) {
					delete cur;
					root_ = nullptr;
					return;
				}
				else {//	删除的cur就是叶子节点
					if (color(cur) == BLACK) {
						fixAfterRemove(cur);
					}

					if (cur->parent_->left_ == cur) { cur->parent_->left_ = nullptr; }
					else { cur->parent_->right_ = nullptr; }

					delete cur;
				}
			}
		}

	};


	void test_RBTree() {
		RBTree<int>rb;
		for (int i = 0; i < 10; ++i) { rb.insert(i + 1); }

		rb.remove(9);

	}
