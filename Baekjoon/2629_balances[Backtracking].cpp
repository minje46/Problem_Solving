#include<iostream>
#include<algorithm>
#include<cmath>

#define MAX 32

using namespace std;

int weight[MAX];		// The memory of weights. [추의 무게 저장 공간.]
int bead[10];			// The memory of beads.	[구슬의 무게 저장 공간.]
bool memo[MAX][MAX * 500];		// The memory of memoization to store all cases. [추와 구슬로 만들 수 있는 모든 경우 저장.]
int N, M;					// N = The number of weights. [추의 개수.]			// M = The number of beads. [구슬의 개수.]

void DP(int cnt, int tot_w)		// To figure out the weights with number of weights. [추의 cnt 개수로 만들 수 있는 추의 총 무게를 계산.]
{							// cnt = The number of weight to use.		tot_w = The current weight.
	if (cnt > N)			// [cnt는 현재 사용한 추의 개수를 의미.		tot_w는 현재 추의 총 무게.]
		return;			// The maximum number of weihgt to use is less than total number of weights.	[추의 총 개수 이상은 계산할 필요X.]

	if (memo[cnt][tot_w])		// If this weight was possible to calculate, it doesn't need to recalculate.
		return;			// [이미 만들었던 추의 무게는 다시 계산할 필요X.]

	memo[cnt][tot_w] = true;	

	DP(cnt + 1, tot_w + weight[cnt]);		// [추의 개수 1개 증가와 함께, 기존의 추 무게+사용할 수 있는 다음 순서의 추를 이용하는 경우.]
	DP(cnt + 1, tot_w);		// [추의 개수는 증가시키지만, 실제로 무게를 높이지는 않는 경우.]	[Ouput 출력 시, 추의 총 개수만 확인하기 때문인 듯?]
	DP(cnt + 1, abs(tot_w - weight[cnt]));	// [추의 개수 1개 증가와 함께, 구슬 쪽에 추를 올리는 경우.]
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin >> N;						// The number of weight.
	for (int i = 0; i < N; i++)
		cin >> weight[i];			// Weight's weight.
	
	cin >> M;						// The number of beads.
	for (int i = 0; i < M; i++)
		cin >> bead[i];			// Bead's weight.

	DP(0, 0);						// Do memoization from zero.
	for (int i = 0; i < M; i++)
	{
		if (bead[i] > MAX * 500)			// The overflow area.
			cout << "N ";
		else if (memo[N][bead[i]])		// The possible case to be balances.
			cout << "Y ";		// [모든 추를 이용했을 때, 가장 많은 무게 조합을 구할 수 있기 때문에, N개의 조합만 확인.]
		else										// The impossible case to be balances.
			cout << "N ";		
	}
	cout << endl;
}