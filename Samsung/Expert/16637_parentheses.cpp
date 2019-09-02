#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

#define MAX 20
#define INF 987654321

using namespace std;

int N, answer = -INF;	// N = The size of calculation formula.		answer = The maximum result of calculation as output.
char formula[MAX];		// formula = The memory of calculation formula.
bool visit[MAX];			// visit = The memory of visited or not to distinguish using parentheses.

int Calculation()		// To calculate the full formula with priority order.
{
	vector<string>tmp;		// temporary memory.
	int i = 0;
	while (i < N)		// The size of formula.
	{
		if (!visit[i])		// Not parentheses.
		{
			string str = "";
			str = formula[i];
			tmp.push_back(str);	// Push the formula in a sequence.
			i += 1;
		}
		else				// Parenthese.
		{
			char op = formula[i + 1];		// Operator.
			switch (op)
			{
			case '+':	// Addition.
				tmp.push_back(to_string((formula[i] - '0') + (formula[i + 2] - '0')));
				break;
			case '-':	// Subtraction.
				tmp.push_back(to_string((formula[i] - '0') - (formula[i + 2] - '0')));
				break;
			case '*':	// Multiplication.
				tmp.push_back(to_string((formula[i] - '0') * (formula[i + 2] - '0')));
				break;
			default:
				break;
			}
			i += 3;		// Index controling to avoid duplicate.
		}
	}

	int tot = stoi(tmp[0]);		// Total sum.
	for (int i = 1; i < tmp.size(); i += 2)	// Even number is integer.
	{									// Odd number is operator.
		if (tmp[i] == "+")			
			tot += stoi(tmp[i + 1]);
		else if (tmp[i] == "-")
			tot -= stoi(tmp[i + 1]);
		else if (tmp[i] == "*")
			tot *= stoi(tmp[i + 1]);
	}
	return tot;
}

void DFS(int idx)		// To figure out the parentheses is possible or not step by step.
{
	answer = max(answer, Calculation());		// Compare the bigger total value.

	for (int i = idx; i < N - 2; i += 2)		// From now to N-2 to avoid overflow.
	{
		if (!visit[i] && !visit[i + 2])		// Parentheses has only one dimension,
		{											// Just consider the right next one.
			visit[i] = true;			// Next one.
			visit[i + 2] = true;
			DFS(i + 2);				// DFS.
			visit[i] = false;		// Return.
			visit[i + 2] = false;
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> formula[i];			// Input of formula.

	DFS(0);		// Do exhaustive search.

	cout << answer << endl;		// Output.
}