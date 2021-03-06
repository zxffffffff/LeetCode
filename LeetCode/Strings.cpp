#include "pch.h"
#include "Test.h"

using namespace std;



/* 804. 唯一摩尔斯密码词
国际摩尔斯密码定义一种标准编码方式，将每个字母对应于一个由一系列点和短线组成的字符串， 
比如: "a" 对应 ".-", "b" 对应 "-...", "c" 对应 "-.-.", 等等。

为了方便，所有26个英文字母对应摩尔斯密码表如下：
[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
给定一个单词列表，每个单词可以写成每个字母对应摩尔斯密码的组合。
例如，"cab" 可以写成 "-.-..--..."，(即 "-.-." + "-..." + ".-"字符串的结合)。
我们将这样一个连接过程称作单词翻译。返回我们可以获得所有词不同单词翻译的数量。

例如:
输入: words = ["gin", "zen", "gig", "msg"]
输出: 2
解释: 
各单词翻译如下:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."
共有 2 种不同翻译, "--...-." 和 "--...--.".

注意:
单词列表words 的长度不会超过 100。
每个单词 words[i]的长度范围为 [1, 12]。
每个单词 words[i]只包含小写字母。
*/
int uniqueMorseRepresentations(vector<string>& words) {
	string v[] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.." };
	set<string> setMorse;
	for (const auto &word : words) {
		string morse;
		for (const auto &c : word) {
			morse += v[c - 'a'];
		}
		setMorse.insert(morse);
	}
	return setMorse.size();
}


/////////////////////////////////////////////// 70%


/* 22. 括号生成
给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
bracket
例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/
void calc(vector<string> &vec, int l, int r, string str) {
	if (l == 0 && r >= 0) {
		while (r > 0) { // 简单优化一下
			str += ")";
			r--;
		}
		vec.push_back(str);
	}
	else if (l == r) {
		calc(vec, l - 1, r, str + "(");
	}
	else {
		if(l > 0) calc(vec, l - 1, r, str + "(");
		if(r > 0) calc(vec, l, r - 1, str + ")");
	}
}
vector<string> generateParenthesis2(int n) {
	vector<string> vecStr;
	if (n < 1)
		return vecStr;

	int l = n, r = n;
	calc(vecStr, l, r, "");
	return vecStr;
}


/* 657. 机器人能否返回原点
在二维平面上，有一个机器人从原点 (0, 0) 开始。
给出它的移动顺序，判断这个机器人在完成移动后是否在 (0, 0) 处结束。
移动顺序由字符串表示。字符 move[i] 表示其第 i 次移动。
机器人的有效动作有 R（右），L（左），U（上）和 D（下）。
如果机器人在完成所有动作后返回原点，则返回 true。否则，返回 false。

注意：机器人“面朝”的方向无关紧要。 
“R” 将始终使机器人向右移动一次，“L” 将始终向左移动等。
此外，假设每次移动机器人的移动幅度相同。

输入: "UD"
输出: true
解释：机器人向上移动一次，然后向下移动一次。
所有动作都具有相同的幅度，因此它最终回到它开始的原点。因此，我们返回 true。

输入: "LL"
输出: false
解释：机器人向左移动两次。它最终位于原点的左侧，距原点有两次 “移动” 的距离。
我们返回 false，因为它在移动结束时没有返回原点。
*/
bool judgeCircle(string moves) {
	int x = 0, y = 0;
	for (const auto c : moves) {
		switch (c) {
		case 'L':
			x--;
			break;
		case 'R':
			x++;
			break;
		case 'U':
			y++;
			break;
		case 'D':
			y--;
			break;
		}
	}
	return (x == 0 && y == 0);
}


/* 929. 独特的电子邮件地址
每封电子邮件都由一个本地名称和一个域名组成，以 @ 符号分隔。
例如，在 alice@leetcode.com中， alice 是本地名称，而 leetcode.com 是域名。
除了小写字母，这些电子邮件还可能包含 '.' 或 '+'。

如果在电子邮件地址的本地名称部分中的某些字符之间添加句点（'.'），
则发往那里的邮件将会转发到本地名称中没有点的同一地址。
例如，"alice.z@leetcode.com” 和 “alicez@leetcode.com” 会转发到同一电子邮件地址。 
（请注意，此规则不适用于域名。）

如果在本地名称中添加加号（'+'），则会忽略第一个加号后面的所有内容。
这允许过滤某些电子邮件，例如 m.y+name@email.com 将转发到 my@email.com。
（同样，此规则不适用于域名。）

可以同时使用这两个规则。

给定电子邮件列表 emails，我们会向列表中的每个地址发送一封电子邮件。实际收到邮件的不同地址有多少？

提示：
1 <= emails[i].length <= 100
1 <= emails.length <= 100
每封 emails[i] 都包含有且仅有一个 '@' 字符。
 
输入：["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
输出：2
解释：实际收到邮件的是 "testemail@leetcode.com" 和 "testemail@lee.tcode.com"。
*/
int numUniqueEmails(vector<string>& emails) {
	set<string> setEmails;
	for (const auto &email : emails) {
		bool flagAt = false;
		bool flagAdd = false;
		string convert;
		for (const auto &c : email) {
			if (!flagAt) {
				if (c == '@')
					flagAt = true;
				else if (c == '.')
					continue;
				else if (c == '+')
					flagAdd = true;
				if (flagAdd && !flagAt)
					continue;
			}
			convert.push_back(c);
		}
		setEmails.insert(convert);
	}
	return setEmails.size();
}



/* 890. 查找和替换模式
你有一个单词列表 words 和一个模式  pattern，你想知道 words 中的哪些单词与模式匹配。

如果存在字母的排列 p ，使得将模式中的每个字母 x 替换为 p(x) 之后，
我们就得到了所需的单词，那么单词与模式是匹配的。

（回想一下，字母的排列是从字母到字母的双射：每个字母映射到另一个字母，没有两个字母映射到同一个字母。）

返回 words 中与给定模式匹配的单词列表。你可以按任何顺序返回答案。

提示：
1 <= words.length <= 50
1 <= pattern.length = words[i].length <= 20

输入：words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
输出：["mee","aqq"]
解释：
"mee" 与模式匹配，因为存在排列 {a -> m, b -> e, ...}。
"ccc" 与模式不匹配，因为 {a -> c, b -> c, ...} 不是排列。
因为 a 和 b 映射到同一个字母。
*/
vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
	vector<string> vecWords;
	for (auto & word : words) {
		if(word.length() != pattern.length())
			break;

		bool flag = false;
		map<char, char> mapFilter;
		set<char> setFilter;

		for (int i = 0; i < word.length(); i++) {
			char c1 = pattern[i];
			char c2 = word[i];
			auto ite = mapFilter.find(c1);
			if (ite != mapFilter.end()) {
				if (ite->second != c2) {
					flag = true;
					break;
				}
			}
			else {
				const int siz = setFilter.size();
				setFilter.insert(c2);
				if (siz == setFilter.size()) {
					flag = true;
					break;
				}
				mapFilter[c1] = c2;
			}
		}

		if(!flag)
			vecWords.push_back(word);
	}
	return vecWords;
}



/* 557. 反转字符串中的单词 III
给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
注意：在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。

输入: "Let's take LeetCode contest"
输出: "s'teL ekat edoCteeL tsetnoc" 
*/
string reverseWords(string s) {
	int l = 0, r = 0;
	const int siz = s.length();
	for (int i = 0; i < siz; i++) {
		if (s[i] == ' ' || i == siz - 1) {
			if (s[i] == ' ')
				r = i - 1;
			else
				r = i;

			if (r != l) {
				while (r > l) {
					std::swap(s[l], s[r]);
					l++;
					r--;
				}
			}
			l = r = i + 1;
		}
	}
	return s;
}



/* 537. 复数乘法
给定两个表示复数的字符串。返回表示它们乘积的字符串。注意，根据定义 i2 = -1 。
注意:
输入字符串不包含额外的空格。
输入字符串将以 a+bi 的形式给出，其中整数 a 和 b 的范围均在 [-100, 100] 之间。输出也应当符合这种形式。

输入: "1+1i", "1+1i"
输出: "0+2i"
解释: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i ，你需要将它转换为 0+2i 的形式。

"2+3i", "4+5i"
(2 + 3i) * (4 + 5i) = 2*4 - （2*5 + 4*3）i + （3*5）i2
*/
string complexNumberMultiply(string a, string b) {
	auto split = [](const string& s, char c) {
		vector<string> v;
		string tmp;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == c) {
				v.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp.push_back(s[i]);
			}
		}
		if (tmp.length() > 0)
			v.push_back(tmp);
		return v;
	};

	int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
	a.pop_back(); // 去'i'
	b.pop_back();
	vector<string> va = split(a, '+');
	vector<string> vb = split(b, '+');
	a1 = stoi(va[0]);
	a2 = stoi(va[1]);
	b1 = stoi(vb[0]);
	b2 = stoi(vb[1]);

	stringstream ss;
	ss << to_string(a1 * b1 - a2 * b2) << '+' << to_string(a1 * b2 + a2 * b1) << 'i';
	return ss.str();
}





/* 521. 最长特殊序列 Ⅰ
给定两个字符串，你需要从这两个字符串中找出最长的特殊序列。
最长特殊序列定义如下：该序列为某字符串独有的最长子序列（即不能是其他字符串的子序列）。

子序列可以通过删去字符串中的某些字符实现，但不能改变剩余字符的相对顺序。
空序列为所有字符串的子序列，任何字符串为其自身的子序列。

输入为两个字符串，输出最长特殊序列的长度。如果不存在，则返回 -1。

输入: "aba", "cdc"
输出: 3
解析: 最长特殊序列可为 "aba" (或 "cdc")
说明:

两个字符串长度均小于100。
字符串中的字符仅含有 'a'~'z'。
*/
int findLUSlength(string a, string b) {
	// 脑经急转弯，傻逼题
	if (a == b)
		return -1;
	else
		return a.length() >= b.length() ? a.length() : b.length();
}





/* 791. 自定义字符串排序
字符串S和 T 只包含小写字符。在S中，所有字符只会出现一次。

S 已经根据某种规则进行了排序。我们要根据S中的字符顺序对T进行排序。
更具体地说，如果S中x在y之前出现，那么返回的字符串中x也应出现在y之前。

返回任意一种符合条件的字符串T。

示例:
输入:
S = "cba"
T = "abcd"
输出: "cbad"
解释: 
S中出现了字符 "a", "b", "c", 所以 "a", "b", "c" 的顺序应该是 "c", "b", "a". 
由于 "d" 没有在S中出现, 它可以放在T的任意位置. "dcba", "cdba", "cbda" 都是合法的输出。
注意:

S的最大长度为26，其中没有重复的字符。
T的最大长度为200。
S和T只包含小写字符。
*/
string customSortString(string S, string T) {
	int dic[26] = { 0 };
	string custom;
	for (auto c : T) {	// T 中出现次数
		dic[c - 'a']++;
	}
	for (auto c : S) {
		for (int i = 0; i < dic[c - 'a']; i++) // S 出现的字符先填上
			custom.push_back(c);
		dic[c - 'a'] = 0;
	}
	for (int i = 0; i < 26; i++) { // S 没出线的字符的往后面加
		for (int j = 0; j < dic[i]; j++)
			custom.push_back('a' + i);
	}
	return custom;
}






///////////////////////////////// 60% 



/* 893. 特殊等价字符串组
你将得到一个字符串数组 A。返回 A 中特殊等价字符串组的数量。

现在规定，A 中的特殊等价字符串组是 A 的非空子集 S，
这样不在 S 中的任何字符串与 S 中的任何字符串都不是特殊等价的。

如果经过任意次数的移动，S == T，那么两个字符串 S 和 T 是特殊等价的。
一次移动包括选择两个索引 i 和 j，且 i ％ 2 == j ％ 2，并且交换 S[j] 和 S [i]。

提示：
1 <= A.length <= 1000
1 <= A[i].length <= 20
所有 A[i] 都具有相同的长度。
所有 A[i] 都只由小写字母组成。

输入：["a","b","c","a","c","c"]
输出：3
解释：3 组 ["a","a"]，["b"]，["c","c","c"]

输入：["aa","bb","ab","ba"]
输出：4
解释：4 组 ["aa"]，["bb"]，["ab"]，["ba"]

输入：["abc","acb","bac","bca","cab","cba"]
输出：3
解释：3 组 ["abc","cba"]，["acb","bca"]，["bac","cab"]

输入：["abcd","cdab","adcb","cbad"]
输出：1
解释：1 组 ["abcd","cdab","adcb","cbad"]
*/
int numSpecialEquivGroups(vector<string>& A) {
	set<string> setHash;
	const int SIZ = 26 * 2;
	for (auto &str : A) {
		char aHash[SIZ + 1];
		memset(aHash, 'a', SIZ); // 非0都行
		aHash[SIZ] = '\0';
		for (int i = 0; i < str.length(); i++) {
			// 哈希表，存26个单数，26个双数
			aHash[str[i] - 'a' + (i % 2) * 26]++;
		}
		setHash.insert(aHash);
	}
	return setHash.size();
}





/* 12. 整数转罗马数字
罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个整数，将其转为罗马数字。输入确保在 1 到 3999 的范围内。

输入: 3
输出: "III"

输入: 4
输出: "IV"

输入: 9
输出: "IX"

输入: 58
输出: "LVIII"
解释: L = 50, V = 5, III = 3.

输入: 1994
输出: "MCMXCIV"
解释: M = 1000, CM = 900, XC = 90, IV = 4.
*/
string intToRoman(int num) {
	char dic[7] = {'I','V','X','L','C','D','M'};
	int flag = 0;
	string roman;
	while (num > 0)
	{
		string tmp;
		const int last = num % 10;
		if (last == 0) {
			
		}
		else if (last <= 3) {
			// 1,2,3
			for (int i = 0; i < last; i++)
				tmp += dic[flag * 2];
		}
		else if (last <= 5) {
			// 4,5
			for (int i = 0; i < 5 - last; i++)
				tmp += dic[flag * 2];
			tmp += dic[flag * 2 + 1];
		}
		else if (last <= 8) {
			// 6,7,8
			tmp += dic[flag * 2 + 1];
			for (int i = 0; i < last - 5; i++)
				tmp += dic[flag * 2];
		}
		else {
			// 9
			tmp += dic[flag * 2];
			tmp += dic[flag * 2 + 2];
		}
		roman = tmp + roman;
		flag++;
		num /= 10;
	}
	return roman;
}



/* 13. 罗马数字转整数
罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。

示例 1:

输入: "III"
输出: 3
示例 2:

输入: "IV"
输出: 4
示例 3:

输入: "IX"
输出: 9
示例 4:

输入: "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.
示例 5:

输入: "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.
*/
int romanToInt(string s) {
	map<char, int> m;
	m['I'] = 1;
	m['V'] = 5;
	m['X'] = 10;
	m['L'] = 50;
	m['C'] = 100;
	m['D'] = 500;
	m['M'] = 1000;
	int sum = 0;
	int nPrev = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		int nCur = m[s[i]];
		if (nCur < nPrev) {
			// 需要做减法的情况
			sum -= nCur;
		}
		else {
			// 直接加
			sum += nCur;
		}
		nPrev = nCur;
	}
	return sum;
}



/* 609. 在系统中查找重复文件
给定一个目录信息列表，包括目录路径，以及该目录中的所有包含内容的文件，
您需要找到文件系统中的所有重复文件组的路径。一组重复的文件至少包括二个具有完全相同内容的文件。

输入列表中的单个目录信息字符串的格式如下：

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

这意味着有 n 个文件（f1.txt, f2.txt ... fn.txt 的内容分别是 f1_content, f2_content ... fn_content）
在目录 root/d1/d2/.../dm 下。
注意：n>=1 且 m>=0。如果 m=0，则表示该目录是根目录。

该输出是重复文件路径组的列表。对于每个组，它包含具有相同内容的文件的所有文件路径。
文件路径是具有下列格式的字符串：
"directory_path/file_name.txt"

输入：
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
输出：
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]

注：
最终输出不需要顺序。
您可以假设目录名、文件名和文件内容只有字母和数字，并且文件内容的长度在 [1，50] 的范围内。
给定的文件数量在 [1，20000] 个范围内。
您可以假设在同一目录中没有任何文件或目录共享相同的名称。
您可以假设每个给定的目录信息代表一个唯一的目录。目录路径和文件信息用一个空格分隔。


超越竞赛的后续行动：

假设您有一个真正的文件系统，您将如何搜索文件？广度搜索还是宽度搜索？
如果文件内容非常大（GB级别），您将如何修改您的解决方案？
如果每次只能读取 1 kb 的文件，您将如何修改解决方案？
修改后的解决方案的时间复杂度是多少？其中最耗时的部分和消耗内存的部分是什么？如何优化？
如何确保您发现的重复文件不是误报？
*/
vector<vector<string>> findDuplicate(vector<string>& paths) {
	auto splitStr = [](const string& s, char c) {
		vector<string> v;
		string tmp;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == c) {
				v.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp.push_back(s[i]);
			}
		}
		if (tmp.length() > 0)
			v.push_back(tmp);
		return v;
	};
	auto splitBracket = [](string &input, string &l, string &r) {
		input.pop_back(); // ')'
		l.clear();
		r.clear();
		bool flag = false;
		for (auto c:input) {
			if (c == '(') {
				flag = true;
				continue;
			}
			if (flag)
				r.push_back(c);
			else
				l.push_back(c);
		}
	};

	map<string, vector<string>> mapData;
	for (auto path : paths) {
		// "root/a 1.txt(abcd) 2.txt(efgh)"
		vector<string> vStr = splitStr(path, ' ');
		for (int i = 1; i < vStr.size(); i++) {
			string filename, data;
			splitBracket(vStr[i], filename, data);
			mapData[data].push_back(vStr[0] + '/' + filename);
		}
	}
	vector<vector<string>> vRet;
	for (auto ite = mapData.begin(); ite != mapData.end(); ite++) {
		const auto &v = (*ite).second;
		if(v.size() > 1)
			vRet.push_back(v); // 输出重复
	}
	return vRet;
}






/* 49. 字母异位词分组
给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

所有输入均为小写字母。
不考虑答案输出的顺序。

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	/*
		效率低？超过10%的人...
	*/
	vector<vector<string>> vRet;
	map<string, int> mapHash; // hash : vRet::index
	for (auto &str : strs) {
		int aHash[26] = { 0 };
		for (auto c : str)
			aHash[c - 'a']++;
		string sHash;
		for (int i = 0; i < 26; i++)
			sHash += to_string(aHash[i]);

		auto ite = mapHash.find(sHash);
		if (ite != mapHash.end()) {
			vRet[(*ite).second].push_back(str); // 这里总是不进来
		}
		else {
			int index = vRet.size();
			mapHash[sHash] = index;

			vector<string> v;
			v.push_back(str);
			vRet.push_back(v);
		}
	}
	return vRet;
}



/* 824. 山羊拉丁文
给定一个由空格分割单词的句子 S。每个单词只包含大写或小写字母。

我们要将句子转换为 “Goat Latin”（一种类似于 猪拉丁文 - Pig Latin 的虚构语言）。

山羊拉丁文的规则如下：

如果单词以元音开头（a, e, i, o, u），在单词后添加"ma"。
例如，单词"apple"变为"applema"。

如果单词以辅音字母开头（即非元音字母），移除第一个字符并将它放到末尾，之后再添加"ma"。
例如，单词"goat"变为"oatgma"。

根据单词在句子中的索引，在单词最后添加与索引相同数量的字母'a'，索引从1开始。
例如，在第一个单词后添加"a"，在第二个单词后添加"aa"，以此类推。
返回将 S 转换为山羊拉丁文后的句子。

示例 1:

输入: "I speak Goat Latin"
输出: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
示例 2:

输入: "The quick brown fox jumped over the lazy dog"
输出: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
说明:

S 中仅包含大小写字母和空格。单词间有且仅有一个空格。1
1 <= S.length <= 150。
*/
string toGoatLatin(string S) {
	auto split = [](const string& s, char c) {
		vector<string> v;
		string tmp;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == c) {
				v.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp.push_back(s[i]);
			}
		}
		if (tmp.length() > 0)
			v.push_back(tmp);
		return v;
	};

	vector<string> vcStr = split(S, ' ');
	for (int i = 0; i < vcStr.size(); i++) {
		if(vcStr[i].size() <= 0)
			continue;
		switch (vcStr[i][0])
		{
		case 'a':case 'e':case 'i':case 'o':case 'u':
		case 'A':case 'E':case 'I':case 'O':case 'U':
			break;
		default:
			for (int j = 1; j < vcStr[i].size(); j++) {
				std::swap(vcStr[i][j], vcStr[i][j - 1]); //首字母移到最后
			}
			break;
		}
		vcStr[i] += 'm';
		for (int j = -2; j < i; j++)
			vcStr[i] += 'a';
	}

	S.clear();
	for (int i = 0; i < vcStr.size(); i++) {
		S += vcStr[i];
		if (i != vcStr.size() - 1)
			S += ' ';
	}

	return S;
}


/* 788. 旋转数字
我们称一个数 X 为好数, 如果它的每位数字逐个地被旋转 180 度后，
我们仍可以得到一个有效的，且和 X 不同的数。要求每位数字都要被旋转。

如果一个数的每位数字被旋转以后仍然还是一个数字， 则这个数是有效的。
0, 1, 和 8 被旋转后仍然是它们自己；2 和 5 可以互相旋转成对方；
6 和 9 同理，除了这些以外其他的数字旋转以后都不再是有效的数字。

现在我们有一个正整数 N, 计算从 1 到 N 中有多少个数 X 是好数？
输入: 10
输出: 4
在[1, 10]中有四个好数： 2, 5, 6, 9。
注意 1 和 10 不是好数, 因为他们在旋转之后不变。
注意:

N 的取值范围是 [1, 10000]。
*/
int rotatedDigits(int N) {
	auto check = [](int n) {
		string S = to_string(n);
		bool flag = false;
		for (int i = 0; i < S.size(); ++i) {
			switch (S[i])
			{
			case '0': break;
			case '1': break;
			case '2': flag = true; break;
			case '3': return false;
			case '4': return false;
			case '5': flag = true; break;
			case '6': flag = true; break;
			case '7': return false;
			case '8': break;
			case '9': flag = true; break;
			}
		}
		return flag;
	};

	int res = 0;
	for (int i = 0; i <= N; i++) { // 解答都是直接遍历。。。
		if (check(i))
			res++;
	}
	return res;
}




/* 1016. 子串能表示从 1 到 N 数字的二进制串
给定一个二进制字符串 S（一个仅由若干 '0' 和 '1' 构成的字符串）和一个正整数 N，
如果对于从 1 到 N 的每个整数 X，其二进制表示都是 S 的子串，就返回 true，否则返回 false。

示例 1：
输入：S = "0110", N = 3
输出：true

示例 2：
输入：S = "0110", N = 4
输出：false

提示：
1 <= S.length <= 1000
1 <= N <= 10^9
*/
bool queryString(string S, int N) {
	// 暴力枚举？
	return true;
}














/* 647. 回文子串
给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。

示例 1:

输入: "abc"
输出: 3
解释: 三个回文子串: "a", "b", "c".
示例 2:

输入: "aaa"
输出: 6
说明: 6个回文子串: "a", "a", "a", "aa", "aa", "aaa".
注意:

输入的字符串长度不会超过1000。
*/
int countSubstrings(string s) {
	//LeetCode一种解法，动态规划很厉害

	int m = s.size();
	vector<vector<int>>dp(m, vector<int>(m, 0));
	for (int i = 0; i < m; i++)
		dp[i][i] = 1;
	//从后往前计算，可以先得出dp[i+1][j-1]的值，
	//不需要重复计算
	for (int i = m - 2; i >= 0; i--)
	{
		for (int j = i + 1; j < m; j++)
		{
			//两个元素相邻
			if (j - i == 1)
				dp[i][j] = s[i] == s[j];
			else
				//至少i和j之间三个元素
				dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
		}
	}
	int count = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (dp[i][j]) count++;
		}
	}
	return count;
}


/* 520. 检测大写字母
给定一个单词，你需要判断单词的大写使用是否正确。

我们定义，在以下情况时，单词的大写用法是正确的：

全部字母都是大写，比如"USA"。
单词中所有字母都不是大写，比如"leetcode"。
如果单词不只含有一个字母，只有首字母大写， 比如 "Google"。
否则，我们定义这个单词没有正确使用大写字母。

示例 1:

输入: "USA"
输出: True
示例 2:

输入: "FlaG"
输出: False
注意: 输入是由大写和小写拉丁字母组成的非空单词。
*/
bool detectCapitalUse(string word) {
	int uppercase = 0;
	for(int i=0; i<word.length(); i++)
	{
		auto c = word[i];
		if (c >= 'A' && c <= 'Z') {
			if (i == 0) {
				uppercase++;
			}
			else if (uppercase == i) {
				uppercase++;
			}
			else {
				return false;
			}
		}
		else if (c >= 'a' &&c <= 'z') {
			if (uppercase == i && i > 1)
				return false;
		}
	}
	return true;
}




/* 553. 最优除法
给定一组正整数，相邻的整数之间将会进行浮点除法操作。例如， [2,3,4] -> 2 / 3 / 4 。

但是，你可以在任意位置添加任意数目的括号，来改变算数的优先级。
你需要找出怎么添加括号，才能得到最大的结果，并且返回相应的字符串格式的表达式。
你的表达式不应该含有冗余的括号。

示例：

输入: [1000,100,10,2]
输出: "1000/(100/10/2)"
解释:
1000/(100/10/2) = 1000/((100/10)/2) = 200
但是，以下加粗的括号 "1000/((100/10)/2)" 是冗余的，
因为他们并不影响操作的优先级，所以你需要返回 "1000/(100/10/2)"。

其他用例:
1000/(100/10)/2 = 50
1000/(100/(10/2)) = 50
1000/100/10/2 = 0.5
1000/100/(10/2) = 2
说明:

输入数组的长度在 [1, 10] 之间。
数组中每个元素的大小都在 [2, 1000] 之间。
每个测试用例只有一个最优除法解。
*/
string optimalDivision(vector<int>& nums) {
	/*
	一组括号把从第二个数开始的所有数括起来就好了 66666
	*/

	string out;
	const int sz = nums.size();
	if (sz == 0)
		return out;

	out = to_string(nums[sz - 1]);
	if (sz == 1)
		return out;

	for (int i = sz - 2; i >= 0; i--)
	{
		if (i == 1)
			out = '(' + to_string(nums[i]) + '/' + out + ')';
		else
			out = to_string(nums[i]) + '/' + out;
	}
	return out;
}


/* 761. 特殊的二进制序列
特殊的二进制序列是具有以下两个性质的二进制序列：

0 的数量与 1 的数量相等。
二进制序列的每一个前缀码中 1 的数量要大于等于 0 的数量。
给定一个特殊的二进制序列 S，以字符串形式表示。
定义一个操作 为首先选择 S 的两个连续且非空的特殊的子串，然后将它们交换。
（两个子串为连续的当且仅当第一个子串的最后一个字符恰好为第二个子串的第一个字符的前一个字符。)

在任意次数的操作之后，交换后的字符串按照字典序排列的最大的结果是什么？

示例 1:

输入: S = "11011000"
输出: "11100100"
解释:
将子串 "10" （在S[1]出现） 和 "1100" （在S[3]出现）进行交换。
这是在进行若干次操作后按字典序排列最大的结果。
说明:

S 的长度不超过 50。
S 保证为一个满足上述定义的特殊 的二进制序列。
*/
string makeLargestSpecial(string S) {
	//结果不对？？？
	/*
	auto generate = [](vector<pair<string, int>> &vc, int &zero, int &one) {
		string s0, s1;

		if (zero < one) {
			while (zero < one--)
				s1 += '1';
			one++;
			pair<string, int> pr(s1, INT_MAX);
			vc.push_back(pr);
			s1.clear();
		}

		if (0 < one) {
			while (0 < one) {
				s0 += '0'; one--;
				s1 += '1'; zero--;
			}
			pair<string, int> pr(s1 + s0, s1.length());
			vc.push_back(pr);
		}

		if (0 < zero) {
			s0.clear();
			while (0 < zero--)
				s0 += '0';
			pair<string, int> pr(s0, 0);
			vc.push_back(pr);
		}

		one = zero = 0;
		return vc;
	};

	//拆分到vector
	vector<pair<string, int>> vc;
	int zero = 0, one = 0;
	for (auto c : S) {
		if (c == '1')
		{
			if (zero != 0)
			{
				generate(vc, zero, one);
			}
			one++;
		}
		else // c == '0'
		{
			zero++;
		}
	}
	generate(vc, zero, one);

	//冒泡交换
	for (int i = 0; i < vc.size(); i++) {
		if(vc[i].second == 0)
			continue;
		for (int j = i + 1; j < vc.size(); j++) {
			if(vc[j].second == 0)
				continue;;
			if (vc[i].second < vc[j].second)
				swap(vc[i], vc[j]);
		}
	}

	//合并
	string s;
	for (int i = 0; i < vc.size(); i++)
		s += vc[i].first;

	return s;
	*/
	return string();
}





/* 856. 括号的分数
给定一个平衡括号字符串 S，按下述规则计算该字符串的分数：

() 得 1 分。
AB 得 A + B 分，其中 A 和 B 是平衡括号字符串。
(A) 得 2 * A 分，其中 A 是平衡括号字符串。


输入： "()"
输出： 1

输入： "(())"
输出： 2

输入： "()()"
输出： 2

输入： "(()(()))"
输出： 6


提示：
S 是平衡括号字符串，且只含有 ( 和 ) 。
2 <= S.length <= 50
*/
int scoreOfParentheses(string S) {
	//将 (()(())) 拆成 (()) + ((()))
	int deep = 0, score = 0;
	for (int i = 0; i < S.size(); i++) {
		if (S[i] == '(') {
			deep++;
		}
		else {
			deep--;
			if (S[i - 1] == '(') {
				score += 1 << deep;
			}
		}
	}
	return score;
}






/* 937. 重新排列日志文件
你有一个日志数组 logs。每条日志都是以空格分隔的字串。

对于每条日志，其第一个字为字母数字标识符。然后，要么：

标识符后面的每个字将仅由小写字母组成，或；
标识符后面的每个字将仅由数字组成。
我们将这两种日志分别称为字母日志和数字日志。保证每个日志在其标识符后面至少有一个字。

将日志重新排序，使得所有字母日志都排在数字日志之前。字母日志按字母顺序排序，
忽略标识符，标识符仅用于表示关系。数字日志应该按原来的顺序排列。

返回日志的最终顺序。



示例 ：

输入：["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
输出：["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]


提示：

0 <= logs.length <= 100
3 <= logs[i].length <= 100
logs[i] 保证有一个标识符，并且标识符后面有一个字。
*/
vector<string> reorderLogFiles(vector<string>& logs) {
	auto isWord = [](const string &s) {
		int idx = s.find(' ') + 1;
		return (s[idx] >= 'a' && s[idx] <= 'z');
	};

	if (logs.size() <= 1)
		return logs;

	//将字母log取出来
	vector<string> logWord;
	for (int i = 0; i < logs.size(); i++) {
		if (isWord(logs[i])) {
			logWord.push_back(logs[i]);
			logs[i].clear();
		}
	}
	//对字母log排序
	sort(logWord.begin(), logWord.end(), [](string s1, string s2) {
		auto ite1 = find(s1.begin(), s1.end(), ' ');
		auto ite2 = find(s2.begin(), s2.end(), ' ');
		int ret = string(ite1, s1.end()).compare(string(ite2, s2.end())) < 0;
		if (ret == 0)
			ret = s1.compare(s2);
		return ret < 0;
		});
	//合并logs过来
	for (auto log : logs) {
		if(log.empty())
			continue;
		logWord.push_back(log);
	}
	return logWord;
}

//////////////////////////////////////// 50%


/* 67. 二进制求和
给定两个二进制字符串，返回他们的和（用二进制表示）。
输入为非空字符串且只包含数字 1 和 0。

示例 1:
输入: a = "11", b = "1"
输出: "100"

示例 2:
输入: a = "1010", b = "1011"
输出: "10101"
*/
string addBinary(string a, string b) {
	return "";
}


/* 917. 仅仅反转字母
给定一个字符串 S，返回 “反转后的” 字符串，其中不是字母的字符都保留在原地，而所有字母的位置发生反转。

提示：
S.length <= 100
33 <= S[i].ASCIIcode <= 122 
S 中不包含 \ or " 

示例 1：
输入："ab-cd"
输出："dc-ba"

示例 2：
输入："a-bC-dEf-ghIj"
输出："j-Ih-gfE-dCba"

示例 3：
输入："Test1ng-Leet=code-Q!"
输出："Qedo1ct-eeLg=ntse-T!"
*/
string reverseOnlyLetters(string S) {
	auto isLetter = [](char c) {
		if (c >= 'a' && c <= 'z')
			return true;
		if (c >= 'A' && c <= 'Z')
			return true;
		return false;
	};

	int len = S.length();
	int lo = 0;
	int hi = len - 1;
	while (lo < hi) {
		while (lo < hi && !isLetter(S[hi]))
			hi--;
		while (lo < hi && !isLetter(S[lo]))
			lo++;
		swap(S[hi], S[lo]);
		hi--;
		lo++;
	}
	return S;
}


/* 383. 赎金信
给定一个赎金信 (ransom) 字符串和一个杂志(magazine)字符串，判断第一个字符串ransom
能不能由第二个字符串magazines里面的字符构成。如果可以构成，返回 true ；否则返回 false。
(题目说明：为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。)

注意：
你可以假设两个字符串均只含有小写字母。

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
*/
bool canConstruct(string ransomNote, string magazine) {
	int hash[26] = { 0 };
	for (auto c : magazine)
		hash[c - 'a']++;
	for (auto c : ransomNote) {
		if (hash[c - 'a'] == 0)
			return false;
		hash[c - 'a']--;
	}
	return true;
}


/* 1023. 驼峰式匹配
如果我们可以将小写字母插入模式串 pattern 得到待查询项 query，那么待查询项与给定模式串匹配。
（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）

给定待查询列表 queries，和模式串 pattern，返回由布尔值组成的答案列表 answer。只有在待查项
 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。

示例 1：
输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
输出：[true,false,true,true,false]
示例：
"FooBar" 可以这样生成："F" + "oo" + "B" + "ar"。
"FootBall" 可以这样生成："F" + "oot" + "B" + "all".
"FrameBuffer" 可以这样生成："F" + "rame" + "B" + "uffer".

示例 2：
输入：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
输出：[true,false,true,false,false]
解释：
"FooBar" 可以这样生成："Fo" + "o" + "Ba" + "r".
"FootBall" 可以这样生成："Fo" + "ot" + "Ba" + "ll".

示例 3：
输出：queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
输入：[false,true,false,false,false]
解释： 
"FooBarTest" 可以这样生成："Fo" + "o" + "Ba" + "r" + "T" + "est".
 
提示：
1 <= queries.length <= 100
1 <= queries[i].length <= 100
1 <= pattern.length <= 100
所有字符串都仅由大写和小写英文字母组成。
*/
vector<bool> camelMatch(vector<string>& queries, string pattern) {
	auto isUpper = [](char c) {
		return (c >= 'A' && c <= 'Z');
	};

	vector<bool> vecRet;
	for (auto &query : queries) {
		int lp = 0, lq = 0;
		bool flag = true;
		
		//todo


		vecRet.push_back(flag);
	}
	return vecRet;
}

/* 539. 最小时间差
给定一个 24 小时制（小时:分钟）的时间列表，找出列表中任意两个时间的最小时间差并已分钟数表示。

示例 1：
输入: ["23:59","00:00"]
输出: 1

备注:
列表中时间数在 2~20000 之间。
每个时间取值在 00:00~23:59 之间。
*/
int findMinDifference(vector<string>& timePoints) {
	auto str2time = [](string &s) {
		return (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0') * 1;
	};
	auto getMin = [str2time](string &s1, string &s2) {
		int t1 = str2time(s1);
		int t2 = str2time(s2);
		int t = abs(abs(t1) - abs(t2));
		return min(t, 24 * 60 - t);
	};
	
	sort(timePoints.begin(), timePoints.end());
	auto len = timePoints.size();
	if (len < 1) 
		return 0;
	int nMin = getMin(timePoints[0], timePoints[len - 1]);
	for (int i = 1; i < len; i++) {
		nMin = min(nMin, getMin(timePoints[i], timePoints[i - 1]));
	}
	return nMin;
}


/* 551. 学生出勤记录 I
给定一个字符串来代表一个学生的出勤记录，这个记录仅包含以下三个字符：
'A' : Absent，缺勤
'L' : Late，迟到
'P' : Present，到场
如果一个学生的出勤记录中不超过一个'A'(缺勤)并且不超过两个连续的'L'(迟到),那么这个学生会被奖赏。
你需要根据这个学生的出勤记录判断他是否会被奖赏。

示例 1:
输入: "PPALLP"
输出: True

示例 2:
输入: "PPALLL"
输出: False
*/
bool checkRecord(string s) {
	int a = 0, l = 0;
	for (auto c : s) {
		if (c == 'A') {
			a++;
			l = 0;
		}
		else if (c == 'L')
			l++;
		else
			l = 0;

		if (a > 1 || l > 2)
			return false;
	}
	return true;
}


/* 541. 反转字符串 II
给定一个字符串和一个整数 k，你需要对从字符串开头算起的每个 2k 个字符的前k个字符进行反转。
如果剩余少于 k 个字符，则将剩余的所有全部反转。
如果有小于 2k 但大于或等于 k 个字符，则反转前 k 个字符，并将剩余的字符保持原样。

示例:
输入: s = "abcdefg", k = 2
输出: "bacdfeg"

要求:
该字符串只包含小写的英文字母。
给定字符串的长度和 k 在[1, 10000]范围内。
*/
string reverseStr(string s, int k) {
	return "";
}


/* 415. 字符串相加
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

注意：
num1 和num2 的长度都小于 5100.
num1 和num2 都只包含数字 0-9.
num1 和num2 都不包含任何前导零。
你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式。
*/
string addStrings(string num1, string num2) {
	reverse(num1.begin(), num1.end()); //可以优化 但是懒得改hah
	reverse(num2.begin(), num2.end());
	int len1 = num1.length();
	int len2 = num2.length();
	int len = max(len1, len2);
	string sret;
	int cur = 0;
	for (int i = 0; i < len; i++) {
		if (i < num1.length())
			cur += num1[i] - '0';
		if (i < num2.length())
			cur += num2[i] - '0';
		sret += (char)('0' + cur % 10);
		cur /= 10;
	}
	if(cur > 0)
		sret += (char)('0' + cur % 10); // '1'
	reverse(sret.begin(), sret.end());
	return sret;
}


/* 696. 计数二进制子串
给定一个字符串 s，计算具有相同数量0和1的非空(连续)子字符串的数量，
并且这些子字符串中的所有0和所有1都是组合在一起的。
重复出现的子串要计算它们出现的次数。

示例 1 :
输入: "00110011"
输出: 6
解释: 有6个子串具有相同数量的连续1和0：“0011”，“01”，“1100”，“10”，“0011” 和 “01”。
请注意，一些重复出现的子串要计算它们出现的次数。
另外，“00110011”不是有效的子串，因为所有的0（和1）没有组合在一起。

示例 2 :
输入: "10101"
输出: 4
解释: 有4个子串：“10”，“01”，“10”，“01”，它们具有相同数量的连续1和0。

注意：
s.length 在1到50,000之间。
s 只包含“0”或“1”字符。
*/
int countBinarySubstrings(string s) {

	int ret = 0;
	int len = s.length();
	for (int i = 0; i < len; i++) {
		string tmp;
		int flag = 0;
		for (int j = i; j < len; j++) {
			tmp += s[j];
			if (s[j] == '0') flag--;
			if (s[j] == '1') flag++;
			if (flag == 0 && !tmp.empty()) {
				ret++;
				break;
			}
		}
	}
	return ret;
}



/* 93. 复原IP地址
给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
示例:
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]
*/
class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> ret;
		DFS(s, 0, 0, "", ret);
		return ret;
	}
	void DFS(string s, int pos, int dots, string ip, vector<string> &ret) {
		if (dots < 3) { //前三个（012）
			for (int mv = 1; mv <= 3; mv++) {
				if(pos + mv >= s.length())
					break;
				string tmp = s.substr(pos, mv);
				if(!isvalid(tmp))
					continue;
				tmp = ip + tmp + '.';
				DFS(s, pos + mv, dots + 1, tmp, ret);
			}
		}
		else { //最后一个（3）
			int mv = s.length() - pos;
			string tmp = s.substr(pos, mv);
			if (!isvalid(tmp))
				return;
			ip += tmp;
			ret.push_back(ip);
		}
	}
	bool isvalid(const string &s) {
		if (s[0] == '0' && s.length() > 1) return false;
		if (s.length() > 3) return false;
		return stoi(s) < 256;
	}
};
void Test::Strings()
{
	Solution s;
	s.restoreIpAddresses("12345678");
}


/* 115. 不同的子序列
给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符
相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

示例 1:
输入: S = "rabbbit", T = "rabbit"
输出: 3
解释:
如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)
rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

示例 2:
输入: S = "babgbag", T = "bag"
输出: 5
解释:
如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。 
(上箭头符号 ^ 表示选取的字母)
babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
*/
int numDistinct(string s, string t) {
	return 0;
}


