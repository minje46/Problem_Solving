#include<iostream>
#include<algorithm>
#include<vector>

#define MAX 1001

using namespace std;

int N;		// N = The number of people to use atm.
int time[MAX] = { 0, };		// time = The memory of time to use ATM

int ATM()		// To calculate total time of spending ATM.
{
	int total = 0;		

	for (int i = 1; i <= N; i++)		// From first to last people.
	{
		int acc = 0;
		for (int j = 1; j <= i; j++)	// Each people should wait the previous one's time as well. 
			acc += time[j];			// It means the time will be accumulated.
		
		total += acc;		// Total time.
	}

	return total;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> time[i];

	sort(time, time + N + 1 , less<int>());		// Sort the time ascending order.
	
	cout << ATM() << endl;		
}