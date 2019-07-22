#include "pch.h"
#include "Test.h"

using namespace std;

/* 动态规划遵循一套固定的流程：递归的暴力解法 -> 带备忘录的递归解法 -> 非递归的动态规划解法。
*/

/* 70. 爬楼梯（简单
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。

示例 1：
输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶

示例 2：
输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶
*/
class Solution70 {
public:
	int climbStairs(int n) {
		if (n < 3) return n;
		vector<int> v;
		v.resize(n + 1);
		v[0] = 0;
		v[1] = 1;
		for (int i = 2; i <= n; i++) {
			v[i] = (v[i - 1] + v[i - 2]);
		}
		return v[n];
	}
};

/* 120. 三角形最小路径和(中等
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：
[
	 [2],
	[3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

说明：
如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。
*/
class Solution120 {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		/*
		执行用时 :12 ms, 在所有 C++ 提交中击败了63.95%的用户
		内存消耗 :9.9 MB, 在所有 C++ 提交中击败了57.63%的用户
		*/
		if (triangle.empty()) return 0;
		vector<vector<int>> v = triangle;
		int rowSz = v.size();
		for (int row = rowSz - 2; row >= 0; row--) { // -idx -last
			for (int col = 0; col < v[row].size(); col++) {
				v[row][col] += min(v[row + 1][col], v[row + 1][col + 1]);
			}
		}
		return v[0][0];
	}
	int minimumTotal2(vector<vector<int>>& triangle) {
		/*
		执行用时 :20 ms, 在所有 C++ 提交中击败了13.92%的用户
		内存消耗 :9.8 MB, 在所有 C++ 提交中击败了78.81%的用户
		*/
		if (triangle.empty()) return 0;
		vector<int> v = triangle[triangle.size() - 1];
		int rowSz = v.size();
		for (int row = rowSz - 2; row >= 0; row--) { // -idx -last
			vector<int> vtmp = triangle[row];
			for (int col = 0; col < vtmp.size(); col++) {
				vtmp[col] += min(v[col], v[col + 1]);
			}
			v = vtmp;
		}
		return v[0];
	}
};

/* 152. 乘积最大子序列（中等
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
class Solution152 {
public:
	int maxProduct(vector<int>& nums) {
		if (nums.empty()) return 0;

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
};

/* 121. 买卖股票的最佳时机（简单
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。
注意你不能在买入股票前卖出股票。

示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
	 注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
class Solution121 {
public:
	int maxProfit(vector<int>& prices) {
		//找最小值和最大峰值
		if (prices.empty()) return 0;
		int min_price = INT_MAX, max_profit = INT_MIN;
		for (int i = 1; i < prices.size(); i++) {
			const int &val = prices[i];
			min_price = min(min_price, val);
			max_profit = max(max_profit, val - min_price);
		}
		return max_profit;
	}
};

/* 122. 买卖股票的最佳时机 II（简单
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
class Solution122 {
public:
	int maxProfit(vector<int>& prices) {
		int ret = 0;
		for (int i = 1; i < prices.size(); i++) {
			int profit = prices[i] - prices[i - 1];
			if (profit > 0)
				ret += profit;
		}
		return ret;
	}
};

/* 123. 买卖股票的最佳时机 III（困难
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [3,3,5,0,0,3,1,4]
输出: 6
解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

示例 2:
输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。  
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。  
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:
输入: [7,6,4,3,1]
输出: 0
解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。
*/
class Solution123 {
public:
	int maxProfit(vector<int>& prices) {

	}
};

/* 309. 最佳买卖股票时机含冷冻期（中等
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

示例:
输入: [1,2,3,0,2]
输出: 3
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
*/
class Solution309 {
public:
	int maxProfit(vector<int>& prices) {

	}
};

/* 188. 买卖股票的最佳时机 IV（困难
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [2,4,1], k = 2
输出: 2
解释: 在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。

示例 2:
输入: [3,2,6,5,0,3], k = 2
输出: 7
解释: 在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
*/
class Solution188 {
public:
	int maxProfit(int k, vector<int>& prices) {

	}
};

/* 714. 买卖股票的最佳时机含手续费（中等
给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每次交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。

示例 1:
输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
输出: 8
解释: 能够达到的最大利润:
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

注意:
0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.
*/
class Solution714 {
public:
	int maxProfit(vector<int>& prices, int fee) {

	}
};

/* 300. 最长上升子序列（中等
给定一个无序的整数数组，找到其中最长上升子序列的长度。

示例:
输入: [10,9,2,5,3,7,101,18]
输出: 4
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。

说明:
可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为 O(n2) 。
进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?
*/
class Solution300 {
public:
	int lengthOfLIS(vector<int>& nums) {
		/*
		执行用时 :96 ms, 在所有 C++ 提交中击败了19.18%的用户
		内存消耗 :8.5 MB, 在所有 C++ 提交中击败了71.57%的用户
		*/
		int sz = nums.size();
		if (sz < 2) return sz;
		vector<int> dp(sz, 1);
		int imax = 1;
		for (int i = 1; i < sz; i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1); //保存之前的最长
					imax = max(imax, dp[i]);
				}
			}
		}
		return imax;
	}
};

/* 322. 零钱兑换（中等
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。

示例 1:
输入: coins = [1, 2, 5], amount = 11
输出: 3
解释: 11 = 5 + 5 + 1

示例 2:
输入: coins = [2], amount = 3
输出: -1
说明:
你可以认为每种硬币的数量是无限的。
*/
class Solution322 {
public:
	int coinChange(vector<int>& coins, int amount) {
		int imin = INT_MAX;
		for (auto coin : coins) {
			if (coin > amount) continue;
			int sub_min = coinChange(coins, amount - coin);
			if (sub_min == -1) continue;
			imin = min(imin, sub_min + 1); // 能写出来这行代码，就可以使用动态规划了
		}
		return (imin == INT_MAX ? -1 : imin);
	}

	int coinChange2(vector<int>& coins, int amount) {
		/*
		执行用时 :68 ms, 在所有 C++ 提交中击败了78.13%的用户
		内存消耗 :12.4 MB, 在所有 C++ 提交中击败了82.03%的用户
		*/
		vector<int> dp(amount + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 1; i <= amount; i++) {
			for (auto coin : coins) {
				if (coin > i) continue;
				dp[i] = min(dp[i], dp[i - coin] + 1); // 动态规划
			}
		}
		return (dp[amount] == INT_MAX ? -1 : dp[amount]);
	}
};

/* 72. 编辑距离（困难
给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符

示例 1:
输入: word1 = "horse", word2 = "ros"
输出: 3
解释:
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2:
输入: word1 = "intention", word2 = "execution"
输出: 5
解释:
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
*/
class Solution72 {
public:
	int minDistance(string word1, string word2) {

	}
};



void Test::Dynamic()
{

}
