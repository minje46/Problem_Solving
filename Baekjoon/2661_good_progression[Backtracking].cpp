#include<iostream>
#include<string>

using namespace std;

int N;															// The progression's length.
bool finish = false;										// Completed variable.

bool Promising(string s)								// Judge the number is correct or not.
{
	int len = s.length();									// The whole length of string. [String의 전체 길이.]
	int start = len - 1;									// Start position to compare. [String의 Last num은 임의로 추가 된 숫자이고, 연속으로 중복된 숫자를 판단해야 하기 위함.]

	for (int i = 1; i <= len / 2; i++)					// [substr(a,b)는 a~b까지 string을 지정하는 것.]
	{															// [substr(a,b) 에서 b가 a보다 작은 숫자일 경우, a~last 까지 지정된다.]
		string first = s.substr(start - i, i);			// First sub string to compare. [앞의 수열 숫자.]
		string second = s.substr(start, i);			// Second sub string to compare. [뒤의 수열 숫자.]
		
		if (first.compare(second) == 0)				// It means two sub strings are exactly same. [동일한 pattern의 수열을 가진다는 의미.]
			return false;
	
		--start;												// [자릿수를 늘려가면서 sub string들을 비교해야 하는데, 이를 --start 와 start-i 로 조정한다.]	
	}
	return true;
}

void Progression(int len, string seq)				// Judge the number is correct or not, then add the correct sequence in a string as a progression.
{
	if (finish)												// At completion.
		return;

	if (!Promising(seq))									// Judge the number is correct or not.
		return;

	if (len == N)											// Completed condition.
	{
		finish = true;
		cout << seq << endl;							// Output of minimum progression.
		return;
	}

	Progression(len + 1, seq + "1");				// Try to check the next number 1 will be ok.
	Progression(len + 1, seq + "2");				// Try to check the next number 2 will be ok.
	Progression(len + 1, seq + "3");				// Try to check the next number 3 will be ok.
}

int main(void) 
{
	cin >> N;					// Input of progression's length.

	Progression(1, "1");		// Find the minimum progression.
}