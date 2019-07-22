#include<cstdio>
#pragma warning(disable:4996)

#define MAX 1000001

using namespace std;

int memo[MAX];

void init()
{
	memo[1] = 0;
	memo[2] = 1;
	memo[3] = 3;

	for (int i = 4; i < MAX; i+=2)
	{
		memo[i] = memo[i / 2] + 1;
		memo[i-1] = memo[i] + 1;
	}
}

int main(int argc, char** argv)
{
	init();
	int T, test_case;
	freopen("[scpc_pre1_2019]input_1.txt", "r", stdin);
	
	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		int X, Y;		// X = The firstt vlaue to do.			Y = The last vlaue to do.
		scanf("%d %d", &X, &Y);
		int Answer = 0;

		for (int i = X; i <= Y; i++)
			Answer += memo[i];

		printf("Case #%d\n", test_case + 1);
		printf("%d\n", Answer);
	}

	return 0;
}