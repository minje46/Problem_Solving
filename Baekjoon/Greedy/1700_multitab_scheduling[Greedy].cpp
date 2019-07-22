#include<iostream>
#include<algorithm>

#define MAX 101

using namespace std;

int N, K;					// N = The number of multi tabs.			K = The number of gadgets to use.
int order[MAX];		// order = The memory of gadget's schedule to use.
int used[MAX] = { 0, };		// used = The memory of multi tab to check which gadget is using.

int Change()			// To figure out how many times gadgets will be converted.
{
	int answer = 0;	// answer = The number of changed.	
	for (int i = 0; i < K; i++)
	{
		bool plug_in = false;			// plug_in = The temporary memory for showing it is already used on multi tab. 
		for (int j = 0; j < N; j++)		// The case of this gadget is already used on multi tab.
			if (used[j] == order[i])		// [해당 gadget이 multi tab에서 사용중인 경우.]
			{
				plug_in = true;
				break;
			}
		if (plug_in)							// Jsut pass.
			continue;

		for (int j = 0; j < N; j++)		// The case of multi tab has empty space.
			if (used[j] == 0)				// [Multi tab에 여유 공간이 있는 경우.]
			{
				used[j] = order[i];		// Treat using this gadget. [해당 gadget이 이제 사용중이라는 것을 표시.]
				plug_in = true;			
				break;
			}
		if (plug_in)
			continue;

		// It should check which space is better to plug out on multi tab.That's because there is no more extra space to use. 
		int idx_tab = -1, idx_device = -1;			
		for (int j = 0; j < N; j++)		// Check the multi tab.
		{
			int dist = 0;			// Count the distance of gadget. [해당 device가 사용될 순서를 dist로 check.]
			for (int d = i; d < K; d++)		// From current gadget to end of schedule. 	
			{
				if (used[j] == order[d])	// The case of gadget will be used later. [추후에 사용되는 경우.]
					break;
				dist++;
			}						// [사용되지 않을 gadget이 최대의 distance값을 가지게 된다.]

			if (dist > idx_device)
			{
				idx_device = dist;
				idx_tab = j;
			}
		}
		used[idx_tab] = order[i];			// The new gadget plug in multi tab.
		answer++;				// Count the number of changed.
	}

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> K;
	for (int i = 0; i < K; i++)
		cin >> order[i];

	cout << Change() << endl;
}