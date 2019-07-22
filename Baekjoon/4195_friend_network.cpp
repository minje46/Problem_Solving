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
		return num;			// [Node �ڱ� �ڽ��� root ��� �ǹ�.]		
	
	int parent = find_root(arr[num]);	// If the node has different root, it should be searched what is the real root. [node�� root�� ��ͷ� �˻�.]
	arr[num] = parent;		// The result root will be returned.
	return parent;
}

void merge(int aParent, int bParent)
{
	if (abs(aParent) >= abs(aParent))		// Compare which one is smaller set.
	{													// [Set�� ũ�⸦ ���ؼ�, ���� ������ ��������.]
		arr[aParent] += arr[bParent];		//Modify the number of set. [node1�� ���� ũ�� ����.]
		arr[bParent] = aParent;				// The node2 is merged in node 1.[node2 ������ node1�� ��������.]
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
		int idx = 1;						// Root idx starts from 1. [1���� index�� �����ϱ� ����.]

		for (int i = 0; i < F; i++)
		{
			string s1, s2;
			cin >> s1 >> s2;			// Input of names.

			if (name.count(s1) == 0)		// If there is no matching in map, it should be new one. 
				name[s1] = idx++;			// [���� ���� �̸��̶�� �ε��� �ο�. index�� 1���� ���ʴ�� �Ҵ�.] 
			if (name.count(s2) == 0)
				name[s2] = idx++;

			int root1 = find_root(name[s1]);		// To find the root. [��Ʈ�� ã��.]
			int root2 = find_root(name[s2]);

			if (root1 == root2) 							// [���� ���� ���� ���� ���.]
				cout << abs(arr[root1]) << "\n";

			else												// [�ٸ� �����̶�� Merge.]
			{
				merge(root1, root2);
				cout << abs(arr[root1]) << "\n";
			}
		}
	}
}