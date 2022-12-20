#include <iostream>
#include "tree.h"
using std::cout;
namespace TreeSavitch
{
	template  <class T>
	void SearchTree<T>::insert(T item)
	{
		insert(item, root);
	}
	template  <class T>
	void SearchTree<T>::insert(T item, TreeNode<T>*& subTreeRoot)
	{
		if (subTreeRoot == NULL)
			subTreeRoot = new TreeNode<T>(item, NULL, NULL);
		else if (item < subTreeRoot->data)
			insert(item, subTreeRoot->leftLink);
		else
			insert(item, subTreeRoot->rightLink);
	}
	template  <class T>
	bool SearchTree<T>::inTree(T item) const
	{
		return inTree(item, root);
	}
	template  <class T>
	bool SearchTree<T>::inTree(T item, TreeNode<T>* subTreeRoot) const
	{
		if (subTreeRoot == NULL)
			return false;
		else if (subTreeRoot->data == item)
			return true;
		else if (item < subTreeRoot->data)
			return inTree(item, subTreeRoot->leftLink);
		else
			return inTree(item, subTreeRoot->rightLink);
	}
	template  <class T>
	void SearchTree<T>::inorderShow() const
	{
		inorderShow(root);
	}
	template  <class T>
	void SearchTree<T>::inorderShow(TreeNode<T>* subTreeRoot) const
	{
		if (subTreeRoot != NULL)
		{
			inorderShow(subTreeRoot->leftLink);
			cout << subTreeRoot->data << " ";
			inorderShow(subTreeRoot->rightLink);
		}
	}
	template  <class T>
	void SearchTree<T>::deleteSubtree(TreeNode<T>*& subTreeRoot)
	{
		if (subTreeRoot != NULL)
		{
			deleteSubtree(subTreeRoot->leftLink);
			deleteSubtree(subTreeRoot->rightLink);
		}
		delete subTreeRoot;
		subTreeRoot = NULL;
	}
	template  <class T>
	SearchTree<T>::~SearchTree()
	{
		deleteSubtree(root);
	}
}
