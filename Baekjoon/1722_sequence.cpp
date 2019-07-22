#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N;													// N = input number to get permutation.
long long factorial[21];						// Set a factorial value in array. (Factorial 값을 미리 저장한다.[문제에서 N<=20 이기에 memory 할당])
int use[21];										// use array check the usage of number. (1~N까지의 숫자의 사용 여부를 check.)
vector<int> P(N);									// P vector stores the permutation. (Vector에 순열을 숫자 하나씩 저장해서 만들어낸다.)

void Factorial()
{
	factorial[0] = 1;

	for (int i = 1; i < 21; i++)
		factorial[i] = factorial[i - 1] * i;
}

void Search_Permutation(long long idx)
{
	for (int i = 0; i < N; i++)				// 0~N 까지의 반복을 위한 loop.
	{
		for (int f = 1; f <= N; f++)			// 실제 값 1~N 을 이용하여 순열을 만들기 위한 loop. 
		{
			if (use[f] == 1)					// It checks the number is already used or not. (1~N의 숫자 사용 여부를 체크)
				continue;

			if (factorial[N - i - 1] < idx)		// It means the order of permutation is located before. 
				idx -= factorial[N - i - 1];	// (Factorial 값을 통해 order가 더 앞에 있다는 것을 파악할 수 있다.)
												// [N-i-1]...어떻게 생각해내니...
			else
			{
				P.push_back(f);
				use[f] = 1;						// 1 means this number is used.
				break;
			}
		}
	}
	for (int i = 0; i < N; i++)
		cout << P[i] << " ";
}

void Search_Index()
{
	long long idx = 0;

	for (int i = 0; i < N; i++)							// 0~N 까지의 반복을 위한 loop.
	{
		for (int f = 1; f < P[i]; f++)					// 순열 1~N 을 찾아보기 위한 loop.
			if (use[f] == 0)
				idx += factorial[N - i - 1];			// [N-i-1]...이 어떻게 idx 찾는 것과 연관이 되는지...

		use[P[i]] = 1;
	}
	cout << idx + 1 << '\n';
}

int main(void) {

	int code;
	long long index;								// index = input of permutation's order. (순열의 순서가 20!일 경우, 순서 또한 커지므로 long long 사용.)

	memset(use, 0, sizeof(use));			// Initialize use array in 0.
	Factorial();										// Set a factorial in array in advance.

	cin >> N >> code;
	switch (code) {
	case 1:
		cin >> index;								// Get an order of permutation.
		Search_Permutation(index);
		break;

	case 2:
		int temp;
		for (int i = 0; i < N; i++) {
			cin >> temp;
			P.push_back(temp);				// Get a permutation.
		}
		Search_Index();
		break;
	}
}