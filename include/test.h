#pragma once

#include"linearTable.h"
//#include"RBT.h"
//using namespace rb_tree;

#include"hashTable.h"
#include"binarySearchTree.h"
#include"AVL.h"
#include"searchSort.h"
#include"priorityQueue.h"
#include"bigData.h"

using namespace linear_table;
using namespace hash_table;
using namespace binary_search_tree;
using namespace avl;
using namespace search_sort;
using namespace priority_queue;
using namespace big_data;

int test() {
	test_linearTable();
	test_hashTable();
	test_BSTree();
	test_AVL();
	test_searchSort();
	test_priorityQueue();
	test_bigData();

	//test_RBTree();
	return 0;
}
