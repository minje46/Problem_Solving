#include<iostream>
#include<memory.h>

#define MAX_M 100001
#define MAX_C 4097
#define INF 50000000

using namespace std;

int M, C, I;			// M = The size of array memory.		C = The size of code block.		I = The size of input data.
unsigned int arr[MAX_M];			// arr = The memory for array.
char code[MAX_C], input[MAX_C];		//  code = The memory of code block.			input = The memory of input data.
int start = -1, fin = -1;				// start,fin = The index of loop's start and finish.

int Find_finish(int s)		// To figure out the index of closed loop location.
{
	int cnt = 0;			// Count the number of start loop to match proper pair.
	for (int i = s + 1; i < C; i++)
	{
		if (code[i] == '[')		// [내부의 중첩 loop가 존재하는 것을 의미.]
			cnt++;
		else if (code[i] == ']')		// [내부의 중첩 loop를 제외하고, match되는 closed 를 찾기 위함.]
		{
			if (cnt != 0)
				cnt--;
			else
				return i;
		}
	}
}

int Find_start(int f)		// To figure out the index of open loop location.
{
	int cnt = 0;			// Count the number of start loop to match proper pair.
	for (int i = f - 1; i > 0; i--)
	{
		if (code[i] == ']')		// [내부의 중첩 loop가 존재하는 것을 의미.]
			cnt++;

		else if (code[i] == '[')		// [내부의 중첩 loop를 제외하고, match되는 open을 찾기 위함.]
		{
			if (cnt != 0)
				cnt--;
			else
				return i;
		}
	}
}

bool Interpreter()			// To do each instructions.
{
	int idx = 0, cnt = 0, ptr = 0;		// idx = The index of memory.		cnt = The number of instructions worked.		ptr = The index of input memory.
	bool flag = false;		// boolean for loop or not.

	for (int i = 0; i < C; i++)		// The whole of code block.
	{		
		if (ptr > I)		// There is no more things to read in input array.
			return true;

		if (cnt == INF)		// The condition for loop. 
		{
			flag = true;
			break;
		}

		switch (code[i])
		{
		case '-':		// Decrease value.
			arr[idx] -= 1;

			if (arr[idx] == -256)		// Underflow.
			{
				arr[idx] %= 256;
			}
			break;

		case '+':		// Increase value.
			arr[idx] += 1;

			if (arr[idx] == 256)			// Overflow.
				arr[idx] %= 256;
			break;

		case '<':		// Decrease pointer.
			if(--idx < 0)
				idx = M - 1;
			break;

		case '>':		// Increase pointer.
			if (++idx == M)
				idx = 0;
			break;

		case '[':			// Loop start.
			start = i;
			if (arr[idx] == 0)
			{
				fin = Find_finish(i);
				i = fin - 1;
			}
			break;

		case ']':			// Loop finish.
			fin = i;
			if (arr[idx] != 0)
			{
				start = Find_start(i);
				i = start - 1;
			}
			break;

		case '.':
			break;

		case ',':			// Read the character.
			if (ptr == I)
				arr[idx] = 255;
			else
				arr[idx] = input[ptr];
			ptr++;
			break;

		default:
			break;
		}
		cnt++;
	}

	int loop = 0;		// [Nested loop를 판단하기 위한 count.]
	for (int i = fin + 1; i < C; i++)
	{
		if (code[i] == '[')
			loop++;

		if (code[i] == ']')
		{
			if (loop == 0)
			{
				fin = i;
				break;
			}
			else
				loop--;
		}
	}

	if (flag)
	{
		start = Find_start(fin);		// [Nested loop에서 가장 바깥 loop의 index를 찾기 위함.]
		return false;
	}
	else
		return true;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.	
		memset(arr, 0, sizeof(arr));
		memset(code, ' ', sizeof(code));
		memset(input, ' ', sizeof(input));

		cin >> M >> C >> I;
		for (int i = 0; i < C; i++)
			cin >> code[i];
		for (int i = 0; i < I; i++)
			cin >> input[i];

		if (Interpreter())
			cout << "Terminates" << endl;
		else
			cout << "Loops" << " " << start << " " << fin << endl;
	}
}