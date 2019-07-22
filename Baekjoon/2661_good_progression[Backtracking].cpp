#include<iostream>
#include<string>

using namespace std;

int N;															// The progression's length.
bool finish = false;										// Completed variable.

bool Promising(string s)								// Judge the number is correct or not.
{
	int len = s.length();									// The whole length of string. [String�� ��ü ����.]
	int start = len - 1;									// Start position to compare. [String�� Last num�� ���Ƿ� �߰� �� �����̰�, �������� �ߺ��� ���ڸ� �Ǵ��ؾ� �ϱ� ����.]

	for (int i = 1; i <= len / 2; i++)					// [substr(a,b)�� a~b���� string�� �����ϴ� ��.]
	{															// [substr(a,b) ���� b�� a���� ���� ������ ���, a~last ���� �����ȴ�.]
		string first = s.substr(start - i, i);			// First sub string to compare. [���� ���� ����.]
		string second = s.substr(start, i);			// Second sub string to compare. [���� ���� ����.]
		
		if (first.compare(second) == 0)				// It means two sub strings are exactly same. [������ pattern�� ������ �����ٴ� �ǹ�.]
			return false;
	
		--start;												// [�ڸ����� �÷����鼭 sub string���� ���ؾ� �ϴµ�, �̸� --start �� start-i �� �����Ѵ�.]	
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