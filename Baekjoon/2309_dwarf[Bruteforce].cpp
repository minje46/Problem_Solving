#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> dwarf;

void Search_dwarf(int sum)
{
	int x=0, y=0;									// x,y = temproray variable to store index of i and j.
	for (int i = 0; i < dwarf.size(); i++)
	{
		int temp = dwarf[i];
		for (int j = i + 1; j < dwarf.size(); j++)
		{
			temp += dwarf[j];					// The number of dwarf is already set and there are only two fake dwarfs in the group.
			if (temp == sum)					// Judge the sum of two fake dwarf's height.
			{					
				x = i;								// Index of the first fake dwarf.
				y = j;								// Index of the second fake dwarf.
				goto EXIT;						// Go to EXIT part directly. (The way of getting out nested loop.)
			}										// [중첩 loop 빠져나가는 방법.]
			else
				temp -= dwarf[j];				// If this dwarf is not fake, compare the next one.
		}
	}

	EXIT:											// It is connected with "goto".	
		dwarf.erase(dwarf.begin() + (x));
		dwarf.erase(dwarf.begin() + (y - 1));
}

int main(void)
{
	int total = 0, tall;				// total = Calculate all of dwarf's height.		tall = temp variable to get.
	for (int i = 0; i < 9; i++)
	{
		cin >> tall;
		dwarf.push_back(tall);
		total += tall;
	}

	sort(dwarf.begin(), dwarf.end());
	
	Search_dwarf(total-100);
	for (int i = 0; i < dwarf.size(); i++)
		cout << dwarf[i] << endl;
}