#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
//#pragma warning(disable:4996)

#define MAX 4001

using namespace std;

struct Atom	// The whole of atom's data.
{
	int y, x;		// Location.
	int dir;		// Direction.
	int force;	// Force.
};

int N;			// N = The number of atoms.
vector<Atom> atom;		// atom = The memory of each atom's data.
int map[MAX][MAX];		// map = The memory of how many atoms are on the map.
bool visit[1001];				// visit = The memory of whether atom alive or not.
int dy[4] = { 1,-1,0,0 };		// [0: Up.]		[1: Down.]
int dx[4] = { 0,0,-1,1 };		// [2: Left.]	[3: Rihgt.]
int answer = 0;		// answer = The total value of atom's force which was extincted.			

bool Check()		// To figure out whether the atom alive or not.
{
	for (int i = 0; i < N; i++)
	{
		if (visit[i])		// [visit = true] means the atom alives. 
			return false;	// Keep moving.
	}
	return true;
}

int Crush(int idx)		// To figure out there is collision or not.
{
	int tot = 0;			// The total energy of crushed each other.
	int y = atom[idx].y;
	int x = atom[idx].x;

	if (map[y][x] >= 2)		// The case of crush.
	{
		for (int i = idx + 1; i < N; i++)		// Find the matched atom which was crushed.
		{												// [Crush 발생하는 또 다른 atom 찾기.]
			if (atom[i].y == y && atom[i].x == x)		// Another atom.
			{
				visit[i] = false;		// Pretends to be dead.
				map[y][x] -= 1;		// Decrease the number of atom.
				tot += atom[i].force;		// The energy after crushed.
			}
		}

		visit[idx] = false;			// Pretends to be dead.
		map[y][x] -= 1;			// Decrease the number of atom.
		tot += atom[idx].force;		// The energy after crushed.
	}
	return tot;		// The total energy.
}

void Move(int idx)		// To move the atom's location.
{
	int ny = atom[idx].y + dy[atom[idx].dir];
	int nx = atom[idx].x + dx[atom[idx].dir];

	map[atom[idx].y][atom[idx].x] = 0;		// The current atom will move or dead.	

	if (ny < 0 || ny >= MAX || nx < 0 || nx >= MAX)		// Overflow.
	{									// Delete the outrange's atom.
		visit[idx] = false;			// This atom pretends to be died.
		return;
	}
	map[ny][nx] += 1;		// Increase the number of atom.
	atom[idx].y = ny;		// Moved atom location.
	atom[idx].x = nx;		// Update.
}

void Atom_extinction()		// To figure out the atom's moving and crush.
{
	for (int i = 0; i < N; i++)
	{
		if (visit[i])		// Check only alive atom.
			Move(i);		// Move first.
	}

	for (int i = 0; i < N; i++)
	{
		if (visit[i])		// Check only alive atom.
			answer += Crush(i);		// Check it was crushed or not.
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

//	freopen("input.txt", "r", stdin);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		memset(map, 0, sizeof(map));
		memset(visit, false, sizeof(visit));
		atom.clear();
		answer = 0;

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			int x, y, d, k;
			cin >> x >> y >> d >> k;			// Input of original atom's data.
			atom.push_back({ (y + 1000) * 2,(x + 1000) * 2,d,k });		// [Crush가 0.5sec에 발생할 수 있기 때문에, 2배로 좌표 늘려서 정수에만 crush 발생 가능하도록.]
			map[(y + 1000) * 2][(x + 1000) * 2] = 1;		// The mark of atom exists.
			visit[i] = true;			// Atom alive.				
		}

		while(!Check())		// Until there is no more alive atom.
			Atom_extinction();			// To control all of atom.

		cout << "#" << t << " " << answer << endl;		// The total force of atom as output.
	}
}