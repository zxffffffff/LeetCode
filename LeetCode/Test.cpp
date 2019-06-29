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

	Characters();
	HashTable();
	Tree();
	Interview();
}

Test::~Test()
{
}
