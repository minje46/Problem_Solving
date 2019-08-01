#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>

#define MAX 101

using namespace std;

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

		int dy, dx, dir = shark[i].dir;
		switch (dir)		// Set the direction coordinate based on direction.
		{
		case 1:			// Up.
			dy = -1;
			dx = 0;
			break;
		case 2:			// Down.
			dy = 1;
			dx = 0;
			break;
		case 3:			// Right.
			dy = 0;	
			dx = 1;
			break;
		case 4:			// Left.
			dy = 0;
			dx = -1;
			break;
		default:
			break;
		}

		int y = shark[i].y;		// The current shark's location.
		int x = shark[i].x;
		for (int s = shark[i].speed; s > 0; s--)
		{
			y += dy;			// Move one by one.
			x += dx;
								// Overflow. [Change the direction as opposite way.]
			if (y < 1)		// Up. [Change the way as Down.]	
			{
				y = 2;			
				dy *= -1;	// Up -> Down.
				dir = 2;		// Down.
			}
			
			else if (y > R)		// Down. [Change the way as Up.]
			{
				y = R - 1;
				dy *= -1;	// Down -> Up.
				dir = 1;		// Up.
			}
			
			else if (x < 1)		// Left. [Change the way as Right.]
			{
				x = 2;
				dx *= -1;	// Left -> Right.
				dir = 3;		// Right.
			}

			else if (x > C)		// Right. [Change the way as Left.]
			{
				x = C - 1;
				dx *= -1;	// Right -> Left.
				dir = 4;		// Left.
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