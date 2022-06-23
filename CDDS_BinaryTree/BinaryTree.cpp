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
	while (m_pRoot)
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
	while (currentNode != toInsert) {
		if (currentNode->GetData() == toInsert->GetData()) {
			break;
		}
		if (toInsert->GetData() >= currentNode->GetData()) {
			if (currentNode->GetRight() == nullptr) {
				currentNode->SetRight(toInsert);
				break;
			}
			else currentNode = currentNode->GetRight();
			continue;
		}
		else {
			if (currentNode->GetLeft() == nullptr) {
				currentNode->SetLeft(toInsert);
				break;
			}
			else currentNode = currentNode->GetLeft();
			continue;
		}
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	//Set the current node to the root
	ppOutNode = m_pRoot;
	ppOutParent = nullptr;
	//	While the current node is not null
	//		if the search value equals the current node value,
	//			return the current node and its parent
	//		otherwise
	//		If the search value is less than the current node
	//			set the current node to the left child
	//		otherwise set the current node to the right child
	//	end While
	//If the loop exits, then a match was not found, so return false
	while (ppOutNode != nullptr) {
		if (ppOutNode->GetData() == a_nSearchValue)
		{
			return true;
		}
		if (ppOutNode->GetData() < a_nSearchValue)
		{
			ppOutParent = ppOutNode;
			ppOutNode = ppOutNode->GetRight();
		}
		else {
			ppOutParent = ppOutNode;
			ppOutNode = ppOutNode->GetLeft();
		}
	}
	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	//find the value in the tree, obtaining a pointer to the nodeand its parent
	TreeNode* pToRemove = nullptr;
	TreeNode* pToRemoveParent = nullptr;
	FindNode(a_nValue, pToRemove, pToRemoveParent);
	TreeNode* currentNode = pToRemove;


	if (m_pRoot->GetLeft() == nullptr && m_pRoot->GetRight() == nullptr)
	{
		m_pRoot = nullptr;
		return;
	}

	//if removing the root
	if (pToRemove == m_pRoot)
	{
		TreeNode* currentNodeParent;
		if(m_pRoot->HasRight())	{
			currentNode = currentNode->GetRight();
			if (!currentNode->HasLeft())
			{
				currentNode->SetLeft(m_pRoot->GetLeft());
				m_pRoot = currentNode;
				return;
			}
 			while (currentNode->GetLeft() != nullptr) {
				currentNode = currentNode->GetLeft();
			}
			FindNode(currentNode->GetData(), currentNode, currentNodeParent);
			//
			if (currentNodeParent != nullptr)
			{
				currentNode->SetRight(m_pRoot->GetRight());
			}
			currentNode->SetLeft(m_pRoot->GetLeft());
			m_pRoot = currentNode;			
			currentNodeParent->SetLeft(nullptr);
			
			return;
		}
		else {
			m_pRoot = m_pRoot->GetLeft();
			return;
		}

	}


	//	If the current node has a right branch, then
	if (currentNode->HasRight()) {
		TreeNode* currentNodeParent;
		//	find the minimum value in the right branch by iterating down the left branch of the
		//	current node’s right child until there are no more left branch nodes
		//	copy the value from this minimum node to the current node
		while (currentNode->GetLeft() != nullptr) {
			currentNode = currentNode->GetLeft();
		}
		//	find the minimum node’s parent node(the parent of the node you are deleting)
		FindNode(currentNode->GetData(), currentNode, currentNodeParent);

		//	if you are deleting the parent’s left node
		if (pToRemove == currentNodeParent->GetLeft())
		{
			//	set this left child of the parent to the right child of the minimum node
			currentNodeParent->SetLeft(currentNode->GetRight());
			return;
		}
		//if  you are deleting the parent’s right node
		if (pToRemove == currentNodeParent->GetRight())
		{
			//	set the right child of the parent to the minimum node’s right child
			currentNodeParent->SetRight(currentNode->GetRight());
			return;
		}
	}
	//	If the current node has no right branch
	else {
		//	if we are deleting the parent’s left child, set the left child of the parent to the left
		//	child of the current node
		if (pToRemove == pToRemoveParent->GetLeft()) {
			pToRemoveParent->SetLeft(pToRemove->GetLeft());
		}
		//	If we are deleting the parent’s right child, set the right child of the parent to the left
		//	child of the current node
		if (pToRemove == pToRemoveParent->GetRight()) {
			pToRemoveParent->SetRight(pToRemove->GetLeft());
		}
	}
	//	If we are deleting the root, the root becomes the left child of the current node
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