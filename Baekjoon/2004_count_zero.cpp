// Time over..
/*
#include<iostream>
#include<vector>

using namespace std;

int count_two = 0, count_five = 0;

void Combination(int n, int m)
{
	bool divided = true;
	int temp;

	for (int i = n; i > m; i--)
	{
		if (i % 2 == 0)
		{
			temp = i;
			while (divided)
			{
				if (temp % 2 == 0)
				{
					count_two++;
					temp /= 2;
				}
				else
					divided = false;
			}
		}
		divided = true;
		if (i % 5 == 0)
		{
			temp = i;
			while (divided)
			{
				if (temp % 5 == 0)
				{
					count_five++;
					temp /= 5;
				}
				else
					divided = false;
			}
		}
		divided = true;
	}

	for (int j = n - m; j > 0; j--)
	{
		if (j % 2 == 0)
		{
			temp = j;
			while (divided)
			{
				if (temp % 2 == 0)
				{
					count_two--;
					temp /= 2;
				}
				else
					divided = false;
			}
		}
		divided = true;
		if (j % 5 == 0)
		{
			temp = j;
			while (divided)
			{
				if (temp % 5 == 0)
				{
					count_five--;
					temp /= 5;
				}
				else
					divided = false;
			}
		}
		divided = true;
	}
}

int main(void)
{
	int N, M;
	cin >> N >> M;

	Combination(N, M);

	int total = 0;
	cout << count_two << endl;
	cout << count_five << endl;

	while (count_two > 0 && count_five > 0)
	{
		total++;
		count_two--;
		count_five--;
	}
	cout << total << endl;
}
*/

// Time attack.
#include<iostream>

using namespace std;

#define min(a,b) (a<b?a:b)

long long int i;
int five = 0, two = 0;

int Count_five(int num) 
{
	int count = 0;

	for (i = 5; num / i >= 1; i *= 5)		// num이 num! 중에 가장 큰 수이기 때문에, 이를 5로 나누었을 때, 나올 수 있는 몫 만큼
		count += num / i;					// n!에서 5의 배수가 존재한다고 판단할 수 있다.
												// 그래서 5의 몫을 count 하는 것.
	return count;
}

int Count_two(int num) 
{
	int count = 0;

	for (i = 2; num / i >= 1; i *= 2)		// num is the largest one in n!. If it divided by 2, we can get the quotient from the largest num
		count += num / i;					// And it prooves there are multiple of quotient numbers in it.
												// That's why counting quotient of divider.
	return count;
}

int main(void) 
{
	int n, r;
	cin >> n >> r;
				
	five += Count_five(n);						// Count the five in n!. (n!은 분자에 위치, 그래서 ++)
	if (r != 0)
		five -= Count_five(r);					// Count the five in r!. (r!은 분모에 위치, 그래서 --)
	if (n != r)
		five -= Count_five(n - r);				// Count the five in (n-r)!. (n-r은 분모에 위치, 그래서 --)

	two += Count_two(n);						// Count the two in n!. (n!은 분자에 위치, 그래서 ++)
	if (r != 0)
		two -= Count_two(r);					// Count the two in r!. (r!은 분모에 위치, 그래서 --)
	if (n != r)
		two -= Count_two(n - r);				// Count the two in (n-r)!. (n-r은 분모에 위치, 그래서 --)	

	cout << min(two, five) << endl;
}
