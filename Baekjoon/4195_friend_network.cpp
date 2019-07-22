#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cstring> //memset

using namespace std;

int arr[100001];

int find_root(int num)		// To figure out what node's root is.
{
	if (arr[num] < 0)			// array was initialized as -1.
		return num;			// [Node 자기 자신이 root 라는 의미.]		
	
	int parent = find_root(arr[num]);	// If the node has different root, it should be searched what is the real root. [node의 root를 재귀로 검색.]
	arr[num] = parent;		// The result root will be returned.
	return parent;
}

void merge(int aParent, int bParent)
{
	if (abs(aParent) >= abs(aParent))		// Compare which one is smaller set.
	{													// [Set의 크기를 비교해서, 작은 집합이 합쳐진다.]
		arr[aParent] += arr[bParent];		//Modify the number of set. [node1의 집합 크기 수정.]
		arr[bParent] = aParent;				// The node2 is merged in node 1.[node2 집합이 node1에 합쳐진다.]
	}
	else
	{
		arr[bParent] += arr[aParent];
		arr[aParent] = bParent;
	}
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T, F;								// T = The number of test case.			F = The number of frends.
	cin >> T;							// Input of test case.

	for (int t = 0; t < T; t++)		// Loop for test case.
	{
		cin >> F;						// Input of friend's number.

		memset(arr, -1, sizeof(arr));	// Initialize input memory for each test case.
		map<string, int> name;	// Memory of friend name and index.
		int idx = 1;						// Root idx starts from 1. [1부터 index가 시작하기 위함.]

		for (int i = 0; i < F; i++)
		{
			string s1, s2;
			cin >> s1 >> s2;			// Input of names.

			if (name.count(s1) == 0)		// If there is no matching in map, it should be new one. 
				name[s1] = idx++;			// [새로 나온 이름이라면 인덱스 부여. index를 1부터 차례대로 할당.] 
			if (name.count(s2) == 0)
				name[s2] = idx++;

			int root1 = find_root(name[s1]);		// To find the root. [루트를 찾음.]
			int root2 = find_root(name[s2]);

			if (root1 == root2) 							// [같은 집합 내에 있을 경우.]
				cout << abs(arr[root1]) << "\n";

			else												// [다른 집합이라면 Merge.]
			{
				merge(root1, root2);
				cout << abs(arr[root1]) << "\n";
			}
		}
	}
}