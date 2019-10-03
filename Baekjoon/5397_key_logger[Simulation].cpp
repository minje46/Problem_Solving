#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

string input = "";				// input = The memory of input data.
string password = "";		// password = The user's password as output.

void Simulation()
{
	int idx = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '<')
		{
			if (!password.empty())
				idx -= 1;
		}

		else if (input[i] == '>')
		{
			if (idx < password.length())
				idx += 1;
		}

		else if (input[i] == '-')
		{
			if (!password.empty())
			{
				idx -= 1;
				if (idx < 0)
					idx = 0;
				else
					password.erase(password.begin() + idx);
			}
		}
		else
		{
			password.insert(password.begin() + idx, input[i]);
			idx += 1;
		}
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
	
		cin >> input;
		
		Simulation();

		cout << password << endl;
	}
}