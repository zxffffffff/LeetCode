#include "pch.h"
#include "Test.h"

using namespace std;


// LeetCode 链表节点

/* 206. 反转链表
* 题目比较简单，所以不光是考察思考能力，更注重考察代码的实现能力，需要简洁
*/
ListNode* reverseList3(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *pCur = head;
	ListNode *pNext = pCur->next;
	ListNode *pNext2;
	head->next = NULL;
	while (pNext != NULL) {
		pNext2 = pNext->next;
		pNext->next = pCur;
		pCur = pNext;
		pNext = pNext2;
	}
	return pCur;
}

/* 24. 两两交换链表中的节点
* 同样，对思维要求不高，对代码要求很高
*/
ListNode* swapPairs2(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *pPrev = NULL;
	ListNode *pCur = head;
	ListNode *pNext = pCur->next;
	while (pNext != NULL) {
		pCur->next = pNext->next;
		pNext->next = pCur;

		ListNode *pSwapCur = pNext;
		ListNode *pSwapNext = pCur;
		if (pPrev != NULL)
			pPrev->next = pSwapCur;
		else
			head = pSwapCur;

		pPrev = pSwapNext;
		pCur = pSwapNext->next;
		if (pCur != NULL)
			pNext = pCur->next;
		else
			break;
	}
	return head;
}

/* 141. 环形链表
* 列出解法，然后选择最优解，考察思路和代码能力
*/
bool hasCycle2(ListNode *head) {
	//set<ListNode *> setFlag;
	//ListNode *p = head;
	//while (p != NULL) {
	//	auto ite = setFlag.find(p);
	//	if (ite != setFlag.end())
	//		return true;
	//	else
	//		setFlag.insert(p);
	//	p = p->next;
	//}
	//return false;

	// 经典解法：快慢指针（龟兔赛跑）
	if (head == NULL || head->next == NULL)
		return false;
	if (head->next == head)
		return true;
	ListNode *pFast = head->next->next;
	ListNode *pSlow = head->next;

	while (pFast != NULL && pSlow != NULL) {
		if (pFast == pSlow)
			return true;
		
		if (pFast->next == NULL)
			return false;
		pFast = pFast->next->next;
		pSlow = pSlow->next;
	}
	return false;
}



