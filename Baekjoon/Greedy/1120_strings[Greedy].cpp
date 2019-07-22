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

	int answer = 50;			// The maximum gap between A and B; [A와 B가 모두 다른 경우.]
	for (int dist = 0; dist <= B.length() - A.length(); dist++) 
	{								// [B-A의 값 만큼, A의 string 위치를 sliding하면서 비교.]
		int cnt = 0;
		for (int i = 0; i<A.length(); i++)		// [A의 앞부터 append 하는 경우만 고려.]
		{								// [A의 길이까지 확인하는 이유는, 그 뒤로는 B와 동일하게 append 할 것이기 때문에...]
			if (A[i] != B[i + dist])				// [실제로 A에 append 하는 것이 아닌, 비교할 기준 B의 index controlling을 통해 조건 1, 2를 가상으로 충족.]
				cnt++;
		}
		answer = min(answer, cnt);
	}
	cout << answer << endl;
}