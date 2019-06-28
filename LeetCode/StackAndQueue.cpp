#include "pch.h"
#include "Test.h"

using namespace std;

/* 20. 有效的括号
* 标准解答：堆栈实现
*/
bool isValid2(string s) {
	// 通过map来存放左右括号
	stack<char> stackTmp;
	map<char, char> mapDic;
	mapDic[')'] = '(';
	mapDic[']'] = '[';
	mapDic['}'] = '{';
	for (int i = 0; i < s.length(); i++) {
		auto ite = mapDic.find(s[i]);
		if (ite != mapDic.end()) {
			if (stackTmp.empty())
				return false;
			if (stackTmp.top() != ite->second)
				return false;
			stackTmp.pop();
		}
		else {
			stackTmp.push(s[i]);
		}
	}
	return (0 == stackTmp.size());
}

/* 232. 用栈实现队列
* 标准解答：两个堆栈实现，当需要pop或者peek的时候，才用讲input导入到output去反向输出
*/
class MyQueue {
public:
	void push(int x) {
		input.push(x);
	}

	int pop() {
		o2i();
		int ret = output.top();
		output.pop();
		return ret;
	}

	int peek() {
		o2i();
		return output.top();
	}

	bool empty() {
		return (input.empty() && output.empty());
	}

private:
	stack<int> input;
	stack<int> output;

	void o2i() {
		if (!output.empty())
			return;
		while (!input.empty()) {
			output.push(input.top());
			input.pop();
		}
	}
};

/* 225. 用队列实现栈
* 同上，两个队列相互倒
*/
class MyStack {
public:
	MyStack() {
		input = new queue<int>;
		output = new queue<int>;
	}
	~MyStack() {
		delete input;
		delete output;
	}

	void push(int x) {
		input->push(x);
		q2q(output, input);
		std::swap(input, output);
	}

	int pop() {
		int ret = output->front();
		output->pop();
		return ret;
	}

	int top() {
		return output->front();
	}

	bool empty() {
		return (input->empty() && output->empty());
	}

private:
	queue<int> *input;
	queue<int> *output;

	void q2q(queue<int> *a, queue<int> *b) {
		while (!a->empty()) {
			b->push(a->front());
			a->pop();
		}
	}
};

