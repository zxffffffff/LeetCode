#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
//#include <hash_map>  // ����ɾ��,��Ϊunordered_map
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <bitset> // std::bitset<32> b1(0xff);
#include <math.h> // �ݡ�n�η�

/* 
* https://leetcode-cn.com/
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Test
{
public:
	Test();
	~Test();

	void Strings();
	void HashTable();
	void Tree();
	void Dynamic();
	void Interview();
};
