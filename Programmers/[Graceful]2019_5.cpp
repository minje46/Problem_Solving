#include<iostream>
#include<string>
// 3,6,9 ∞‘¿”. 
using namespace std;

int solution(int num)
{
	int cnt = 0;	
	for (int i = 1; i <= num; i++)
	{		
		string str = to_string(i);		// To check each digit easily.
		for (int j = 0; j < str.length(); j++)
		{
			if (str[j] == '3' || str[j] == '6' || str[j] == '9')		// 3, 6, 9.
				cnt += 1;
		}
	}
	return cnt;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);

	int number = 33;		// Input data.
	cout << solution(number) << endl;
}