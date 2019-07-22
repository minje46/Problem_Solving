#include<iostream>
#include<algorithm>
#include<cmath>

#define MAX 32

using namespace std;

int weight[MAX];		// The memory of weights. [���� ���� ���� ����.]
int bead[10];			// The memory of beads.	[������ ���� ���� ����.]
bool memo[MAX][MAX * 500];		// The memory of memoization to store all cases. [�߿� ������ ���� �� �ִ� ��� ��� ����.]
int N, M;					// N = The number of weights. [���� ����.]			// M = The number of beads. [������ ����.]

void DP(int cnt, int tot_w)		// To figure out the weights with number of weights. [���� cnt ������ ���� �� �ִ� ���� �� ���Ը� ���.]
{							// cnt = The number of weight to use.		tot_w = The current weight.
	if (cnt > N)			// [cnt�� ���� ����� ���� ������ �ǹ�.		tot_w�� ���� ���� �� ����.]
		return;			// The maximum number of weihgt to use is less than total number of weights.	[���� �� ���� �̻��� ����� �ʿ�X.]

	if (memo[cnt][tot_w])		// If this weight was possible to calculate, it doesn't need to recalculate.
		return;			// [�̹� ������� ���� ���Դ� �ٽ� ����� �ʿ�X.]

	memo[cnt][tot_w] = true;	

	DP(cnt + 1, tot_w + weight[cnt]);		// [���� ���� 1�� ������ �Բ�, ������ �� ����+����� �� �ִ� ���� ������ �߸� �̿��ϴ� ���.]
	DP(cnt + 1, tot_w);		// [���� ������ ������Ű����, ������ ���Ը� �������� �ʴ� ���.]	[Ouput ��� ��, ���� �� ������ Ȯ���ϱ� ������ ��?]
	DP(cnt + 1, abs(tot_w - weight[cnt]));	// [���� ���� 1�� ������ �Բ�, ���� �ʿ� �߸� �ø��� ���.]
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
			cout << "Y ";		// [��� �߸� �̿����� ��, ���� ���� ���� ������ ���� �� �ֱ� ������, N���� ���ո� Ȯ��.]
		else										// The impossible case to be balances.
			cout << "N ";		
	}
	cout << endl;
}