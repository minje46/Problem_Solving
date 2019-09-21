#include<iostream>
#include<algorithm>
#include <string>
#include <vector>

using namespace std;

bool comp(const vector<string> &a, const vector<string> &b)		// Customized sort.
{
	string p1, p2;
	for (int i = 0; i<a[0].size(); i++)
		p1 += toupper(a[0][i]);			// Case insensitive.	[Head]
	for (int i = 0; i < b[0].size(); i++)
		p2 += toupper(b[0][i]);			// Make as upper case to compare.

	if (p1.compare(p2) == 0)				// Numerical.	[Middle]
		return stoi(a[1]) < stoi(b[1]);	

	if (p1.compare(p2)<0)					// Stable sort.
		return true;
	else
		return false;
}

vector<string> solution(vector<string> files)		// To figure out the file's order.
{
	vector<string> answer;			
	vector<vector<string>> data(files.size(), vector<string>(3));		// [Head], [Middle], [Tail]
	for (int i = 0; i<files.size(); i++)		// For each file names.
	{
		int y = 0, x = 0;			// y = The index of file.		x = The index of current file's string.
		while (x<files[i].size())		// [Head.]
		{
			if (files[i][x]<'0' || files[i][x] >'9')		// Only characters.
				data[i][y] += files[i][x];
			else
			{
				y += 1;
				break;
			}
			x += 1;
		}

		while (x<files[i].size())			// [Middle.]
		{
			if (files[i][x] >= '0' && files[i][x] <= '9')		// Only numbers.
				data[i][y] += files[i][x];
			else
			{
				y += 1;
				break;
			}
			x += 1;
		}

		while (x<files[i].size())			// [Tail.]
		{
			data[i][y] += files[i][x];		// remainders.
			x += 1;
		}
	}

	stable_sort(data.begin(), data.end(), comp);
	for (int i = 0; i<files.size(); i++)
		answer.push_back(data[i][0] + data[i][1] + data[i][2]);
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vector<string> input = { "img12.png", "img10.png", "img02.png", "img1.png", "IMG01.GIF", "img2.JPG" };
	vector<string> output = solution(input);
	for (int i = 0; i < output.size(); i++)
		cout << output[i] << endl;
}