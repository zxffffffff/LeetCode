#include "pch.h"
#include "Test.h"

using namespace std;


/* 771. 宝石与石头
* 给定字符串J 代表石头中宝石的类型，和字符串 S代表你拥有的石头。 
* S 中每个字符代表了一种你拥有的石头的类型，你想知道你拥有的石头中有多少是宝石。
* J 中的字母不重复，J 和 S中的所有字符都是字母。字母区分大小写，因此"a"和"A"是不同类型的石头。
* S 和 J 最多含有50个字母。
* J 中的字符不重复。
* 
* 输入: J = "aA", S = "aAAbbbb"			* 输出: 3
* 输入: J = "z", S = "ZZ"				* 输出: 0
*/
int numJewelsInStones(string J, string S) {
	// 哈希思想
	int count = 0;
	char buff[128] = {0};
	//memset(buff, 0, sizeof(buff));

	for (int j = 0; j < J.length(); ++j) {
		buff[J[j]] = 1;
	}
	for (int s = 0; s < S.length(); ++s) {
		if (1 == buff[S[s]])
			++count;
	}
	return count;
}

/* 665. 非递减数列
* 给定一个长度为 n 的整数数组，你的任务是判断在最多改变 1 个元素的情况下，该数组能否变成一个非递减数列。
* 我们是这样定义一个非递减数列的： 对于数组中所有的 i (1 <= i < n)，满足 array[i] <= array[i + 1]。
* 
* 输入: [4,2,3]		* 输出: true	解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。
* 输入: [4,2,1]		* 输出: false	解释: 你不能在只改变一个元素的情况下将其变为非递减数列。
*/
bool checkPossibility(vector<int>& nums) {
	const int numsCount = nums.size();
	int nFind;
	bool bFlag = false;

	// 至少有2个数
	if (numsCount < 2)
		return true; 
	// 遍历不满足的条件
	for (int i = 0; i < numsCount - 1; ++i) {
		if (nums[i + 1] < nums[i]) {
			// 至多有1个递减
			if (bFlag)
				return false; 
			else {
				bFlag = true;
				nFind = i;
			}
		}
	}
	// 未出现 / 在最左边 / 在最右边
	if (!bFlag || 0 == nFind || (numsCount - 1 == nFind + 1))
		return true; 
	// 若改小左边值，不能比前一个小 / 若改大右边的值，不能比后一个大
	if (nums[nFind + 1] >= nums[nFind - 1] || nums[nFind] <= nums[nFind + 2])
		return true;
	return false;
}

/* 674. 最长连续递增序列
* 给定一个未经排序的整数数组，找到最长且连续的的递增序列。
* 
* 输入: [1,3,5,4,7]		* 输出: 3		解释: 最长连续递增序列是 [1,3,5], 长度为3。
* 输入: [2,2,2,2,2]		* 输出: 1		解释: 最长连续递增序列是 [2], 长度为1。
*/
int findLengthOfLCIS(vector<int>& nums) {
	const int numsCount = nums.size();
	int max = 0;
	int cur = 0;

	// 至少有2个数
	if (numsCount < 2)
		return numsCount;
	// 遍历查找所有连续递增
	for (int i = 0; i < numsCount - 1; ++i) {
		++cur;
		if (cur > max)
			max = cur;
		if (nums[i] < nums[i + 1]) {
			// 递增
		}
		else {
			// 中断
			cur = 0;
		}
	}
	++cur;
	if (cur > max)
		max = cur;
	return max;
}

/* 680. 验证回文字符串 Ⅱ
* 给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。
* 
* 输入: "aba"		* 输出: True		ABA、ABBA 都算回文
* 输入: "abca"		* 输出: True		解释: 你可以删除c字符。
*/
bool validPalindrome(string s) {
	int left = 0;
	int right = s.length() - 1;
	bool bFlag = false;
	auto checkPal = [](string &s, int left, int right) -> bool {
		while (right > left) {
			if (s[right] != s[left])
				return false;
			++left;
			--right;
		}
		return true;
	};

	// 至少有2个字符串
	if (right - left < 2)
		return true;
	while (right > left) {
		if (s[right] != s[left]) {
			if (!bFlag) {
				bFlag = true;
				// 发现不同，删左 / 删右
				return (checkPal(s, left + 1, right) || checkPal(s, left, right - 1));
			}
			else {
				// 至多有1个不同
				return false;
			}
		}
		++left;
		--right;
	}
	return true;
}

/* 475. 供暖器
* 冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。
* 现在，给出位于一条水平线上的房屋和供暖器的位置，找到可以覆盖所有房屋的最小加热半径。
* 所以，你的输入将会是房屋和供暖器的位置。你将输出供暖器的最小加热半径。
* 1 给出的房屋和供暖器的数目是非负数且不会超过 25000。
* 2 给出的房屋和供暖器的位置均是非负数且不会超过10^9。
* 3 只要房屋位于供暖器的半径内(包括在边缘上)，它就可以得到供暖。
* 4 所有供暖器都遵循你的半径标准，加热的半径也一样。
* 
* 输入: [1,2,3],[2]		* 输出: 1	解释: 仅在位置2上有一个供暖器。如果我们将加热半径设为1，那么所有房屋就都能得到供暖。
* 输入: [1,2,3,4],[1,4]	* 输出: 1	解释: 在位置1, 4上有两个供暖器。我们需要将加热半径设为1，这样所有房屋就都能得到供暖。
*/
int findRadius(vector<int>& houses, vector<int>& heaters) {
	if (houses.size() < 1 || heaters.size() < 1)
		return -1;
	// 输入可能乱序，先从小到大排序
	std::sort(houses.begin(), houses.end());
	std::sort(heaters.begin(), heaters.end());
	// 只有一个heater的情况，可以直接返回
	if (heaters.size() == 1) {
		int left = std::abs(houses[0] - heaters[0]);
		int right = std::abs(houses[houses.size() - 1] - heaters[0]);
		return std::max(left, right);
	}
	// 对于每一个house有前后两个取暖器(都在一侧也可以当做两侧来处理)
	int radius = 0;
	int prev = 0, next = 1; 
	for (int i = 0; i < houses.size(); ++i) {
		if (houses[i] == heaters[prev] || houses[i] == heaters[next]) {
			// house 和heater重叠，不处理
		}
		else if (houses[i] < heaters[prev]) {
			// house 在prev的前面，一定是第一个heater
			radius = std::max(radius, heaters[prev] - houses[i]);
		}
		else if (houses[i] > heaters[next]) {
			// house 在next的后面，可能是最后一个heater
			if (next >= heaters.size() - 1) {
				radius = std::max(radius, houses[i] - heaters[next]);
			}
			// 也可能是移动next
			else {
				prev = next;
				++next;
				--i; // 重新判断一次
			}
		}
		else {
			// house 在prev和next之间，取最近
			int r = min(houses[i] - heaters[prev], heaters[next] - houses[i]);
			radius = max(radius, r);
		}
	}
	return radius;
}

/* 476. 数字的补数
* 给定一个正整数，输出它的补数。补数是对该数的二进制表示取反。
* 1 给定的整数保证在32位带符号整数的范围内。
* 2 你可以假定二进制数不包含前导零位。
* 
* 输入: 5	输出: 2		解释: 5的二进制表示为101（没有前导零位），其补数为010。所以你需要输出2。
* 输入: 1	输出: 0		解释: 1的二进制表示为1（没有前导零位），其补数为0。所以你需要输出0。
*/
int findComplement(int num) {
	// 需要把"前导零位"去掉，用掩码
	int mask = ~0; // 0xffffffff
	while (mask & num)
		mask = mask << 1;
	return ((~num )& (~mask));
}

/* 482. 密钥格式化
* 给定一个密钥字符串S，只包含字母，数字以及 '-'（破折号）。N 个 '-' 将字符串分成了 N+1 组。
* 给定一个数字 K，重新格式化字符串，除了第一个分组以外，每个分组要包含 K 个字符，第一个分组至少要包含 1 个字符。
* 两个分组之间用 '-'（破折号）隔开，并且将所有的小写字母转换为大写字母。
* 给定非空字符串 S 和数字 K，按照上面描述的规则进行格式化。
* 1 S 的长度不超过 12,000，K 为正整数
* 2 S 只包含字母数字（a-z，A-Z，0-9）以及破折号'-'
* 3 S 非空
* 
* 输入：S = "5F3Z-2e-9-w", K = 4	解释：字符串 S 被分成了两个部分，每部分 4 个字符；注意，两个额外的破折号需要删掉。
* 输出："5F3Z-2E9W"
* 输入：S = "2-5g-3-J", K = 2		解释：字符串 S 被分成了 3 个部分，第一部分的字符可以少于给定的数量，其余部分皆为 2 个字符。
* 输出："2-5G-3J" 
*/
string licenseKeyFormatting(string S, int K) {
	// 为了提高效率，可以把insert操作换成自己定义的char[]固定长度
	// 先替换字符
	auto ite = S.begin();
	while (ite != S.end()) {
		if ('-' == *ite) {
			ite = S.erase(ite);
			continue;
		}
		if (*ite >= 'a' && *ite <= 'z') {
			*ite += ('A' - 'a');
		}
		++ite;
	}
	// 在添加'-'
	int firstLen = S.size() % K;
	int count = S.size() / K;
	ite = S.begin();
	if (firstLen > 0 && count > 0) {
		ite = S.insert(ite + firstLen, '-');
		++ite;
	}
	for (int i = 0; i < count - 1; ++i) {
		ite = S.insert(ite + K, '-');
		++ite;
	}
	return S;
}

/* 342. 4的幂
* 给定一个整数 (32 位有符号整数)，请编写一个函数来判断它是否是 4 的幂次方。
* 进阶：
* 你能不使用循环或者递归来完成本题吗？
* 
* 输入: 16		* 输出: true
* 输入: 5		* 输出: false 
*/
bool isPowerOfFour(int num) {
	// 理论上数字4幂的二进制类似于100，10000，1000000，etc...形式。可以有如下结论：
	// 4的幂一定是2的。
	// 4的幂和2的幂一样，只会出现一位1。但是，4的1总是出现在奇数位。
	if (num < 0 || num & (num - 1))
		return false;

	// 0x5 = 0101b可以用来校验奇数位上的1。
	return num & 0x55555555;
}

/* 344. 反转字符串
* 编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 char[] 的形式给出。
* 不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。
* 你可以假设数组中的所有字符都是 ASCII 码表中的可打印字符。
* 
* 输入：["h","e","l","l","o"]
* 输出：["o","l","l","e","h"]
*/
void reverseString(vector<char>& s) {
	//// 新建一个vec然后交换
	//const int siz = s.size();
	//vector<char> reverse;
	//reverse.resize(siz);
	//for (int i = 0; i < siz; ++i)
	//	reverse[siz - 1 - i] = s[i];
	//s.swap(reverse);

	// 双指针对换，测试两个效率不相上下
	const int siz = s.size();
	if (siz < 2)
		return;
	int left = 0;
	int right = siz - 1;
	while (right > left) {
		std::swap(s[left], s[right]);
		++left;
		--right;
	}
}

/* 345. 反转字符串中的元音字母
* 编写一个函数，以字符串作为输入，反转该字符串中的元音字母。
* 
* 输入: "hello"
* 输出: "holle"
*/
string reverseVowels(string s) {
#define isVowels(X) ('a' == X || 'A' == X || 'e' == X || 'E' == X || 'i' == X || 'I' == X || 'o' == X || 'O' == X || 'u' == X || 'U' == X)
	//// 双指针对换，超时了...???
	//const int siz = s.size();
	//if (siz < 2)
	//	return s;
	//int left = 0;
	//int right = siz - 1;
	//while (1) {
	//	while (right > left && !isVowels(s[left]))
	//		++left;
	//	while (right > left && !isVowels(s[right]))
	//		--left;
	//	if (right > left)
	//		std::swap(s[left], s[right]);
	//	else
	//		break;
	//}
	//return s;

	// 保存元音和地址，倒着放回去
	const int siz = s.size();
	if (siz < 2)
		return s;
	vector<char> val;
	vector<int> idx;
	for (int i = 0; i < siz; ++i) {
		if (isVowels(s[i])) {
			val.push_back(s[i]);
			idx.push_back(i);
		}
	}
	for (int i = 0; i < idx.size(); ++i) {
		s[idx[i]] = val[idx.size() - 1 - i];
	}
	return s;

#undef isVowels
}

/* 219. 存在重复元素 II
* 给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，
* 使得 nums [i] = nums [j]，并且 i 和 j 的差的绝对值最大为 k。
* 
* 输入: nums = [1,2,3,1], k = 3			* 输出: true
* 输入: nums = [1,0,1,1], k = 1			* 输出: true
* 输入: nums = [1,2,3,1,2,3], k = 2		* 输出: false
*/
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	// 用map保存 value-index 重复时判断差值，其他方法感觉都不如map舒服
	map<int, int> mapNearby;
	for (int i = 0; i < nums.size(); i++) {
		auto ite = mapNearby.find(nums[i]);
		if (ite != mapNearby.end() && i - ite->second <= k) {
			return true;
		}
		else {
			mapNearby[nums[i]] = i;
		}
	}
	return false;
}

/* 762. 二进制表示中质数个计算置位
* 给定两个整数 L 和 R ，找到闭区间 [L, R] 范围内，计算置位位数为质数的整数个数。
* 注意，计算置位代表二进制表示中1的个数。例如 21 的二进制表示 10101 有 3 个计算置位。还有，1 不是质数。
* 
* 输入: L = 6, R = 10			* 输出: 4
	6 -> 110 (2 个计算置位，2 是质数)
	7 -> 111 (3 个计算置位，3 是质数)
	9 -> 1001 (2 个计算置位，2 是质数)
	10-> 1010 (2 个计算置位，2 是质数)
* 
* 输入: L = 10, R = 15			* 输出: 5
	10 -> 1010 (2 个计算置位, 2 是质数)
	11 -> 1011 (3 个计算置位, 3 是质数)
	12 -> 1100 (2 个计算置位, 2 是质数)
	13 -> 1101 (3 个计算置位, 3 是质数)
	14 -> 1110 (3 个计算置位, 3 是质数)
	15 -> 1111 (4 个计算置位, 4 不是质数)
*/
int countPrimeSetBits(int L, int R) {
	return 0;
}


/* 146. LRU缓存机制
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。
它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。
当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

进阶:
你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:
LRUCache cache = new LRUCache( 2  缓存容量  );
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4
*/
class LRUCache {
public:
	LRUCache(int capacity) {

	}

	int get(int key) {
		return 0;
	}

	void put(int key, int value) {

	}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
};


/* 148. 排序链表
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:
输入: 4->2->1->3
输出: 1->2->3->4

示例 2:
输入: -1->5->3->4->0
输出: -1->0->3->4->5
*/
ListNode* sortList(ListNode* head) {
	return 0;
}


/* 152. 乘积最大子序列
给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

示例 1:
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

示例 2:
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/
int maxProduct(vector<int>& nums) {
	//1、暴力 双for 返回最大值
	//2、动态规划 保留最大最小值
	if (nums.empty()) return 0;
	if (nums.size() < 2) return nums[0];

	int imax, imin, ret;
	imax = imin = ret = nums[0];
	for (int i = 1; i < nums.size(); i++) {
		int &n = nums[i];
		if (n < 0)
			swap(imax, imin);
		imax = max(n, n * imax);
		imin = min(n, n * imin);
		ret = max(ret, imax);
	}
	return ret;
}


/* 155. 最小栈
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。
push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。

示例:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
*/
bool xxx(int a, int b) { return a > b; }
class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		s.push(x);
		if (s_min.empty() || x <= s_min.top())
			s_min.push(x);
	}

	void pop() {
		int x = s.top();
		s.pop();
		if (x == s_min.top())
			s_min.pop();
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return s_min.top();
	}

	stack<int> s, s_min; //用一个最小值的stack
	/**
	 * Your MinStack object will be instantiated and called as such:
	 * MinStack* obj = new MinStack();
	 * obj->push(x);
	 * obj->pop();
	 * int param_3 = obj->top();
	 * int param_4 = obj->getMin();
	 */
};

/* 160. 相交链表
编写一个程序，找到两个单链表相交的起始节点。
	a1 -> a2 -> a3 \
			        -> c1 -> c2 
	      b1 -> b2 /

注意：
如果两个链表没有交点，返回 null.
在返回结果后，两个链表仍须保持原有的结构。
可假定整个链表结构中没有循环。
程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。
*/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (headA == NULL || headA->next == NULL || headB == NULL || headB->next == NULL)
		return NULL;
	//1、用set记录途径节点
	//2、消除两个链的长度差，第二次同时移动相交
	ListNode *pA = headA, *pB = headB;
	int nA = 0, nB = 0;
	while (pA != NULL) {
		nA++;
		pA = pA->next;
	}
	while (pB != NULL) {
		nB++;
		pB = pB->next;
	}

	pA = headA; pB = headB;
	if (nA > nB) {
		for (int i = 0; i < nA - nB; i++)
			pA = pA->next;
	}
	else {
		for (int i = 0; i < nB - nA; i++)
			pB = pB->next;
	}

	while (pA != NULL && pB != NULL) {
		if (pA == pB)
			return pA;
		pA = pA->next;
		pB = pB->next;
	}
	return NULL;
}


/* 198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是
相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

示例 1:
输入: [1,2,3,1]
输出: 4
解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。

示例 2:
输入: [2,7,9,3,1]
输出: 12
解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
*/
int rob(vector<int>& nums) {
	//1、暴力枚举
	//2、动态规划 dp[i] = max(dp[i-2], dp[i-3]) + val
	int sz = nums.size();
	if (sz == 0) return 0;
	if (sz == 1) return nums[0];
	if (sz == 2) return max(nums[0], nums[1]);

	vector<int> dp(sz, 0);
	dp[0] = nums[0];
	dp[1] = nums[1];
	dp[2] = nums[0] + nums[2];
	int imax = max(dp[1], dp[2]);
	for (int i = 3; i < sz; i++) {
		dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i];
		imax = max(imax, dp[i]);
	}
	return imax;
}


/* 200. 岛屿数量
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:
		11110
		11010
		11000
		00000
输出: 1

示例 2:
		11000
		11000
		00100
		00011
输出: 3
*/
void numIslandsSet0(vector<vector<char>>& grid, pair<int, int> root) {
	int xlen = grid.size();
	int ylen = grid[0].size();
	auto pushTask = [&xlen, &ylen](set<pair<int, int>> &tasks_new, pair<int, int> pos) {
		if (pos.first < 0 || pos.first >= xlen || pos.second < 0 || pos.second >= ylen)
			return;
		tasks_new.insert(pos);
	};

	//BFS
	set<pair<int, int>> tasks;
	tasks.insert(root);
	while (!tasks.empty()) {
		set<pair<int, int>> tasks_new;
		for (auto &pos : tasks) {
			if (grid[pos.first][pos.second] == '0')
				continue;
			grid[pos.first][pos.second] = '0';
			pushTask(tasks_new, pair<int, int>(pos.first + 1, pos.second));
			pushTask(tasks_new, pair<int, int>(pos.first - 1, pos.second));
			pushTask(tasks_new, pair<int, int>(pos.first, pos.second + 1));
			pushTask(tasks_new, pair<int, int>(pos.first, pos.second - 1));
		}
		tasks.swap(tasks_new);
	}
}
int numIslands(vector<vector<char>>& grid) {
	//双 5% 这么惨
	//遍历，找到1后总数+1，以1为起点上下左右全部设为0
	int count = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int ii = 0; ii < grid[0].size(); ii++) {
			if (grid[i][ii] == '1') {
				count++;
				numIslandsSet0(grid, pair<int, int>(i, ii));
			}
		}
	}
	return count;
}

/* 207. 课程表
现在你总共有 n 门课需要选，记为 0 到 n-1。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
给定课程总量以及它们的先决条件，判断是否可能完成所有课程的学习？

示例 1:
输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。

示例 2:
输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。

说明:
输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。

提示:
这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
拓扑排序也可以通过 BFS 完成。
*/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	return 0;
}




/* 51. N皇后
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

上图为 8 皇后问题的一种解法。
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。
*/
class Q51{
//执行用时 :28 ms, 在所有 C++ 提交中击败了30.91%的用户
//内存消耗 :13.8 MB, 在所有 C++ 提交中击败了27.62%的用户
public:
	vector<vector<string>> m_ret;
	int m_n;
	void addQ(vector<int> &pos) {
		vector<string> vs;
		for(int row = 0; row < m_n; row++){
			string s(m_n, '.');
			int col = pos[row];
			s[col] = 'Q';
			vs.push_back(s);
		}
		m_ret.push_back(vs);
	}
	void DFS(set<int> &invalid_col, set<int> &invalid_pie, set<int> &invalid_na, vector<int> &pos) {
		int row = pos.size();
		if(row == m_n) {
			addQ(pos);
			return;
		}
		for (int col = 0; col < m_n; col++) {
			if(invalid_col.find(col) != invalid_col.end()) continue;
			if(invalid_pie.find(col + row) != invalid_pie.end()) continue;
			if(invalid_na.find(col - row) != invalid_na.end()) continue;

			invalid_col.insert(col);
			invalid_pie.insert(col + row);
			invalid_na.insert(col - row);
			pos.push_back(col);
			DFS(invalid_col, invalid_pie, invalid_na, pos);
			pos.pop_back();
			invalid_na.erase(invalid_na.find(col - row));
			invalid_pie.erase(invalid_pie.find(col + row));
			invalid_col.erase(invalid_col.find(col));
		}
	}
	vector<vector<string>> solveNQueens(int n) {
		m_n = n;
		set<int> invalid_col, invalid_pie, invalid_na;
		vector<int> pos;
		DFS(invalid_col, invalid_pie, invalid_na, pos);
		return m_ret;
	}
};

/* 52. N皇后 II
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

上图为 8 皇后问题的一种解法。
给定一个整数 n，返回 n 皇后不同的解决方案的数量。

输入: 4  输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/
int totalNQueens(int n) {
	return 0;
}


/* 36. 有效的数独
判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

示例 1:输入:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: true

示例 2:输入:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: false
解释: 除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。
	 但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
*/
bool isValidSudoku(vector<vector<char>>& board) {
	

	return 0;
}

/* 37. 解数独
编写一个程序，通过已填充的空格来解决数独问题。
一个数独的解法需遵循如下规则：
数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。
答案被标成红色。

Note:
给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。
*/
void solveSudoku(vector<vector<char>>& board) {

}


/* 69. x 的平方根
实现 int sqrt(int x) 函数。
计算并返回 x 的平方根，其中 x 是非负整数。
由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

示例 1:
输入: 4 输出: 2

示例 2:
输入: 8 输出: 2
说明: 8 的平方根是 2.82842...,由于返回类型是整数，小数部分将被舍去。
*/
int mySqrt(int x) {
	
	return 0;
}


/* 208. 实现 Trie (前缀树)
实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

说明:
你可以假设所有的输入都是由小写字母 a-z 构成的。
保证所有输入均为非空字符串。
*/
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {

	}

	/** Inserts a word into the trie. */
	void insert(string word) {

	}

	/** Returns if the word is in the trie. */
	bool search(string word) {

	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {

	}

	/**
	 * Your Trie object will be instantiated and called as such:
	 * Trie* obj = new Trie();
	 * obj->insert(word);
	 * bool param_2 = obj->search(word);
	 * bool param_3 = obj->startsWith(prefix);
	 */
};


/* 79. 单词搜索
给定一个二维网格和一个单词，找出该单词是否存在于网格中。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

示例:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
给定 word = "ABCCED", 返回 true.
给定 word = "SEE", 返回 true.
给定 word = "ABCB", 返回 false.
*/
bool exist(vector<vector<char>>& board, string word) {
	if (word.empty())
		return true;
	if (board.empty() || board[0].empty())
		return false;
	
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if(word[0] != board[i][j])
				continue;

			set<pair<int, int>> setIdx;
			pair<int, int> idx(i, j);
			for (auto c : word) {
				////
			}
		}
	}

	return false;
}






/* 73. 矩阵置零(Medium
给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。

示例 1:
输入:[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
输出:[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]

示例 2:
输入:[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
输出:[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]

进阶:
一个直接的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
你能想出一个常数空间的解决方案吗？
*/
class Solution73 {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		set<int> setRow, setCol;
		for (int row = 0; row < matrix.size(); row++) {
			for (int col = 0; col < matrix[row].size(); col++) {
				if (matrix[row][col] == 0) {
					setRow.insert(row);
					setCol.insert(col);
				}
			}
		}
		for (int row = 0; row < matrix.size(); row++) {
			bool bRow = (setRow.find(row) != setRow.end());
			for (int col = 0; col < matrix[row].size(); col++) {
				if (bRow) {
					matrix[row][col] = 0;
					continue;
				}
				bool bCol = (setCol.find(col) != setCol.end());
				if (bCol) {
					matrix[row][col] = 0;
				}
			}
		}
	}
};

/* 905. 按奇偶排序数组(Easy
给定一个非负整数数组 A，返回一个数组，在该数组中， A 的所有偶数元素之后跟着所有奇数元素。
你可以返回满足此条件的任何数组作为答案。

示例：
输入：[3,1,2,4]
输出：[2,4,3,1]
输出 [4,2,3,1]，[2,4,1,3] 和 [4,2,1,3] 也会被接受。
 
提示：
1 <= A.length <= 5000
0 <= A[i] <= 5000
*/
class Solution905 {
public:
	vector<int> sortArrayByParity(vector<int>& A) {
		int sz = A.size();
		if (sz < 2) return A;

		vector<int> ans(sz, 0);
		int lo = 0, hi = sz - 1;
		for (int i = 0; i < sz; i++) {
			if (A[i] % 2 == 0)
				ans[lo++] = A[i];
			else
				ans[hi--] = A[i];
		}
		return ans;
	}
};

/* 1019. 链表中的下一个更大节点(mudium
给出一个以头节点 head 作为第一个节点的链表。链表中的节点分别编号为：node_1, node_2, node_3, ... 。

每个节点都可能有下一个更大值（next larger value）：
对于 node_i，如果其 next_larger(node_i) 是 node_j.val，那么就有 j > i 且  node_j.val > node_i.val，
而 j 是可能的选项中最小的那个。如果不存在这样的 j，那么下一个更大值为 0 。

返回整数答案数组 answer，其中 answer[i] = next_larger(node_{i+1}) 。

注意：在下面的示例中，诸如 [2,1,5] 这样的输入（不是输出）是链表的序列化表示，
其头节点的值为 2，第二个节点值为 1，第三个节点值为 5 。

示例 1：
输入：[2,1,5]
输出：[5,5,0]

示例 2：
输入：[2,7,4,3,5]
输出：[7,0,5,5,0]

示例 3：
输入：[1,7,5,1,9,2,5,1]
输出：[7,9,9,9,0,5,0,0]

提示：
对于链表中的每个节点，1 <= node.val <= 10^9
给定列表的长度在 [0, 10000] 范围内
*/
class Solution {
public:
	/*
	执行用时 :292 ms, 在所有 C++ 提交中击败了83.66%的用户
	内存消耗 :25.8 MB, 在所有 C++ 提交中击败了44.86%的用户
	*/
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> v;
		for (auto p = head; p != NULL; p = p->next) {
			v.push_back(p->val);
		}
		vector<int> ans(v.size(), 0);
		stack<int> dic; //维护一个递减的栈，栈底放最大值
		for (int i = v.size(); i > 0; i--) {
			int val = v[i - 1];
			while (!dic.empty()) {
				if (dic.top() > val) {
					ans[i - 1] = dic.top();
					dic.push(val);
					break;
				}
				dic.pop();
			}
			if (dic.empty()) {
				dic.push(val);
				continue;
			}
		}
		return ans;
	}
};


/* 462. 最少移动次数使数组元素相等 II（medium
给定一个非空整数数组，找到使所有数组元素相等所需的最小移动数，其中每次移动可将选定的一个元素加1或减1。
您可以假设数组的长度最多为10000。
例如:

输入:
[1,2,3]
输出:
2

说明：
只有两个动作是必要的（记得每一步仅可使其中一个元素加1或减1）：
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
*/
class Solution462 {
public:
	int minMoves2(vector<int>& nums) {
		//中位数最优解
	}
};

/* 914. 卡牌分组(easy
给定一副牌，每张牌上都写着一个整数。
此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

每组都有 X 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 X >= 2 时返回 true。
*/
class Solution914 {
public:
	static bool hasGroupsSizeX(vector<int> deck) {
		if (deck.empty()) return false;

		map<int, int> mapCount; //牌：重复次数
		for (auto val : deck) {
			if (mapCount.find(val) != mapCount.end())
				mapCount[val]++;
			else
				mapCount[val] = 1;
		}
		
		map<int, int> mapCount2; //公约数：重复次数
		for (auto ite = mapCount.begin(); ite != mapCount.end(); ite++) {
			int val = ite->second;
			if (val < 2) return false; // X >= 2

			for (int i = 2; i <= val; i++) {
				if (val % i == 0) {
					if (mapCount2.find(i) != mapCount2.end())
						mapCount2[i]++;
					else
						mapCount2[i] = 1;
				}
			}
		}

		for (auto ite = mapCount2.begin(); ite != mapCount2.end(); ite++) {
			if (ite->second == mapCount.size())
				return true;
		}
		return false;
	}
};


/* 349. 两个数组的交集(easy
给定两个数组，编写一个函数来计算它们的交集。

示例 1:
输入: nums1 = [1,2,2,1], nums2 = [2,2]
输出: [2]

示例 2:
输入: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出: [9,4]

说明:
输出结果中的每个元素一定是唯一的。
我们可以不考虑输出结果的顺序。
*/
class Solution349 {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		set<int> dic, ans;
		for (auto n : nums1) {
			dic.insert(n);
		}
		for (auto n : nums2) {
			if (dic.find(n) != dic.end())
				ans.insert(n);
		}
		vector<int> vans;
		for (auto n : ans) {
			vans.push_back(n);
		}
		return vans;
	}
};


/* 63. 不同路径 II(medium
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
网格中的障碍物和空位置分别用 1 和 0 来表示。
说明：m 和 n 的值均不超过 100。

示例 1:
输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: 2

解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
*/
class Solution63 {
public:
    static int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //递归 f(x,y) = f(x+1,y) + f(x,y+1)
		//动态规划
		int rowCount = obstacleGrid.size();
		if (rowCount < 1) return 0;
		int colCount = obstacleGrid[0].size();
		if (colCount < 1) return 0;
		vector<vector<int>> dp(rowCount, vector<int>(colCount, 0));
		for (int row = rowCount; row > 0; row--) {
			for (int col = colCount; col > 0; col--) {
				if (obstacleGrid[row - 1][col - 1] == 1) {
					//dp[row - 1][col - 1] = 0;
					continue;
				}
				if (row == rowCount && col == colCount) {
					dp[row - 1][col - 1] = 1;
					continue;
				}
				long long right = 0, down = 0;
				if (col < colCount) right = dp[row - 1][col];
				if (row < rowCount) down = dp[row][col - 1];
				dp[row - 1][col - 1] = right + down;
			}
		}
		return dp[0][0];
    }
};


/* 283. 移动零(easy
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]

说明:
必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。
*/
class Solution283 {
public:
	void moveZeroes(vector<int>& nums) {
		int idxz = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] != 0) {
				nums[idxz++] = nums[i];
			}
		}

		for (int i = idxz; i < nums.size(); i++) {
			nums[i] = 0;
		}
	}
};



Test::Test()
{
// 	vector<int> nums = {1, 2, 3, 1};
// 	cout << "219. bool=" << (containsNearbyDuplicate(nums, 3) ? "true" : "false") << endl;

//	cout << "342. bool=" << (isPowerOfFour(INT_MIN) ? "true" : "false") << endl;

//	cout << "482. string=" << licenseKeyFormatting("----------kmhvVuPIyobPjThzMdhzvBWqNwfDajFiWUQvSUfrQsTuHorFisEjIbHtNEPrLbHJFnDNWFijctwBskljKratHqSOWBOgDnaQodjo", 99).c_str() << endl;

// 	vector<int> houses = { 1, 2, 3, 4 };
// 	vector<int> heaters = { 1, 4 };
// 	cout << "475. count=" << findRadius(houses, heaters) << endl;

// 	vector<int> nums = { 1, 3, 5, 4, 7 };
// 	cout << "674. count=" << findLengthOfLCIS(nums) << endl;

// 	vector<int> nums = {3, 4, 2, 3};
// 	cout << "665. bool=" << (checkPossibility(nums) ? "true" : "false") << endl;

//	cout << "771. count=" << numJewelsInStones("aA", "aAAbbbb") << endl;

	//Solution914::hasGroupsSizeX(vector<int>({ 1,1,1,2,2,2,3,3 }));

	vector<vector<int>> obstacleGrid(3, vector<int>(3, 0));
	obstacleGrid[1][1] = 1;
	Solution63::uniquePathsWithObstacles(obstacleGrid);

	Strings();
	HashTable();
	Tree();
	Interview();
}

Test::~Test()
{
}
