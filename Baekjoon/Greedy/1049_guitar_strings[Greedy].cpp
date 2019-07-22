#include<iostream>
#include<algorithm>

#define MAX 101
#define INF 987654321

using namespace std;

int N, M;				// N = The number of guitar strings to buy at least.		M = The number of brands sell guitar strings.
int indv = INF, pack = INF;	// indv = The cost of individual string.		pack = The cost of string package.

int Guitar()			// To figure out the minimum total cost for buying guitar strings.
{
	int answer = INF;		
	
	if (N <= 6)		// The only case to buy strings individually.
		answer = min(pack, indv*N);	// Compare the package cost and N's cost.
	
	else
	{
		int k = N / 6;
		if (N % 6 == 0)		// It just consider buying package sets or indiviual sets.
			answer = min(pack*k, indv*N);		// [N이 6개로 떨어지는 경우, package set과 individual set만 비교하면 된다.]
		else						
		{
			answer = min(pack*k + indv * (N % 6), indv*N);		// [6개 단위는 package로 구매하고, 남은 개수는 individual set으로 구매한 경우와 전체 individual set 으로 구매한 경우 비교.]
			answer = min(answer, pack*(k + 1));			// [N개를 초과하더라도, package로 구매할 수도 있기 때문에, 예외 경우 고려.]
		}
	}
	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;

		pack = min(pack, a);			// The cheapest cost of string package was stored.
		indv = min(indv, b);				// The cheapest cost of individual string was stored.
	}

	cout << Guitar() << endl;			// The minimum total cost for buying guitar strings.
}