#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int L, C;													// L = The length of passwords.		// C = The lists example of alphabet to make passwords.
char *alphabet;										// Input of alphabet list.
bool visited[20] = { false, };						// Check the visited or not matching each alphabet in list.
vector<char> pass_wrods;						// The list of pass words.
char vowel[5] = { 'a','e','i','o','u' };

void Print()												// Print passwords.
{
	for (int i = 0; i < pass_wrods.size(); i++)
		cout << pass_wrods[i];
	cout << endl;
}

bool Promising()										// Judge whether passwords fit conditions or not.		
{
	bool flags = false;								// For checking vowel.
	int cnt = 0;											// For checking the number of consonants.	

	for (int i = 0; i < pass_wrods.size(); i++)	
	{
			if (pass_wrods[i]=='a' || pass_wrods[i]=='e' || pass_wrods[i]=='i' || pass_wrods[i]=='o' || pass_wrods[i]=='u')
				flags = true;
			else
				cnt++;
	}

	if (cnt >= 2 && flags)							// Passwords have one more vowels and two more consonants.				
		return true;

	else
		return false;
}

void Password(int len, int idx)					// Find proper passwords.
{
	if (len == L)										// The given length of passwords.
	{
		if (Promising())								// Judge whether passwords fit conditions or not.		
			Print();										// If the passwords fit conditions, Print it.
		return;											// If not, skip.
	}
	
	for (int i = idx; i < C; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			pass_wrods.push_back(alphabet[i]);
			Password(len + 1, i + 1);				// Do DFS recursively.

			pass_wrods.pop_back();				// Pop the last one.
			visited[i] = false;							// Reset visited way.
		}
	}
}

int main(void)
{
	cin >> L >> C;								// Input of length and the number of characters.
	alphabet = new char[C];					// Allocate memory of alphabet list.
	
	for (int i = 0; i < C; i++)					
		cin >> alphabet[i];						// Input of alphabet list.

	sort(alphabet, alphabet+C);				// Sort alphabets in list.	
	
	Password(0, 0);								// The length of alphabet list,	each alphabet.
}
