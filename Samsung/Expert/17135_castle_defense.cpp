#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 15

using namespace std;

int N, M, D;		// N = The height of map.		M = The width of map.			D = The distance of archer's shoot.
int map[MAX][MAX];		// map = The memory of original map data.
int visit[MAX];			// visit = The memory of archer's location.
vector<pair<int, int>> enemy;	// enemy = The whole of enemy's location.
int answer = 0;		// answer = The maximum number of killed.

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> D;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];		// Original map data.

			if (map[i][j] == 1)		// Enemy location.
				enemy.push_back(make_pair(i, j));
		}
	}
		
	for (int i = 0; i < M - 3; i++)		// For next_permutation.
		visit[i] = 0;
	for (int i = M - 3; i < M; i++)		// It starts from end to begin.
		visit[i] = 1;

	do
	{
		int cnt = 0;
		vector<pair<int, int>> temp = enemy;	// To repetive comparation.
		vector<int> archer;		// archer = The current archer's location.
		for (int i = 0; i <M; i++)
		{
			if (visit[i] == 1)	// 현재 궁수 위치 저장
				archer.push_back(i);
		}
	
		while (!temp.empty())	// Untill there is no more enemy.
		{
			int y = N;		// Fixed archers location.
			vector<int> target;		// Possible to shoot.
			for (int i = 0; i < archer.size(); i++)		// Every archers shoot at the same time.
			{
				int x = archer[i];
				int idx = 0;
				int enemyX = temp[0].second;
				int dist = abs(y - temp[0].first) + abs(x - temp[0].second);

				for (int j = 1; j < temp.size(); j++)
				{
					int tempDist = abs(y - temp[j].first) + abs(x - temp[j].second);
					// 더 가까운 적
					if (dist > tempDist)
					{
						enemyX = temp[j].second;
						dist = tempDist;
						idx = j;
					}

					// 거리가 같다면 더 왼쪽에 있는 적
					else if (dist == tempDist && enemyX > temp[j].second)
					{
						enemyX = temp[j].second;
						idx = j;
					}
				}

				// D 이내에 있는 적만 처치 가능
				if (dist <= D)
					target.push_back(idx);
			}

			// 동시에 공격하기 때문에 중복된 적 있을 수 있다
			target.erase(unique(target.begin(), target.end()), target.end());
			sort(target.begin(), target.end());

			int shoot = 0;			// 적을 처치
			for (int i = 0; i < target.size(); i++)
			{
				temp.erase(temp.begin() + (target[i] - shoot++));
				cnt++;
			}

			if (temp.empty())
				break;

			// 한칸 아래로
			vector<pair<int, int>> copyTemp;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i].first < N - 1)
					copyTemp.push_back({ temp[i].first + 1, temp[i].second });
			}

			temp = copyTemp;
		}
		answer = max(answer, cnt);
	} while (next_permutation(visit, visit + M));

	cout << answer << "\n";
}