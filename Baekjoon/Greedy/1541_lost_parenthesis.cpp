#include<iostream>
#include<string>

using namespace std;

string input;			// input = The input of the basic formula.
int answer = 0;		// answer = The minimum total value as output.

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	bool flag = false;			// To check minus or addition.
	string tmp = "";			// temporary memory.
	cin >> input;
	for (int i = 0; i <= input.length(); i++)
	{
		if (input[i] >= '0' && input[i] <= '9')		// Integer.
			tmp += input[i];
		else
		{
			if (flag)				// Do subtraction.
				answer -= stoi(tmp);
			else					// Do addition.
				answer += stoi(tmp);
			tmp = "";			// Initialization.

			if (input[i] == '-')	// Greedy calculation.
				flag = true;
		}
	}

	cout << answer << endl;		// Output.
}