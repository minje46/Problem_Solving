#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

int CountBits(int n)	// Do count the number of bit is 1.
{
	int ret = 0;

	while (n)
	{
		if (n & 1)	// [Bit에 1이 존재 하는 수 만큼 ret가 count.]
			ret++;

		n = n >> 1;
	}
	return ret;		// [N의 2진수 bit 중에서 1의 bit 수 를 return.]
}

bool comp(const int &a, const int &b)	// To do sort based on big size of bits.
{
	int x = CountBits(a);
	int y = CountBits(b);

	return x > y;		// [Bit에 1이 많은 순으로 sort한다.]
}

bool Check(vector<vector<string>>relation, int row_len, int col_len, int subset)	// [subset의 값을 이용하여, columns의 조합 set이 candiate key가 될 수 있는지의 여부를 확인한다.]
{
	for (int a = 0; a < row_len - 1; a++)		// [비교를 하기 위한 table의 첫 번째 비교 대상.]
	{
		for (int b = a + 1; b < row_len; b++)	// [선택된 a를 제외한 모든 하위 tuple을 b로 설정하여 전체 탐색한다.]
		{
			bool flag = true;							// [Tuple a와 b가 서로 중복되는 값을 가지는지 파악하기 위한 flag 변수.]
			for (int k = 0; k < col_len; k++)		// [모든 columns들을 0~col_len까지 차례대로 확인하기 위함.]
			{	// [1을 column의 번호 만큼 bit shift 하여, subset의 해당되지 않는 column의 경우 0이 return된다. -> 비교할 필요 없는 column 이라는 의미.]
				if ((subset & 1 << k) == 0)		// [매번 a와 b의 모든 columns의 value들을 비교하는 것을 방지하기 위해, 
					continue;							// subset에 해당 되는 column만 비교한다.]
						
				if (relation[a][k] != relation[b][k])	// [Tuple a와 b의 중복 여부를 확인.]
				{
					flag = false;
					break;
				}
			}

			if (flag)										// [Tuple a와 b가 중복된다는 것을 의미. -> Candidate key가 될 수 없는 column의 조합 set.]
				return false;
		}
	}
	return true;
}

int solution(vector<vector<string>> relation)
{
	int answer = 0;
	int row_len = relation.size();				// The size of total tuples.
	int col_len = relation.front().size();		// The size of total columns.
	vector<int>candidate;						// The memory of candidate keys. [유일성만 만족하는 후보키의 집합 메모리.]
					// [<< 비트연산이 연산 우선 순위가 제일 높기 때문에 1의 비트 연산이 이루어진 결과 값과 i의 값을 비교하게 된다.]					
	for (int i = 1; i < 1 << col_len; i++)		// [i가 1<<col_len 값보다 작을 때 까지 loop를 반복하는 것.]
	{													// [예시 문제에서는 col_len=4 이기 때문에, i가 15까지 loop를 반복한다.]	
		if (Check(relation, row_len, col_len, i))		// [조합 set을 모두 search하면서, candidate key가 되는지 여부를 확인한다.]
			candidate.push_back(i);			// [최소성은 보장하지 못한, candidate key가 될 수 있는 모든 집합을 만든다.]
	}

	sort(candidate.begin(), candidate.end(), comp);		// [Bit의 1이 많은 순으로 내림차순 sort.]
	// [유일성만 만족하는 candidate key의 집합에서, 최소성을 만족시키는 candidate key를 선정하기 위한 작업.]
	while (!candidate.empty())
	{
		int n = candidate.back();		// [Bit의 1의 수를 기준으로 내림차순 sort되었기 때문에, 맨 뒤의 값이 최소성이 만족되는 candidate key가 된다.]
		candidate.pop_back();
		answer++;							// [유일성 + 최소성을 만족시킨 candidate key.]

		for (vector<int>::iterator it = candidate.begin(); it != candidate.end();)		// [Candidate key의 집합에서 최소성이 배제되는 set을 제거하기 위함.]
		{
			if ((n&*it) == n)				// [현재 최소성을 만족시킨 n의 bit와 *연산을 통해 n을 포함하고 있다는 것은, 현재 n의 column을 포함하고 있다는 의미.]
				it = candidate.erase(it);		// [Candidate key의 최소성 조건에 위배되기 때문에, erase.]
			else								// [현재 column을 포함하지 않은 candidate key의 경우, pass.]
				it++;							
		}
	}

	return answer;
}

int main(void)
{
	ios_base::sync_with_stdio(false);

	vector<vector<string>> relation = { {"100", "ryan", "music", "2"},{"200", "apeach", "math", "2"},{"300", "tube", "computer", "3"},{"400", "con", "computer", "4"},{"500", "muzi", "music", "3"},{"600", "apeach", "music", "2"} };

	cout << solution(relation) << endl;
}