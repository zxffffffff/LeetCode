#include "pch.h"
#include "Test.h"

using namespace std;





/* 数组和链表 *****************************************************************************************
*/

/* 206. 反转链表
反转一个单链表。

示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
*/
ListNode* reverseList2(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *pCur = head, *pNext = pCur->next;
	head->next = NULL;
	while (pNext != NULL)
	{
		ListNode *tmp = pNext->next;
		pNext->next = pCur;
		pCur = pNext;
		pNext = tmp;
	}
	return pCur;
}
ListNode* reverseList(ListNode* head) {
	if (head == NULL)
		return head;

	//递归终止
	if (head->next == NULL)
		return head;

	ListNode *pCur = head, *pNext = pCur->next;
	ListNode *pHead = reverseList(pNext);
	pNext->next = pCur;
	pCur->next = NULL;
	return pHead;
}

/* 24. 两两交换链表中的节点
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例:
给定 1->2->3->4, 你应该返回 2->1->4->3.
*/
ListNode* swapPairs(ListNode* head) {
	//递归终止
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *pCur = head, *pNext = pCur->next;
	ListNode *tmp = swapPairs(pNext->next);

	pCur->next = tmp;
	pNext->next = pCur;
	return pNext;
}

/* 141. 环形链表
给定一个链表，判断链表中是否有环。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。

输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
*/
bool hasCycle(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return false;

	//快慢指针
	ListNode *pFast = head->next, *pSlow = head;
	while (pFast != NULL && pFast->next != NULL)
	{
		if (pFast == pSlow)
			return true;
		pFast = pFast->next->next;
		pSlow = pSlow->next;
	}
	return false;
}

/*142. 环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。
*/
ListNode* detectCycle(ListNode* head) {
	set<ListNode *> set1;
	ListNode *pCur = head;
	while (pCur != NULL)
	{
		auto ite = set1.find(pCur);
		if(ite != set1.end())
			return pCur;
		set1.insert(pCur);
		pCur = pCur->next;
	}
	return NULL;
}

/* 25. K 个一组翻转链表
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
k 是一个正整数，它的值小于或等于链表的长度。
如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

示例 :
给定这个链表：1->2->3->4->5
当 k = 2 时，应当返回: 2->1->4->3->5
当 k = 3 时，应当返回: 3->2->1->4->5

说明 :
你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
*/
ListNode* reverseKGroup(ListNode* head, int k) {
	if (head == NULL)
		return head;

	//长度不够，递归终止
	ListNode *pCur = head->next;
	for (int i = 1; i < k; i++) {
		if (pCur == NULL)
			return head;
		pCur = pCur->next;
	}

	ListNode *pHead = reverseKGroup(pCur, k);
	
	//反转k个节点
	pCur = head;
	ListNode *pNext = pCur->next;
	for (int i = 1; i < k; i++) {
		ListNode *tmp = pNext->next;
		pNext->next = pCur;
		pCur = pNext;
		pNext = tmp;
	}
	head->next = pHead;
	return pCur;
}





/* 堆栈和队列 *****************************************************************************************
*/

/* 844. 比较含退格的字符串
给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，
判断二者是否相等，并返回结果。 # 代表退格字符。

示例 1：
输入：S = "ab#c", T = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。

示例 2：
输入：S = "ab##", T = "c#d#"
输出：true
解释：S 和 T 都会变成 “”。

示例 3：
输入：S = "a##c", T = "#a#c"
输出：true
解释：S 和 T 都会变成 “c”。

示例 4：
输入：S = "a#c", T = "b"
输出：false
解释：S 会变成 “c”，但 T 仍然是 “b”。
 
提示：
1 <= S.length <= 200
1 <= T.length <= 200
S 和 T 只含有小写字母以及字符 '#'。
*/
bool backspaceCompare(string S, string T) {
	auto parse = [](const string &s) {
		stack<char> sk;
		for (auto c : s) {
			if (c != '#')
				sk.push(c);
			else if (!sk.empty())
				sk.pop();
		}
		return sk;
	};

	return (parse(S) == parse(T));
}



/* 232. 用栈实现队列
使用栈实现队列的下列操作：
push(x) -- 将一个元素放入队列的尾部。
pop() -- 从队列首部移除元素。
peek() -- 返回队列首部的元素。
empty() -- 返回队列是否为空。

示例:
MyQueue queue = new MyQueue();
queue.push(1);
queue.push(2);
queue.peek();  // 返回 1
queue.pop();   // 返回 1
queue.empty(); // 返回 false

说明:
你只能使用标准的栈操作 -- 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）。
*/
class MyQueue {
public:
	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {

	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		return 0;
	}

	/** Get the front element. */
	int peek() {
		return 0;
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return 0;
	}
	/**
	 * Your MyQueue object will be instantiated and called as such:
	 * MyQueue* obj = new MyQueue();
	 * obj->push(x);
	 * int param_2 = obj->pop();
	 * int param_3 = obj->peek();
	 * bool param_4 = obj->empty();
	 */
};

/* 225. 用队列实现栈
使用队列实现栈的下列操作：
push(x) -- 元素 x 入栈
pop() -- 移除栈顶元素
top() -- 获取栈顶元素
empty() -- 返回栈是否为空

注意:
你只能使用队列的基本操作-- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。
*/
class MyStack {
public:
	/** Initialize your data structure here. */
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {

	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		return 0;
	}

	/** Get the top element. */
	int top() {
		return 0;
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return 0;
	}
	/**
	 * Your MyStack object will be instantiated and called as such:
	 * MyStack* obj = new MyStack();
	 * obj->push(x);
	 * int param_2 = obj->pop();
	 * int param_3 = obj->top();
	 * bool param_4 = obj->empty();
	 */
};

/* 20. 有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。

示例 1:
输入: "()"
输出: true

示例 2:
输入: "()[]{}"
输出: true

示例 3:
输入: "(]"
输出: false

示例 4:
输入: "([)]"
输出: false

示例 5:
输入: "{[]}"
输出: true
*/
bool isValid(string s) {
	return 0;
}


/* 优先队列 *****************************************************************************************
*/

/* 703. 数据流中的第K大元素
设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。
你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。
每次调用 KthLargest.add，返回当前数据流中第K大的元素。

示例:
int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8

说明:
你可以假设 nums 的长度≥ k-1 且k ≥ 1。
*/
class KthLargest {
public:
	KthLargest(int k, vector<int>& nums) {

	}

	int add(int val) {
		return 0;
	}
	/**
	 * Your KthLargest object will be instantiated and called as such:
	 * KthLargest* obj = new KthLargest(k, nums);
	 * int param_1 = obj->add(val);
	 */
};

/* 239. 滑动窗口最大值
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口 k 内的数字。滑动窗口每次只向右移动一位。
返回滑动窗口最大值。

示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:
  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

注意：
你可以假设 k 总是有效的，1 ≤ k ≤ 输入数组的大小，且输入数组不为空。
进阶：
你能在线性时间复杂度内解决此题吗？
*/



/* 哈希表（映射map 集合set）  ************************************************************************
*/

/* 242. 有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true

示例 2:
输入: s = "rat", t = "car"
输出: false

说明:
你可以假设字符串只包含小写字母。
进阶:
如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？--换成map
*/
bool isAnagram(string s, string t) {
	auto toHash = [](string s) {
		vector<int> hash(26, 0);
		for (auto c : s)
			hash[c - 'a']++;
		return hash;
	};

	return (toHash(s) == toHash(t));
}

/* 1. 两数之和
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
*/
vector<int> twoSum(vector<int>& nums, int target) {
	//建表 value : index
	map<int, vector<int>> hash;
	for (int i = 0; i < nums.size(); i++) {
		hash[nums[i]].push_back(i);
	}

	vector<int> v;
	for (auto n : nums) {
		int need = target - n;
		if(hash.find(need) == hash.end())
			continue;

		//相同val
		if (need == n) {
			if (hash[n].size() < 2)
				continue;
			else {
				v.push_back(hash[n][0]);
				v.push_back(hash[n][1]);
				break;
			}
		}
		//不同val
		v.push_back(hash[n][0]);
		v.push_back(hash[need][0]);
		break;
	}
	return v;
}

/* 15. 三数之和
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
vector<vector<int>> threeSum(vector<int>& nums) {
	//建表 value : times
	map<int, int> hash;
	for (auto n : nums) {
		if (hash.find(n) == hash.end())
			hash[n] = 1;
		else
			hash[n]++;
	}

	//遍历两个值，找第三个
	set<vector<int>> setv;
	vector<int> v(3, 0);
	for (auto ite = hash.begin(); ite != hash.end(); ite++) {
		for (auto ite2 = ite; ite2 != hash.end(); ite2++) {
			int need = 0 - (*ite).first - (*ite2).first;
			auto ite3 = hash.find(need);
			if(ite3 == hash.end())
				continue;

			// 1+1+1(-1,-2,3) , 2+1(-1,-1,2) , 3(0,0,0)
			if (ite == ite2 && (*ite).second < 2)
				continue;
			if((ite == ite3 || ite2 == ite3) && (*ite3).second < 2)
				continue;
			if(ite == ite2 && ite2 == ite3 && (*ite).second < 3)
				continue;

			v[0] = (*ite).first;
			v[1] = (*ite2).first;
			v[2] = need;
			sort(v.begin(), v.end());
			setv.insert(v);
		}
	}

	vector<vector<int>> vv;
	for (auto v : setv)
		vv.push_back(v);
	return vv;
	
	//////////////////////////////////////////////////////////////////////////
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size() && nums[i] <= 0; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		int first = i + 1; int last = nums.size() - 1;
		while (first < last)
		{
			int sums = nums[i] + nums[first] + nums[last];
			if (sums > 0)
				last--;
			else if (sums < 0)
				first++;
			else
			{
				result.push_back(vector<int>{nums[i], nums[first], nums[last]});
				first++;
				while (first < last && nums[first] == nums[first - 1])
					first++;
			}
		}
	}
	return result;
	//////////////////////////////////////////////////////////////////////////
	vector<vector<int>> three; 
	vector<int>num;
	if (nums.size() >= 3)
	{
		sort(nums.begin(), nums.end());
		int first, last;
		for (int i = 0; i < nums.size() - 2; i++)
		{
			if (i > 0 && nums[i] == nums[i - 1])
				continue;

			first = i + 1; 
			last = nums.size() - 1;

			int sum;
			while (first != last)
			{
				sum = nums[i] + nums[first] + nums[last];
				if (sum < 0) first++;
				if (sum > 0) last--;
				if (sum == 0)
				{
					if (nums[first] != nums[first - 1] || first == i + 1)
					{
						num.push_back(nums[i]); num.push_back(nums[first]); num.push_back(nums[last]);
						three.push_back(num);
						num.clear();
					}
					first++;
				}
			}
		}
	}
	return three;
}


/* 18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，
使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
注意：答案中不可以包含重复的四元组。

示例：
给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	return vector<vector<int>>();
}


/* 树和图（Tree Graph）  ************************************************************************
*/
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* 98. 验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。
假设一个二叉搜索树具有如下特征：
节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

示例 1:
输入:
	2
   / \
  1   3
输出: true

示例 2:
输入:
	5
   / \
  1   4
     / \
    3   6
输出: false
解释: 输入为: [5,1,4,null,null,3,6]。
     根节点的值为 5 ，但是其右子节点值为 4 。
*/
bool isValidBST(TreeNode* root, int &max, int &min) {
	if (root == NULL)
		return true;

	bool ret = false;
	int maxL, minL, maxR, minR;
	maxL = minL = maxR = minR = root->val;

	if (root->left != NULL) {
		ret = isValidBST(root->left, maxL, minL);
		if (!ret || maxL >= root->val)
			return false;
	}
	if (root->right != NULL) {
		ret = isValidBST(root->right, maxR, minR);
		if (!ret || minR <= root->val)
			return false;
	}

	max = maxR;
	min = minL;
	return true;
}
bool isValidBST(TreeNode* root) {
	int max, min;
	return isValidBST(root, max, min);
}

/* 235. 二叉搜索树的最近公共祖先
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
    6
   / \
  2    8
 /\    /\
0  4  7  9
   /\
  3  5

示例 1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6
解释: 节点 2 和节点 8 的最近公共祖先是 6。

示例 2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。

说明:
所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	//找到分叉口
	if (root->val > p->val && root->val > q->val)
		return lowestCommonAncestor(root->left, p, q);
	if (root->val < p->val && root->val < q->val)
		return lowestCommonAncestor(root->right, p, q);
	return root;
}

/* 236. 二叉树的最近公共祖先（不是搜索树！！！！！）
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4] 

示例 1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

示例 2:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。

说明:
所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉树中。
*/
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == NULL || root == p || root == q)
		return root;

	TreeNode *l = lowestCommonAncestor2(root->left, p, q);
	if (l != NULL && l != p && l != q)
		return l;

	TreeNode *r = lowestCommonAncestor2(root->right, p, q);
	if (r != NULL && r != p && r != q)
		return r;

	if (l != NULL && r != NULL)
		return root;
	return (l != NULL ? l : r);
}


/* 二叉树的遍历  ************************************************************************
*	Pre-order		前序 ROOT - left - right
*	In-order		中序 left - ROOT - right
*	Post-order		后序 left - right - ROOT
*/


/* 递归和分治 ************************************************************************
*/

/* 50. Pow(x, n)
实现 pow(x, n) ，即计算 x 的 n 次幂函数。

示例 1:
输入: 2.00000, 10
输出: 1024.00000

示例 2:
输入: 2.10000, 3
输出: 9.26100

示例 3:
输入: 2.00000, -2
输出: 0.25000
解释: 2^-2 = 1/2^2 = 1/4 = 0.25

说明:
-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是 [−2^31, 2^31 − 1] 。
*/
double fastPow(double x, long long n) {
	if (n == 0) 
		return 1.0;

	double half = fastPow(x, n / 2);
	if (n % 2 == 0)
		x = half * half;
	else
		x = half * half * x;
	return x;
}
double myPow(double x, int n) {
	long long ll = n;
	if (n < 0) {
		x = 1 / x;
		ll = -ll;
	}
	return fastPow(x, n);
}



/* 169. 求众数
给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在众数。

示例 1:
输入: [3,2,3]
输出: 3

示例 2:
输入: [2,2,1,1,1,2,2]
输出: 2
*/
int MECount(vector<int>& nums, int n, int l, int r) {
	//查找出现的次数
	return 1;
}
int majorityElement(vector<int>& nums, int l, int r) {
	//分治法，左边一半和右边一半进行对比
	int mid = l + (r - l) / 2;
	int mjL = majorityElement(nums, l, mid);
	int mjR = majorityElement(nums, mid + 1, r);
	if (mjL == mjR)
		return mjL;
	return (MECount(nums, mjL, l, r) > MECount(nums, mjR, l, r) ? mjL : mjR);
}
int majorityElement(vector<int>& nums) {
	//偷懒法
	//sort(nums.begin(), nums.end());
	//return nums[nums.size() / 2];
	return 1;
}


/* 贪心算法 ************************************************************************************
*/

/* 122. 买卖股票的最佳时机 II
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。

示例 2:
输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
int maxProfit(vector<int>& prices) {
	int n = 0;
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1])
			n += prices[i] - prices[i - 1];
	}
	return n;
}


/* 广度优先搜索（BFS Breadth） 深度优先搜索（DFS Depth） ******************************************
*/

/* 102. 二叉树的层次遍历
给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。

例如:给定二叉树: [3,9,20,null,null,15,7],
	3
   / \
  9  20
	/  \
   15   7
返回其层次遍历结果：
[
  [3],
  [9,20],
  [15,7]
]
*/
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> v;
	vector<TreeNode*> task;

	task.push_back(root);
	while (task.size() > 0)
	{
		vector<int> vTmp;
		vector<TreeNode*> taskTmp;
		for (auto p : task)
		{
			if (p != NULL) {
				vTmp.push_back(p->val);
				taskTmp.push_back(p->left);
				taskTmp.push_back(p->right);
			}
		}
		task.swap(taskTmp);
		if (vTmp.size() > 0)
			v.push_back(vTmp);
	}
	return v;
}

/* 104. 二叉树的最大深度
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
说明: 叶子节点是指没有子节点的节点。

示例：给定二叉树 [3,9,20,null,null,15,7]，
	3
   / \
  9  20
	/  \
   15   7
返回它的最大深度 3 。
*/
int maxDepthLevel(TreeNode *root, int level) {
	int l = level, r = level;
	if (root->left)
		l = maxDepthLevel(root->left, level + 1);
	if (root->right)
		r = maxDepthLevel(root->right, level + 1);
	return max(l, r);
}
int maxDepth(TreeNode* root) {
	if (root == NULL)
		return 0;
	return maxDepthLevel(root, 1);
}

/* 22. 括号生成
给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。

例如，给出 n = 3，生成结果为：
[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/
vector<string> generateParenthesis(int n) {
	set<string> base;
	base.insert("()");
	for (int i = 1; i < n; i++) {
		set<string> v;
		for (auto s : base) {
			for (int idx = 0; idx <= s.size(); idx++) {
				v.insert(string(s).insert(idx, "()"));
			}
		}
		v.swap(base);
	}

	vector<string> ret;
	for (auto &s : base)
		ret.push_back(s);
	return ret;
}
void Test::Interview()
{
	generateParenthesis(3);
}


/* 剪纸 ******************************************************************************************
*/
















