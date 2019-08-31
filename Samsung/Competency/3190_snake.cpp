#include<iostream>
#include<vector>
#include<queue>

#define MAX 101

using namespace std;

const int dy[4] = { -1,1,0,0 };		// Up, Down.
const int dx[4] = { 0,0,-1,1 };		// Left, Right.

struct Snake
{
	int y, x;
	int dir;
};

int N, K, L;			// N = The size of map.		K = The number of apples.			L = The number of rotation.
Snake head = { 1,1,3 }, tail = { 0,0,0 };		// head, tail = The memory of each snake's haed and tail.
vector<Snake>body;				// body = The memory of all snake's body.
vector<pair<int, int>>apple;		// apple = The memory of apple's location.
queue<pair<int, char>> rotation;		// rotation = The memory of roatation.

int Convert(char ch)		// To convert the direction to rotate.
{
	int val;
	switch (head.dir)
	{
	case 0:		// Up.
	{
		if (ch == 'L')		// To left.	
			val = 2;	
		else					// To right.
			val = 3;
		break;
	}
	case 1:		// Down.
	{
		if (ch == 'L')		// To right.
			val = 3;
		else					// To left.
			val = 2;
		break;
	}
	case 2:		// Left.
	{
		if (ch == 'L')		// To down.
			val = 1;
		else					// To up.
			val = 0; 
		break;
	}
	case 3:		// Right.
	{
		if (ch == 'L')		// To up.
			val = 0;
		else					// To down.
			val = 1;
		break;
	}
	default:
		break;
	}
	return val;
}

int Move()		// To figure out the snake's movement by time.
{
	int time = 0;
	while (true) 
	{
		time++;
		int ny = head.y + dy[head.dir];		// The new location of head.
		int nx = head.x + dx[head.dir];		// Head moved first.

		if(body.size() == 0)		// If there is nothing in body, the previous head's location will be tail.
			tail = head;	
		body.push_back({ head.y, head.x, head.dir });		// The locaion of head's movement will be included to body.

		if (ny < 1 || ny >N || nx<1 || nx > N)	// Overflow.
			return time;

		for (int i = 0; i < body.size(); i++)		// Crush with itself.
		{
			if (body[i].y == ny && body[i].x == nx)
				return time;
		}

		bool flag = false;		// To check there is apple or not.
		for (int i = 0; i < apple.size(); i++)
		{
			if (ny == apple[i].first && nx == apple[i].second)
			{
				flag = true;
				apple.erase(apple.begin() + i);
				break;
			}
		}
		
		if (!flag)		// There is no apple.
		{
			for (int i = 0; i < body.size(); i++)
			{
				if (body[i].y == tail.y && body[i].x == tail.x)		// Tail should be reorganized.
				{
					body.erase(body.begin() + i);
					if (body.size() != 0)		// The last part will be new tail.
						tail = body[0];
					break;
				}
			}
		}

		head.y = ny;		// The new location will be head.
		head.x = nx;

		if (!rotation.empty() && time == rotation.front().first)		// If there is direction roation in the current time.
		{
			head.dir = Convert(rotation.front().second);
			rotation.pop();
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> K;			// Input.
	for (int i = 0; i < K; i++)
	{
		int y, x;
		cin >> y >> x;
		apple.push_back(make_pair(y, x));		// Apple's location.
	}
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int time;
		char ch;
		cin >> time >> ch;
		rotation.push(make_pair(time, ch));		// Rotation's location.
	}

	cout << Move() << endl;			// Output.
}
