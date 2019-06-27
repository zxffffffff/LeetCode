#include "pch.h"
#include "Test.h"

using namespace std;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

//二叉树的前序遍历 先访问根节点，然后遍历左子树，最后遍历右子树。
void preorderTraversalSearch(vector<int>& v, TreeNode* root)
{
	if (root == NULL)
		return;
	v.push_back(root->val);
	preorderTraversalSearch(v, root->left);
	preorderTraversalSearch(v, root->right);
}
vector<int> preorderTraversal(TreeNode* root) 
{
	vector<int> v;
	preorderTraversalSearch(v, root);
	return v;
}


//中序遍历 先遍历左子树，然后访问根节点，然后遍历右子树。
void inorderTraversalSearch(vector<int>& v, TreeNode* root)
{
	if (root == NULL)
		return;
	inorderTraversalSearch(v, root->left);
	v.push_back(root->val);
	inorderTraversalSearch(v, root->right);
}
vector<int> inorderTraversal(TreeNode* root) 
{
	vector<int> v;
	inorderTraversalSearch(v, root);
	return v;
}


//后序遍历 先遍历左子树，然后遍历右子树，最后访问树的根节点。
void postorderTraversalSearch(vector<int>& v, TreeNode* root)
{
	if (root == NULL)
		return;
	postorderTraversalSearch(v, root->left);
	postorderTraversalSearch(v, root->right);
	v.push_back(root->val);
}
vector<int> postorderTraversal(TreeNode* root) 
{
	vector<int> v;
	postorderTraversalSearch(v, root);
	return v;
}


//层序遍历 逐层遍历树结构。
void levelOrderSearch(vector<int>& v, vector<TreeNode*>& task, TreeNode* root)
{
	if (root == NULL)
		return;
	v.push_back(root->val);
	task.push_back(root->left);
	task.push_back(root->right);
}
vector<vector<int>> levelOrder(TreeNode* root) 
{
	vector<vector<int>> v;
	vector<TreeNode*> task;

	task.push_back(root);
	while (task.size() > 0)
	{
		vector<int> vTmp;
		vector<TreeNode*> taskTmp;
		for (auto p : task)
		{
			levelOrderSearch(vTmp, taskTmp, p);
		}
		task.swap(taskTmp);
		if(vTmp.size() > 0)
			v.push_back(vTmp);
	}
	return v;
}


//二叉树的最大深度
int g_maxDepth = 0;
void maxDepthSearch(int& depth, TreeNode* root)
{
	if (root == NULL)
		return;
	depth++;
	g_maxDepth = (g_maxDepth > depth) ? g_maxDepth : depth;
	maxDepthSearch(depth, root->left);
	maxDepthSearch(depth, root->right);
	depth--;
}
int maxDepth(TreeNode* root) 
{
	int depth = 0;
	maxDepthSearch(depth, root);
	return g_maxDepth;
}


//对称二叉树 递归和迭代两种方法，这里只做了一种
bool isSymmetric(TreeNode* root)
{
	if (root == NULL)
		return true;
	vector<TreeNode*> task;
	task.push_back(root->left);
	task.push_back(root->right);

	while (task.size() > 0)
	{
		vector<TreeNode*> taskTmp;
		int sz = task.size();
		if (sz % 2 > 0)
			return false;
		for (int i = 0; i < sz / 2; i++)
		{
			if (task[i] != NULL && task[sz - 1 - i] != NULL) {
				if (task[i]->val != task[sz - 1 - i]->val)
					return false;
			}
			else if (task[i] == NULL && task[sz - 1 - i] == NULL) {

			}
			else {
				return false;
			}
		}
		for (auto p : task) {
			if (p != NULL) {
				taskTmp.push_back(p->left);
				taskTmp.push_back(p->right);
			}
		}
		task.swap(taskTmp);
	}
	return true;
}



//路径总和 判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
int g_hasPathSum = 0;
bool hasPathSum(TreeNode* root, int sum) 
{
	if (root == NULL)
		return false;
	g_hasPathSum += root->val;
	if (root->left == NULL && root->right == NULL && g_hasPathSum == sum)
		return true;
	if (hasPathSum(root->left, sum))
		return true;
	if (hasPathSum(root->right, sum))
		return true;
	g_hasPathSum -= root->val;
	return false;
}



//从中序与后序遍历序列构造二叉树（前序+中序 原理相同）
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
{
	int sz = inorder.size();
	if (sz > 0)
	{
		TreeNode* root = new TreeNode(postorder[sz - 1]);
		vector<int> l, r, l2, r2;
		bool flag = false;
		for (int i = 0; i < sz; i++)
		{
			if (inorder[i] == postorder[sz - 1]) {
				flag = true;
			}
			else if (flag) {
				r.push_back(inorder[i]);
				r2.push_back(postorder[i - 1]);
			}
			else {
				l.push_back(inorder[i]);
				l2.push_back(postorder[i]);
			}
		}
		root->left = buildTree(l, l2);
		root->right = buildTree(r, r2);
		return root;
	}
	return NULL;
}



class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;
	Node(int _val, Node* _left = NULL, Node* _right = NULL, Node* _next = NULL) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;
	}
};
//填充每个节点的下一个右侧节点指针
Node* connect(Node* root) 
{
	if (root == NULL)
		return root;

	vector<Node*> task;
	task.push_back(root);
	while (task.size() > 0) 
	{
		vector<Node*> taskTmp;
		for (auto p : task) 
		{
			if(p != NULL && p->left != NULL)
				taskTmp.push_back(p->left);
			if(p != NULL && p->right != NULL)
				taskTmp.push_back(p->right);
		}
		task.swap(taskTmp);
		
		int sz = task.size();
		for (int i = 0; i < sz - 1; i++)
			task[i]->next = task[i + 1];
	}
	return root;
}

/* 给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
* 
	输入: 3
	输出: 5
	解释:
	给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

	   1         3     3      2      1
		\       /     /      / \      \
		 3     2     1      1   3      2
		/     /       \                 \
	   2     1         2                 3
*/
int numTrees(int n) {
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	dp[1] = 1;
	for (int num = 2; num <= n; num++) 
	{
		//当i为根，左子树个数i-1，右子树个数n-i
		//即f(i) = G(i-1)*G(n-i),
		for (int i = 0; i <= num; i++)
		{
			dp[num] += dp[i - 1] * dp[num - i];
		}
	}
	return dp[n];
}


/* 78. 子集
* 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
* 说明：解集不能包含重复的子集。
*/
void helper(vector<vector<int> >& res, vector<int> tmp, vector<int>& nums, int level) 
{
	if (tmp.size() <= nums.size()) {
		res.push_back(tmp);
	}
	for (int i = level; i < nums.size(); i++) {
		tmp.push_back(nums[i]);
		helper(res, tmp, nums, i + 1);
		tmp.pop_back();
	}
}
vector<vector<int>> subsets(vector<int>& nums)
{
	vector<vector<int> > res;
	vector<int> tmp;
	helper(res, tmp, nums, 0);
	return res;
}


void Test::Tree()
{
	numTrees(3);

	//vector<int> inorder = { 9,3,15,20,7 };
	//vector<int> postorder = { 9,15,7,20,3 };
	//buildTree(inorder, postorder);

	//Node* root = new Node(1);
	//root->left = new Node(2);
	//root->right = new Node(3);
	//root->left->left = new Node(4);
	//root->left->right = new Node(5);
	//root->right->left = new Node(6);
	//root->right->right = new Node(7);
	//connect(root);
}




