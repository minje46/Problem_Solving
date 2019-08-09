#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 51
#define Baseball 10

using namespace std;

int N, answer = 0;					// N = The number of innings.		answer = The total score of game.
int player[MAX][Baseball];		// player = The memory of player's score in each inning.
int hitters[Baseball];				// hitters = The memory of player's order.
int order[9];							// order = It has number 2~9 to allocate automatically player's order using next permutation.
int score, out;							// score = The total score of each inning.		out = The number of out counts.
bool base[4];							// base = The memory of checking where the runner is.

void Game()
{
	int start = 1; score = 0;		// start = The number of player to start in this inning.
	for (int inn = 1; inn <= N; inn++)
	{
		bool flag = false;
		out = 0;
		while (1)
		{
			for (int i = start; i < Baseball; i++)
			{
				int state = player[inn][hitters[i]];			// [Inning�� i��°, palyer�� batting.]

				if (state == 0)		// Strike out.
				{
					out++;
					if (out == 3)
					{
						if (i == 9)
							start = 1;
						else
							start = i + 1;
						memset(base, 0, sizeof(base));		// All of runners die.
						flag = true;
						break;
					}
				}

				if (state == 1)		// A first-base hit. [1��Ÿ.]
				{
					if (base[3])		// The case of runner is on third-base. [3�翡 ����.]		
					{
						base[3] = false;
						score++;
					}
					for (int r = 2; r > 0; r--)	// Advance to base. [���ڴ� ����.]
					{
						if (base[r])		// The runners on the base.
						{
							base[r + 1] = true;
							base[r] = false;
						}
					}
					base[1] = true;			// Batter is on first-base. [Ÿ�ڴ� 1��.]
				}

				if (state == 2)		// A second-base hit.	[2��Ÿ.]
				{
					if (base[3])		// The case of runner is on third-base. [3�翡 ����.]
					{
						base[3] = false;
						score++;
					}
					if (base[2])		// The case of runner is on second-base. [2�翡 ����.]
					{
						base[2] = false;
						score++;
					}
					if (base[1])		// The case of runner is on first-base. [1�翡 ����.]
					{
						base[1] = false;
						base[3] = true;
					}
					base[2] = true;		// Batter is on first-base. [Ÿ�ڴ� 1��.]
				}

				if (state == 3)		// A third-base hit.	[3��Ÿ.]
				{
					for (int r = 1; r <= 3; r++)		// The case of runner is on each base. [���ڵ� Ȩ����.]
					{
						if (base[r])
						{
							base[r] = false;
							score++;
						}
					}
					base[3] = true;		// Batter is on third-base. [Ÿ�ڴ� 3��.]
				}

				if (state == 4)		// A home-run.	[Ȩ��.]
				{
					for (int r = 1; r <= 3; r++)		// The case of runner is on each base. [���ڵ� Ȩ����.]
					{
						if (base[r])
						{
							base[r] = false;
							score++;
						}
					}
					score++;		// Batter is comming to home. [Ÿ�� Ȩ����.]
				}
			}
			if (flag)
				break;
			start = 1;
		}
	}
}
void Combination()
{
	hitters[4] = 1;		// The first batter is fixed as slugger (Number : 4)
	do {
		int idx = 1;
		for (int i = 0; i < 8; i++)
		{
			if (idx != 4)		// Except number 4, it could be set automatically.
				hitters[idx] = order[i];		// [order�� next_permutation���� ����, �ڵ����� ���� ��ġ.]
			else
				hitters[++idx] = order[i];	// If number 4 -> number 5.
			idx++;
		}
		Game();
		answer = max(score, answer);
	} while (next_permutation(order, order + 8));
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 8; i++)
		order[i] = i + 2;		// [2~9������ next_permutation�� �̿��Ͽ� �ڵ����� ������ ��ġ�ϱ� ����.] 

	cin >> N;
	for (int i = 1; i <= N; i++)		// Every inning.
	{
		for (int j = 1; j < Baseball; j++)		// Each player's score.
			cin >> player[i][j];
	}

	Combination();
	cout << answer << endl;
}
