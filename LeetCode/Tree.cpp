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
vector<vector<int>> levelOrder2(TreeNode* root) 
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
int maxDepth2(TreeNode* root) 
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
	//for (int num = 2; num <= n; num++) 
	//{
	//	//当i为根，左子树个数i-1，右子树个数n-i
	//	//即f(i) = G(i-1)*G(n-i),
	//	for (int i = 0; i <= num; i++)
	//	{
	//		dp[num] += dp[i - 1] * dp[num - i];
	//	}
	//}
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


/* 1002. 查找常用字符(easy
给定仅有小写字母组成的字符串数组 A，返回列表中的每个字符串中都显示的全部字符（包括重复字符）组成的列表。
例如，如果一个字符在每个字符串中出现 3 次，但不是 4 次，则需要在最终答案中包含该字符 3 次。
你可以按任意顺序返回答案。

示例 1：
输入：["bella","label","roller"]
输出：["e","l","l"]

示例 2：
输入：["cool","lock","cook"]
输出：["c","o"]
 
提示：
1 <= A.length <= 100
1 <= A[i].length <= 100
A[i][j] 是小写字母
*/
class Solution1002 {
public:
	vector<string> commonChars(vector<string>& A) {
		const int sz = A.size();
		vector<string> v_ans;
		if (sz < 2)
			return v_ans;
		vector<int> v_count(26); //a~z

		for (int i = 0; i < sz; i++) {

			vector<int> v_tmp(26);
			for (auto& c : A[i]) {
				v_tmp[c - 'a']++;
			}

			if (i == 0) {
				v_count.swap(v_tmp);
				continue;
			}

			for (int j = 0; j < 26; j++) {
				v_count[j] = min(v_count[j], v_tmp[j]);
			}
		}
		for (int i = 0; i < 26; i++) {
			string c = "a";
			c[0] += i;
			for (int j = 0; j < v_count[i]; j++) {
				v_ans.push_back(c);
			}
		}
		return v_ans;
	}
};

/* 645. 错误的集合(easy
集合 S 包含从1到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个元素复制了成了集合里面的另外一个元素的值，
导致集合丢失了一个整数并且有一个元素重复。
给定一个数组 nums 代表了集合 S 发生错误后的结果。你的任务是首先寻找到重复出现的整数，
再找到丢失的整数，将它们以数组的形式返回。

示例 1:
输入: nums = [1,2,2,4]
输出: [2,3]

注意:
给定数组的长度范围是 [2, 10000]。
给定的数组是无序的。
*/
class Solution645 {
public:
	vector<int> findErrorNums(vector<int>& nums) {
		const int MAX = 10000;
		vector<bool> v_flag(MAX, false);
		vector<int> v_ans(2);
		for (auto& n : nums) {
			if (v_flag[n])
				v_ans[0] = n;
			else
				v_flag[n] = true;
		}
		for (int i = 1; i < v_flag.size(); i++) {
			if (!v_flag[i]) {
				v_ans[1] = i;
				break;
			}
		}
		return v_ans;

		//sort(nums.begin(), nums.end());
		//vector<int> v_ans(2);
		//int base = 0;
		//int loop = 2;
		//for (int i = 0; loop && i < nums.size(); i++) {
		//	if (base == nums[i]) {
		//		v_ans[0] = base;
		//		loop--;
		//	}
		//	if (base + 1 != nums[i]) {
		//		v_ans[1] = base + 1;
		//		loop--;
		//	}
		//	base = nums[i];
		//}
		//return v_ans;
	}
};

/* 627. 交换工资(easy
给定一个 salary 表，如下所示，有 m = 男性 和 f = 女性 的值。
交换所有的 f 和 m 值（例如，将所有 f 值更改为 m，反之亦然）。
要求只使用一个更新（Update）语句，并且没有中间的临时表。
注意，您必只能写一个 Update 语句，请不要编写任何 Select 语句。

例如：
| id | name | sex | salary |
|----|------|-----|--------|
| 1  | A    | m   | 2500   |
| 2  | B    | f   | 1500   |
| 3  | C    | m   | 5500   |
| 4  | D    | f   | 500    |
运行你所编写的更新语句之后，将会得到以下表:
| id | name | sex | salary |
|----|------|-----|--------|
| 1  | A    | f   | 2500   |
| 2  | B    | m   | 1500   |
| 3  | C    | f   | 5500   |
| 4  | D    | m   | 500    |
*/
//update salary set sex = char(ascii('m') + ascii('f') - ascii(sex));

/* 78. 子集(medium
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/
class Solution78 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> v_ans(1); //empty item
		vector<vector<int>> v_tmp;
		for (auto& n : nums) {
			v_tmp.clear();
			v_tmp.reserve(v_ans.size() + 1);
			for (auto v : v_ans) {
				v.push_back(n);
				v_tmp.push_back(v);
			}
			v_ans.reserve(v_ans.size() * 2 + 1);
			v_ans.insert(v_ans.end(), v_tmp.begin(), v_tmp.end());
		}
		return v_ans;
	}
};
/* 90. 子集 II
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/
class Solution90 {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		set<vector<int>> set_ans;
		set<vector<int>> set_tmp;
		set_ans.insert(vector<int>()); //empty item
		for (auto& n : nums) {
			set_tmp.clear();
			for (auto v : set_ans) {
				v.push_back(n);
				sort(v.begin(), v.end());
				set_tmp.insert(v);
			}
			set_ans.insert(set_tmp.begin(), set_tmp.end());
		}
		vector<vector<int>> v_ans;
		v_ans.reserve(set_ans.size());
		for (auto& v : set_ans) {
			v_ans.push_back(v);
		}
		return v_ans;
	}
};


/* 189. 旋转数组
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
*/
class Solution189 {
public:
	inline void reverse(vector<int>& nums, int lo, int hi) {
		while (lo < hi) {
			swap(nums[lo], nums[hi]);
			lo++;
			hi--;
		}
	}
	void rotate(vector<int>& nums, int k) {
		if (nums.empty() || k < 1)
			return;
		k = k % nums.size();
		reverse(nums, 0, nums.size() - 1);
		reverse(nums, 0, k - 1);
		reverse(nums, k, nums.size() - 1);
	}
};


void Test::Tree()
{
	//numTrees(3);

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




