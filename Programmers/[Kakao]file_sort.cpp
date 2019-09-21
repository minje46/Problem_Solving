#include<iostream>
#include<algorithm>
#include <string>
#include <vector>

using namespace std;

bool Pred(vector<string> a, vector<string> b)
{
	string a1, b1;
	for (int i = 0; i<a[0].size(); i++)
		a1 += toupper(a[0][i]);

	for (int i = 0; i<b[0].size(); i++)
		b1 += toupper(b[0][i]);

	if (a1.compare(b1) == 0)
		return stoi(a[1])<stoi(b[1]);

	if (a1.compare(b1)>0)
		return false;
	else
		return true;
}

vector<string> solution(vector<string> files) {
	vector<string> answer;
	vector<vector<string>> data(files.size(), vector<string>(3));

	int temp = 0;
	int j = 0;
	for (int i = 0; i < files.size(); i++)
	{
		j = 0;
		temp = 0;
		while (j < files[i].size())
		{
			if ((files[i][j] < '0' || files[i][j] > '9'))
				data[i][temp] += files[i][j];
			else
			{
				temp++;
				break;
			}
			j++;
		}
		while (j < files[i].size())
		{
			if (files[i][j] >= '0'&&files[i][j] <= '9')
				data[i][temp] += files[i][j];
			else
			{
				temp++;
				break;
			}
			j++;
		}
		while (j < files[i].size())
		{
			data[i][temp] += files[i][j];
			j++;
		}
	}
	stable_sort(data.begin(), data.end(), Pred);

	for (int i = 0; i < files.size(); i++) {
		answer.push_back(data[i][0] + data[i][1] + data[i][2]);
	}
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