#include "pch.h"
#include "Test.h"

using namespace std;


/* 771. ��ʯ��ʯͷ
* �����ַ���J ����ʯͷ�б�ʯ�����ͣ����ַ��� S������ӵ�е�ʯͷ�� 
* S ��ÿ���ַ�������һ����ӵ�е�ʯͷ�����ͣ�����֪����ӵ�е�ʯͷ���ж����Ǳ�ʯ��
* J �е���ĸ���ظ���J �� S�е������ַ�������ĸ����ĸ���ִ�Сд�����"a"��"A"�ǲ�ͬ���͵�ʯͷ��
* S �� J ��ຬ��50����ĸ��
* J �е��ַ����ظ���
* 
* ����: J = "aA", S = "aAAbbbb"			* ���: 3
* ����: J = "z", S = "ZZ"				* ���: 0
*/
int numJewelsInStones(string J, string S) {
	// ��ϣ˼��
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

/* 665. �ǵݼ�����
* ����һ������Ϊ n ���������飬����������ж������ı� 1 ��Ԫ�ص�����£��������ܷ���һ���ǵݼ����С�
* ��������������һ���ǵݼ����еģ� �������������е� i (1 <= i < n)������ array[i] <= array[i + 1]��
* 
* ����: [4,2,3]		* ���: true	����: �����ͨ���ѵ�һ��4���1��ʹ������Ϊһ���ǵݼ����С�
* ����: [4,2,1]		* ���: false	����: �㲻����ֻ�ı�һ��Ԫ�ص�����½����Ϊ�ǵݼ����С�
*/
bool checkPossibility(vector<int>& nums) {
	const int numsCount = nums.size();
	int nFind;
	bool bFlag = false;

	// ������2����
	if (numsCount < 2)
		return true; 
	// ���������������
	for (int i = 0; i < numsCount - 1; ++i) {
		if (nums[i + 1] < nums[i]) {
			// ������1���ݼ�
			if (bFlag)
				return false; 
			else {
				bFlag = true;
				nFind = i;
			}
		}
	}
	// δ���� / ������� / �����ұ�
	if (!bFlag || 0 == nFind || (numsCount - 1 == nFind + 1))
		return true; 
	// ����С���ֵ�����ܱ�ǰһ��С / ���Ĵ��ұߵ�ֵ�����ܱȺ�һ����
	if (nums[nFind + 1] >= nums[nFind - 1] || nums[nFind] <= nums[nFind + 2])
		return true;
	return false;
}

/* 674. �������������
* ����һ��δ��������������飬�ҵ���������ĵĵ������С�
* 
* ����: [1,3,5,4,7]		* ���: 3		����: ��������������� [1,3,5], ����Ϊ3��
* ����: [2,2,2,2,2]		* ���: 1		����: ��������������� [2], ����Ϊ1��
*/
int findLengthOfLCIS(vector<int>& nums) {
	const int numsCount = nums.size();
	int max = 0;
	int cur = 0;

	// ������2����
	if (numsCount < 2)
		return numsCount;
	// ��������������������
	for (int i = 0; i < numsCount - 1; ++i) {
		++cur;
		if (cur > max)
			max = cur;
		if (nums[i] < nums[i + 1]) {
			// ����
		}
		else {
			// �ж�
			cur = 0;
		}
	}
	++cur;
	if (cur > max)
		max = cur;
	return max;
}

/* 680. ��֤�����ַ��� ��
* ����һ���ǿ��ַ��� s�����ɾ��һ���ַ����ж��Ƿ��ܳ�Ϊ�����ַ�����
* 
* ����: "aba"		* ���: True		ABA��ABBA �������
* ����: "abca"		* ���: True		����: �����ɾ��c�ַ���
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

	// ������2���ַ���
	if (right - left < 2)
		return true;
	while (right > left) {
		if (s[right] != s[left]) {
			if (!bFlag) {
				bFlag = true;
				// ���ֲ�ͬ��ɾ�� / ɾ��
				return (checkPal(s, left + 1, right) || checkPal(s, left, right - 1));
			}
			else {
				// ������1����ͬ
				return false;
			}
		}
		++left;
		--right;
	}
	return true;
}

/* 475. ��ů��
* �����Ѿ����١� ������������һ���й̶����Ȱ뾶�Ĺ�ů�������з��ݹ�ů��
* ���ڣ�����λ��һ��ˮƽ���ϵķ��ݺ͹�ů����λ�ã��ҵ����Ը������з��ݵ���С���Ȱ뾶��
* ���ԣ�������뽫���Ƿ��ݺ͹�ů����λ�á��㽫�����ů������С���Ȱ뾶��
* 1 �����ķ��ݺ͹�ů������Ŀ�ǷǸ����Ҳ��ᳬ�� 25000��
* 2 �����ķ��ݺ͹�ů����λ�þ��ǷǸ����Ҳ��ᳬ��10^9��
* 3 ֻҪ����λ�ڹ�ů���İ뾶��(�����ڱ�Ե��)�����Ϳ��Եõ���ů��
* 4 ���й�ů������ѭ��İ뾶��׼�����ȵİ뾶Ҳһ����
* 
* ����: [1,2,3],[2]		* ���: 1	����: ����λ��2����һ����ů����������ǽ����Ȱ뾶��Ϊ1����ô���з��ݾͶ��ܵõ���ů��
* ����: [1,2,3,4],[1,4]	* ���: 1	����: ��λ��1, 4����������ů����������Ҫ�����Ȱ뾶��Ϊ1���������з��ݾͶ��ܵõ���ů��
*/
int findRadius(vector<int>& houses, vector<int>& heaters) {
	if (houses.size() < 1 || heaters.size() < 1)
		return -1;
	// ������������ȴ�С��������
	std::sort(houses.begin(), houses.end());
	std::sort(heaters.begin(), heaters.end());
	// ֻ��һ��heater�����������ֱ�ӷ���
	if (heaters.size() == 1) {
		int left = std::abs(houses[0] - heaters[0]);
		int right = std::abs(houses[houses.size() - 1] - heaters[0]);
		return std::max(left, right);
	}
	// ����ÿһ��house��ǰ������ȡů��(����һ��Ҳ���Ե�������������)
	int radius = 0;
	int prev = 0, next = 1; 
	for (int i = 0; i < houses.size(); ++i) {
		if (houses[i] == heaters[prev] || houses[i] == heaters[next]) {
			// house ��heater�ص���������
		}
		else if (houses[i] < heaters[prev]) {
			// house ��prev��ǰ�棬һ���ǵ�һ��heater
			radius = std::max(radius, heaters[prev] - houses[i]);
		}
		else if (houses[i] > heaters[next]) {
			// house ��next�ĺ��棬���������һ��heater
			if (next >= heaters.size() - 1) {
				radius = std::max(radius, houses[i] - heaters[next]);
			}
			// Ҳ�������ƶ�next
			else {
				prev = next;
				++next;
				--i; // �����ж�һ��
			}
		}
		else {
			// house ��prev��next֮�䣬ȡ���
			int r = min(houses[i] - heaters[prev], heaters[next] - houses[i]);
			radius = max(radius, r);
		}
	}
	return radius;
}

/* 476. ���ֵĲ���
* ����һ����������������Ĳ����������ǶԸ����Ķ����Ʊ�ʾȡ����
* 1 ������������֤��32λ�����������ķ�Χ�ڡ�
* 2 ����Լٶ���������������ǰ����λ��
* 
* ����: 5	���: 2		����: 5�Ķ����Ʊ�ʾΪ101��û��ǰ����λ�����䲹��Ϊ010����������Ҫ���2��
* ����: 1	���: 0		����: 1�Ķ����Ʊ�ʾΪ1��û��ǰ����λ�����䲹��Ϊ0����������Ҫ���0��
*/
int findComplement(int num) {
	// ��Ҫ��"ǰ����λ"ȥ����������
	int mask = ~0; // 0xffffffff
	while (mask & num)
		mask = mask << 1;
	return ((~num )& (~mask));
}

/* 482. ��Կ��ʽ��
* ����һ����Կ�ַ���S��ֻ������ĸ�������Լ� '-'�����ۺţ���N �� '-' ���ַ����ֳ��� N+1 �顣
* ����һ������ K�����¸�ʽ���ַ��������˵�һ���������⣬ÿ������Ҫ���� K ���ַ�����һ����������Ҫ���� 1 ���ַ���
* ��������֮���� '-'�����ۺţ����������ҽ����е�Сд��ĸת��Ϊ��д��ĸ��
* �����ǿ��ַ��� S ������ K���������������Ĺ�����и�ʽ����
* 1 S �ĳ��Ȳ����� 12,000��K Ϊ������
* 2 S ֻ������ĸ���֣�a-z��A-Z��0-9���Լ����ۺ�'-'
* 3 S �ǿ�
* 
* ���룺S = "5F3Z-2e-9-w", K = 4	���ͣ��ַ��� S ���ֳ����������֣�ÿ���� 4 ���ַ���ע�⣬������������ۺ���Ҫɾ����
* �����"5F3Z-2E9W"
* ���룺S = "2-5g-3-J", K = 2		���ͣ��ַ��� S ���ֳ��� 3 �����֣���һ���ֵ��ַ��������ڸ��������������ಿ�ֽ�Ϊ 2 ���ַ���
* �����"2-5G-3J" 
*/
string licenseKeyFormatting(string S, int K) {
	// Ϊ�����Ч�ʣ����԰�insert���������Լ������char[]�̶�����
	// ���滻�ַ�
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
	// �����'-'
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

/* 342. 4����
* ����һ������ (32 λ�з�������)�����дһ���������ж����Ƿ��� 4 ���ݴη���
* ���ף�
* ���ܲ�ʹ��ѭ�����ߵݹ�����ɱ�����
* 
* ����: 16		* ���: true
* ����: 5		* ���: false 
*/
bool isPowerOfFour(int num) {
	// ����������4�ݵĶ�����������100��10000��1000000��etc...��ʽ�����������½��ۣ�
	// 4����һ����2�ġ�
	// 4���ݺ�2����һ����ֻ�����һλ1�����ǣ�4��1���ǳ���������λ��
	if (num < 0 || num & (num - 1))
		return false;

	// 0x5 = 0101b��������У������λ�ϵ�1��
	return num & 0x55555555;
}

/* 344. ��ת�ַ���
* ��дһ���������������ǽ�������ַ�����ת�����������ַ������ַ����� char[] ����ʽ������
* ��Ҫ�����������������Ŀռ䣬�����ԭ���޸��������顢ʹ�� O(1) �Ķ���ռ�����һ���⡣
* ����Լ��������е������ַ����� ASCII ����еĿɴ�ӡ�ַ���
* 
* ���룺["h","e","l","l","o"]
* �����["o","l","l","e","h"]
*/
void reverseString(vector<char>& s) {
	//// �½�һ��vecȻ�󽻻�
	//const int siz = s.size();
	//vector<char> reverse;
	//reverse.resize(siz);
	//for (int i = 0; i < siz; ++i)
	//	reverse[siz - 1 - i] = s[i];
	//s.swap(reverse);

	// ˫ָ��Ի�����������Ч�ʲ�������
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

/* 345. ��ת�ַ����е�Ԫ����ĸ
* ��дһ�����������ַ�����Ϊ���룬��ת���ַ����е�Ԫ����ĸ��
* 
* ����: "hello"
* ���: "holle"
*/
string reverseVowels(string s) {
#define isVowels(X) ('a' == X || 'A' == X || 'e' == X || 'E' == X || 'i' == X || 'I' == X || 'o' == X || 'O' == X || 'u' == X || 'U' == X)
	//// ˫ָ��Ի�����ʱ��...???
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

	// ����Ԫ���͵�ַ�����ŷŻ�ȥ
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

/* 219. �����ظ�Ԫ�� II
* ����һ�����������һ������ k���ж��������Ƿ����������ͬ������ i �� j��
* ʹ�� nums [i] = nums [j]������ i �� j �Ĳ�ľ���ֵ���Ϊ k��
* 
* ����: nums = [1,2,3,1], k = 3			* ���: true
* ����: nums = [1,0,1,1], k = 1			* ���: true
* ����: nums = [1,2,3,1,2,3], k = 2		* ���: false
*/
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	// ��map���� value-index �ظ�ʱ�жϲ�ֵ�����������о�������map���
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

/* 762. �����Ʊ�ʾ��������������λ
* ������������ L �� R ���ҵ������� [L, R] ��Χ�ڣ�������λλ��Ϊ����������������
* ע�⣬������λ��������Ʊ�ʾ��1�ĸ��������� 21 �Ķ����Ʊ�ʾ 10101 �� 3 ��������λ�����У�1 ����������
* 
* ����: L = 6, R = 10			* ���: 4
	6 -> 110 (2 ��������λ��2 ������)
	7 -> 111 (3 ��������λ��3 ������)
	9 -> 1001 (2 ��������λ��2 ������)
	10-> 1010 (2 ��������λ��2 ������)
* 
* ����: L = 10, R = 15			* ���: 5
	10 -> 1010 (2 ��������λ, 2 ������)
	11 -> 1011 (3 ��������λ, 3 ������)
	12 -> 1100 (2 ��������λ, 2 ������)
	13 -> 1101 (3 ��������λ, 3 ������)
	14 -> 1110 (3 ��������λ, 3 ������)
	15 -> 1111 (4 ��������λ, 4 ��������)
*/
int countPrimeSetBits(int L, int R) {
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
