//树总满足二分查找树存储策略。
#ifndef TREE_H
#define TREE_H
namespace TreeSavitch
{
	template  <class T>
	class SearchTree;
	template  <class T>
	class TreeNode
	{
	public:
		TreeNode() : root(NULL) {}
		TreeNode(T theData, TreeNode<T>* left, TreeNode<T>* right)
			:data(theData), leftLink(left), rightLink(right) {}
		friend class SearchTree < T > ;
	private:
		T data;
		TreeNode<T> *leftLink;
		TreeNode<T> *rightLink;
	};

	template <class T>
	class SearchTree
	{
	public:
		SearchTree() : root(NULL) {}
		void insert(T item);
		bool inTree(T item) const;
		void inorderShow() const;
		virtual ~SearchTree();
	private:
		void insert(T item, TreeNode<T>*& subTreeRoot);
		bool inTree(T item, TreeNode<T>* subTreeRoot) const;
		void deleteSubtree(TreeNode<T>*& subTreeRoot);
		void inorderShow(TreeNode<T>* subTreeRoot) const;
		TreeNode<T> *root;
	};
}
#endif