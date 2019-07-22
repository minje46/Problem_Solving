#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N;													// N = input number to get permutation.
long long factorial[21];						// Set a factorial value in array. (Factorial ���� �̸� �����Ѵ�.[�������� N<=20 �̱⿡ memory �Ҵ�])
int use[21];										// use array check the usage of number. (1~N������ ������ ��� ���θ� check.)
vector<int> P(N);									// P vector stores the permutation. (Vector�� ������ ���� �ϳ��� �����ؼ� ������.)

void Factorial()
{
	factorial[0] = 1;

	for (int i = 1; i < 21; i++)
		factorial[i] = factorial[i - 1] * i;
}

void Search_Permutation(long long idx)
{
	for (int i = 0; i < N; i++)				// 0~N ������ �ݺ��� ���� loop.
	{
		for (int f = 1; f <= N; f++)			// ���� �� 1~N �� �̿��Ͽ� ������ ����� ���� loop. 
		{
			if (use[f] == 1)					// It checks the number is already used or not. (1~N�� ���� ��� ���θ� üũ)
				continue;

			if (factorial[N - i - 1] < idx)		// It means the order of permutation is located before. 
				idx -= factorial[N - i - 1];	// (Factorial ���� ���� order�� �� �տ� �ִٴ� ���� �ľ��� �� �ִ�.)
												// [N-i-1]...��� �����س���...
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

	for (int i = 0; i < N; i++)							// 0~N ������ �ݺ��� ���� loop.
	{
		for (int f = 1; f < P[i]; f++)					// ���� 1~N �� ã�ƺ��� ���� loop.
			if (use[f] == 0)
				idx += factorial[N - i - 1];			// [N-i-1]...�� ��� idx ã�� �Ͱ� ������ �Ǵ���...

		use[P[i]] = 1;
	}
	cout << idx + 1 << '\n';
}

int main(void) {

	int code;
	long long index;								// index = input of permutation's order. (������ ������ 20!�� ���, ���� ���� Ŀ���Ƿ� long long ���.)

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