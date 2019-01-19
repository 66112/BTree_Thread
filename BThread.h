#pragma once 
#include <iostream>
#include <assert.h>
using namespace std;
typedef int DataType;
enum PtrTag
{
	LINK,  //连接左右孩子
	THREAD  //线索化
};
typedef struct BTNode
{
	BTNode* _pleft;
	BTNode* _pright;
	BTNode* _parent;
	DataType _data;
	PtrTag _ltag;     
 	PtrTag _rtag;
}BTNode;
BTNode* BuyBTNode(DataType x)
{
	BTNode* cur = new BTNode;
	cur->_data = x;
	cur->_pleft = nullptr;
	cur->_parent = nullptr;
	cur->_pright = nullptr;
	cur->_ltag = LINK;
	cur->_rtag = LINK;
	return cur;
}
BTNode* CreateTree(DataType* a, DataType invalaid, size_t* pindex)
{
	assert(a && pindex);
	BTNode* root = nullptr;
	if (a[*pindex] != invalaid){
		root = BuyBTNode(a[*pindex]);
		(*pindex)++;
		root->_pleft = CreateTree(a, invalaid, pindex);
		if (root->_pleft)
			root->_pleft->_parent = root;
		(*pindex)++;
		root->_pright = CreateTree(a, invalaid, pindex);
		if (root->_pright)
			root->_pright->_parent = root;
	}
	return root;
}
//中序线索化////////////////////////////////////////
void BTreeInoderThread(BTNode* cur,BTNode** pprev)  //pprev指向cur的前驱结点
{
	if (cur == nullptr) return;
	BTreeInoderThread(cur->_pleft,pprev);
	if (cur->_pleft == nullptr){
		cur->_ltag = THREAD;
		cur->_pleft = *pprev;
	}
	if (*pprev && (*pprev)->_pright == nullptr){
		(*pprev)->_pright = cur;
		(*pprev)->_rtag = THREAD;
	};
	*pprev = cur;
	BTreeInoderThread(cur->_pright,pprev);
}
BTNode* GetInorderNext(BTNode* cur)
{
	if (cur->_rtag == THREAD)
		return cur->_pright;
	cur = cur->_pright;
	while (cur -> _ltag == LINK){   //右子树最左边的节点
		cur = cur->_pleft;
	}
	return cur;
}
void BTreeInoderPrint(BTNode* cur)
{
	if (cur == nullptr) return;
	while (cur->_ltag == LINK)
		cur = cur->_pleft;
	while (cur){
		cout << cur->_data << " ";
		cur = GetInorderNext(cur);
	}
	cout << endl;
}
//前序线索化///////////////////////////////////////
void BTNodeFrontThread(BTNode* cur,BTNode** pprev)
{
	if (cur == nullptr) return;
	if (cur->_pleft == nullptr){
		cur->_pleft = *pprev;
		cur->_ltag = THREAD;
	}
	if (*pprev && (*pprev)->_pright == nullptr){
		(*pprev)->_pright = cur;
		(*pprev)->_rtag = THREAD;
	}
	*pprev = cur;
	if (cur ->_ltag == LINK)
		BTNodeFrontThread(cur->_pleft, pprev);
	if (cur ->_rtag == LINK)
		BTNodeFrontThread(cur->_pright, pprev);
}
BTNode* GetFrontThreadNext(BTNode* cur)
{
	if (cur->_ltag == LINK)
		return cur->_pleft;
	return cur->_pright;
}
void BTreeFrontThreadPrint(BTNode* cur)
{
	if (cur == nullptr) return;
	while (cur){
		cout << cur->_data << " ";
		cur = GetFrontThreadNext(cur);
	}
	cout << endl;
}
//后序线索化/////////////////////////////////
void Back(BTNode* root)
{
	if (root == nullptr) return;
	if (root->_ltag == LINK)
		Back(root->_pleft);
	if (root->_rtag == LINK)
		Back(root->_pright);
	cout << root->_data << " ";
}
void BTNodeBackThread(BTNode* cur, BTNode** pprev)
{
	if (cur == nullptr) return;
	BTNodeBackThread(cur->_pleft, pprev); 
	BTNodeBackThread(cur->_pright, pprev);
	if (cur->_pleft == nullptr){
		cur->_pleft = *pprev;
		cur->_ltag = THREAD;
	}
	if (*pprev && (*pprev)->_pright == nullptr){
		(*pprev)->_pright = cur;
		(*pprev)->_rtag = THREAD;
	}
	*pprev = cur;
}
BTNode* GetBackThreadNext(BTNode* cur)
{
	if (cur->_rtag == THREAD)
		return cur->_pright;
	if (cur->_parent == nullptr)
		return nullptr;
	if (cur->_parent->_pright == nullptr)
		return cur->_parent;
	cur = cur->_parent->_pright;
	while (cur -> _ltag == LINK){  //找到兄弟子树最左边的节点
		cur = cur->_pleft;
	}
	return cur;
}
void BTreeBackThreadPrint(BTNode* cur)
{
	if (cur == nullptr) return;
	while (cur->_ltag == LINK){
		cur = cur->_pleft;
	}
	while (cur){
		cout << cur->_data << " ";
		cur = GetBackThreadNext(cur);
	}
	cout << endl;
}
void BTreeTest()
{
	BTNode* root = nullptr;
	DataType arr[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#', '#', '#' };
	size_t index = 0;
	root = CreateTree(arr, '#', &index);
	BTNode* prev = nullptr;
	//中序线索化
	//BTreeInoderThread(root, &prev);
	//prev->_rtag = THREAD;
	//BTreeInoderPrint(root);
	//前序线索化
	//prev = nullptr;
	//BTNodeFrontThread(root,&prev);
	//prev->_rtag = THREAD;
	//BTreeFrontThreadPrint(root);
	//后续线索化
	//Back(root);
	//cout << endl;
	BTNodeBackThread(root, &prev);
	BTreeBackThreadPrint(root);
}