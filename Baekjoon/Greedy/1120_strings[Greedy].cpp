#include <iostream>
#include <algorithm>
#include<string>

using namespace std;

int main(void) 
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string A, B;				// A = The first string memory.			B = The second string memory.
	cin >> A >> B;

	int answer = 50;			// The maximum gap between A and B; [A�� B�� ��� �ٸ� ���.]
	for (int dist = 0; dist <= B.length() - A.length(); dist++) 
	{								// [B-A�� �� ��ŭ, A�� string ��ġ�� sliding�ϸ鼭 ��.]
		int cnt = 0;
		for (int i = 0; i<A.length(); i++)		// [A�� �պ��� append �ϴ� ��츸 ���.]
		{								// [A�� ���̱��� Ȯ���ϴ� ������, �� �ڷδ� B�� �����ϰ� append �� ���̱� ������...]
			if (A[i] != B[i + dist])				// [������ A�� append �ϴ� ���� �ƴ�, ���� ���� B�� index controlling�� ���� ���� 1, 2�� �������� ����.]
				cnt++;
		}
		answer = min(answer, cnt);
	}
	cout << answer << endl;
}