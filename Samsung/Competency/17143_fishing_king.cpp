#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 101

using namespace std;

const int dy[5] = { 0,-1,1,0,0 };		// [1:UP]	[2:DOWN]
const int dx[5] = { 0,0,0,1,-1 };		// [3:RIGHT]	[4:LEFT]

struct Shark		// The memory for shark's data.
{
	int y, x;			// Location.
	int speed;		// Speed to move.
	int dir;			// Direction for move.
	int size;			// Size.
};

int R, C, M;		// R = The height of map.	C = The width of map.			M = The number of sharks.
vector<Shark>shark;		// shark = The memory for sharks.
int map[MAX][MAX];		// map = The memory for shark's current location on the map.

int Find(int y, int x)		// To search this shark's index from all shark's data.
{
	for (int i = 0; i < shark.size(); i++)
	{
		if (shark[i].y == y && shark[i].x == x)	// Compare the location of shark.
			return i;			// Return the index.		
	}
}

void Arrange()		// To rearrange the map based on new shark's data.
{
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			if (map[i][j] > 1)		// If there are one more sharks, it should be rearranged.
			{								// [Only one shark should stay in one room.]
				int n = map[i][j];	// The number of sharks.
				vector<Shark> duplicate(n);
				for (int k = 0; k < n; k++)
				{
					int idx = Find(i, j);		// To search the index of shark.
					duplicate[k] = shark[idx];	// Store current shark temporarily.
					shark.erase(shark.begin() + idx);		// Delete the current shark in Shark data to find again next time.
				}

				int king = 0;
				for (int z = 1; z < duplicate.size(); z++)
				{
					if (duplicate[king].size < duplicate[z].size)		// Compare the shark's size each by each.
						king = z;		// The index of the biggest shark.
				}
				shark.push_back(duplicate[king]);	// Only one shark which is the biggest is saved.
				map[i][j] = 1;	// Rearrange the map as well.
			}
		}
	}
}

void Move()		// To move the whole of sharks based on their own speed and direction.
{						// [Direction : 1 = Up.	2 = Down.	3 = Right.	4 = Left.]
	for (int i = 0; i < shark.size(); i++)
	{
		map[shark[i].y][shark[i].x] -= 1;		// It means current shark will move.
		
		int y = shark[i].y, x = shark[i].x;		// The current shark's location.
		int dir = shark[i].dir;						// The current shark's direction to move.
		int range;										// [Shark가 다시 제자리로 돌아오는 값.]
		if (dir <= 2)										// [range를 이용하여 shark의 움직이는 loop 값을 줄여줌.]
			range = shark[i].speed % (2 * (R - 1));			// [Up,Down의 경우, 1~row의 값이 overflow range.]
		else																// [Right, Left의 경우, 1~column의 값이 overflow range.]
			range = shark[i].speed % (2 * (C - 1));

		for (int s = 0; s < range; s++)
		{
			y += dy[dir];
			x += dx[dir];

			if (y < 1 || y > R || x < 1 || x > C)		// Overflow.
			{														// Change the direction as opposite way.		
				switch (dir)		// Set the direction coordinate based on direction.
				{
				case 1:			// Up.
					dir = 2;
					break;
				case 2:			// Down.
					dir = 1;
					break;
				case 3:			// Right.
					dir = 4;
					break;
				case 4:			// Left.
					dir = 3;
					break;
				default:
					break;
				}
				s -= 1;			
				y += dy[dir];	// Return to previous location because of overflow.
				x += dx[dir];
				continue;
			}
		}
		map[y][x] += 1;		// Increase the number of sharks on this location.
		shark[i].y = y;			// Update the new shark's data.
		shark[i].x = x;
		shark[i].dir = dir;	
	}
}

int Fishing(int cur)		// To capture the shark at idx column on the map.
{
	for (int i = 1; i <= R; i++)		// Each rows.
	{
		if (map[i][cur])	// If the shark exists. [The nearest one should be captured first.]	
		{
			map[i][cur] = 0;					// Delete the shark's existence.	
			int idx = Find(i, cur);			// To figure out the index of current shark.
			int tmp = shark[idx].size;		// To figure out the weight of current shark.
			shark.erase(shark.begin() + idx);		// The current shark was captured. It should be deleted in Shark data.
			return tmp;
		}
	}
	return 0;			// When there is no shark current column on the map.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> R >> C >> M;
	for (int i = 0; i < M; i++)
	{
		int r, c, s, d, z;	// (r,c) = location.		s = Speed.		d = Directino.		z = Size.
		cin >> r >> c >> s >> d >> z;
		shark.push_back({ r,c,s, d,z });	// Store the shark's data.
		map[r][c] = 1;	// The mark of shark's existence.
	}

	int answer = 0;		// answer = The total weight of captured sharks.
	for (int i = 1; i <= C; i++)		// The fisherman should move right way.
	{
		answer += Fishing(i);		// The weight of captured shark.
		Move();				// Move the whole of sharks.
		Arrange();			// Rearrange the map data based on new shark's data.
	}
	cout << answer << endl;		// The total weight as output.
}