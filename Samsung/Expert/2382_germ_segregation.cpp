#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 101

using namespace std;

struct Germ		// The data of germ.
{
	int y, x;			// Location.
	int num;			// Number of germs.
	int dir;			// Direction to move.	[1 : Up, 2 : Down, 3 : Left, 4 : Right.]
};

int N, M, K;			// N = The size of map.		M = The time to flow.			K = The number of germs.
int visit[MAX][MAX];			// visit = To check how many germs stay.
int dy[4] = { -1,1,0,0 };		// Up, Down.
int dx[4] = { 0,0,-1,1 };		// Left, Right.
vector<Germ> germ;			// germ = The memory of all germ's data.

int Find(int y, int x)		// To search the index of germ which is located on (y,x).
{
	for (int i = 0; i < germ.size(); i++)
	{
		if (y == germ[i].y && x == germ[i].x)		// Find the same location.
			return i;			// Return the index.
	}
}

void Arrange()		// To rearrange the whole of germs which should be dealt with.
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] < 1)		// Germ doesn't exit.	
				continue;

			if (i == 0 || i == N - 1 || j == 0 || j == N - 1)		// Vaccine area. [The half of germs should be died. + Change the direction.]
			{
				int idx = Find(i, j);		// Find the germ's index.

				if (germ[idx].dir == 1 || germ[idx].dir == 3)		// Up or Left.
					germ[idx].dir += 1;								// Down or Right.
				else																// Down or Right.
					germ[idx].dir -= 1;								// Up or Left.

				germ[idx].num /= 2;	// Be half.
			}
			
			if (visit[i][j] > 1)		// If there are one more germs together, it should be only one.
			{
				int n = visit[i][j];				// The number of germs stay here.
				vector<Germ> duplicate(n);		// Temporary memory for storing germs.

				int king = 0, k_idx = 0;		// king = The maximum size.		k_idx = The index of germ which is king.
				for (int k = 0; k < n; k++)
				{
					int idx = Find(i, j);		// Find the index of germ.
					duplicate[k] = germ[idx];			// Store the data temporarily.
					germ.erase(germ.begin() + idx);	// And delete the data in original memory.

					if (king < duplicate[k].num)		// Also find the maximum size at once.
					{
						king = duplicate[k].num;		// Maximum size.
						k_idx = k;							// Index of this one.
					}
				}

				for (int k = 0; k < duplicate.size(); k++)		// Search the whole of temporary memory.
				{
					if (k == k_idx)		// Excep the king one.
						continue;

					duplicate[k_idx].num += duplicate[k].num;		// Absorb the size of others.
				}
				germ.push_back(duplicate[k_idx]);		// Push the new data in original memory.
			}
		}
	}
}

void Move()		// To move each germs through the their own direction.
{
	for (int i = 0; i < germ.size(); i++)
	{
		int ny = germ[i].y + dy[germ[i].dir - 1];		// New location.
		int nx = germ[i].x + dx[germ[i].dir - 1];
		// Move to new area.
		germ[i].y = ny;
		germ[i].x = nx;
		visit[ny][nx] += 1;		// Check the number of germs.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		germ.clear();

		cin >> N >> M >> K;
		for (int i = 0; i < K; i++)
		{
			int y, x, num, dir;
			cin >> y >> x >> num >> dir;
			germ.push_back({ y, x, num, dir });		// Germ's data.
		}

		while (M--)		// Time flows.
		{
			memset(visit, 0, sizeof(visit));		// Initialize.
			Move();			// Move the all germs.
			Arrange();		// Rearrange the moved germs.
		}

		int answer = 0;			// answer = The number of all germs.
		for (int i = 0; i < germ.size(); i++)
			answer += germ[i].num;			// Total number of germs.

		cout << "#" << t << " " << answer << endl;		// Output.
	}
}
