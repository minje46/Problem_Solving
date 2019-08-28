#include<iostream>
#include<algorithm>
#include<string>
//#pragma warning(disable:4996)

#define PASSWORD 8

using namespace std;
// Code = The specific rules to recognize binary code. 
const string Code[10] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};

int N, M;							// N = The height of map.			M = The width of map.
string map;						// map = The memory of original input data.
int pw[PASSWORD];		// pw = The memory of password after converted code.
int answer = 0;				// answer = The memory of results as output.

bool Check(string str)		// To figure out string has empty zone or not.
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != '0')		// All the array is 0, it means empty zone.
			return true;			// If not, it has code in array.
	}
	return false;
}

int Find(int dpt)		// To convert code to password.
{
	string tmp;	
	for (int i = dpt; i < dpt+7; i++)
		tmp += map[i];		// Candidate string.
	
	for (int i = 0; i < 10; i++)
	{
		if (Code[i] == tmp)	// Compare to code.
			return i;
	}
	return -1;			// Wrong code.
}

int Proof()		// To figure out the password is correct or not.
{
	int odd = 0, even = 0, tot = 0;
	for (int i = 0; i < PASSWORD - 1; i++)
	{
		if ((i+1) % 2 != 0)		// Odd number.
			odd += pw[i];
		else							// Even number.
			even += pw[i];
	}

	tot = (odd*3) + even + pw[PASSWORD - 1];		// Condition to proof password.

	int res = 0;
	if (tot % 10 == 0)			// Correct password.
	{
		for (int i = 0; i < PASSWORD; i++)
			res += pw[i];			// Return sum value.
	}
	return res;			
}

void Solve()		// To search the correct code and change to password.
{
	int idx = 0, start = -1;			// idx = The index of password array.		
	while (idx != PASSWORD)		// Until find the correct passwrods.
	{
		idx = 0, start += 1;			// start = The start index which was changed password. 
		for (int i = start; i < map.size() - 7; i++)		// [Wrong code가 convert되어, 중간부터 다시 시작하기 위함.]
		{
			int num = Find(i);		// Judge the code or not.
			if (num < 0)				// Wrong code.
			{
				if (idx > 0)				// [한 번, password를 찾았으나, 바로 다음 code는 wrong인 경우, 애초에 잘못된 변환 이었다고 판단.]
					break;
				continue;				// Shift the index.
			}
			else							// Correct code.
			{
				if (idx == 0)			// [처음 암호코드라고 판단한 시작 index 저장.]
					start = i;				// [추후에 pw가 8개가 안만들어지면 시작 위치 +1 부터 다시 shift하면서 찾기 위함.]
				pw[idx++] = num;	
				i += 6;					// Success to find code.

				if (idx == PASSWORD)		// Success to find all passwords.
					break;
			}
		}
	}
	answer = Proof();		// Prove the correct password or not.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	
		cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			string tmp;
			cin >> tmp;			// Input.

			if (Check(tmp))		// Check the valueable input or not.
				map = tmp;
		}

		Solve();		// Simulation.
			
		cout << "#" << t << " " << answer << endl;		// Output.
	}
}