#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int N;							// N = The number of words.
int alphabet[26];			// alphabet = The memory of displacement from character to integer based on digits. 

int Word_Math()			// To displace the character to integer.
{
	int answer = 0, cnt = 9;
	vector<int> vc;		// vc = The temporary memory for used alphabet only.
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i])	// Only used character has integer value.
			vc.push_back(alphabet[i]);
	}

	sort(vc.begin(), vc.end(), greater<int>());			// Descending order. To check higher priority based on digits.
	for (int i = 0; i<vc.size(); i++)
		answer += vc[i] * (cnt--);		// [사용된 단어가 내림차순 정렬되어 있고, 순서대로 높은 숫자를 부여하면 된다.]

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i<N; i++) 
	{
		string str;
		cin >> str;

		for (int j = 0; j < str.length(); j++)			// [A = 65] in Ascii code.
			alphabet[str[j] - 65] += (int)pow(10, str.length() - j - 1);		// Displacement character to integer.
	}

	cout << Word_Math() << endl;
}