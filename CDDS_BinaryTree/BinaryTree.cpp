/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	//step 1 insert at the Root if there is no root
	TreeNode* toInsert = new TreeNode(a_nValue);
	if (IsEmpty()) {
		m_pRoot = toInsert;
		return;
	}

	//step 2 if there is a root, compare the new node value to the root value,
	// if it is low move to left node if higher move to right,
	//if that position is nullptr, insert node,
	//if not repeat check for left and right
	TreeNode* currentNode = m_pRoot;
	while (currentNode != toInsert){
		if (currentNode->GetData() == toInsert->GetData())	{
			break;
		}
		if (toInsert->GetData() >= currentNode->GetData()) {
			if (currentNode->GetRight() == nullptr) {
				currentNode->SetRight(toInsert);
			}
			else currentNode = currentNode->GetRight();
		}
		else {
			if (currentNode->GetLeft() == nullptr) {
				currentNode->SetLeft(toInsert);
			}
			else currentNode;
		}
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* currentNode = m_pRoot;
	TreeNode currentNode = TreeNode(a_nSearchValue);
	while (currentNode != ) {

	}


	return false;
}

void BinaryTree::Remove(int a_nValue)
{

}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
    PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}