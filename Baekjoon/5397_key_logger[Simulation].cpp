#include<iostream>
#include<string>
#include<list>

using namespace std;

string input = "";				// input = The memory of input data.
list<char> password;		// password = The user's password as output.

void Simulation()		// To figure out the password based on key logger.
{
	list<char>::iterator idx = password.begin();		// Index memory.
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '<')		// Move to left.
		{
			if (idx != password.begin())		// Avoid underflow.
				idx--;
		}
		else if (input[i] == '>')		// Move to right.
		{
			if (idx != password.end())			// Avoid overflow.
				idx++;
		}
		else if (input[i] == '-')		// Back space.
		{
			if (idx != password.begin())		// Avoid underflow.
				password.erase((--idx)++);
		}
		else								// Insert the character.
			password.insert(idx, input[i]);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++)
	{	// Initialization.
		input.clear();
		password.clear();
	
		cin >> input;		// Input.

		Simulation();		// Key logger.
		for (auto i : password)
			cout << i;		// Output.
		cout << endl;
	}
}