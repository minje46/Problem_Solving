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
		if (n & 1)	// [Bit�� 1�� ���� �ϴ� �� ��ŭ ret�� count.]
			ret++;

		n = n >> 1;
	}
	return ret;		// [N�� 2���� bit �߿��� 1�� bit �� �� return.]
}

bool comp(const int &a, const int &b)	// To do sort based on big size of bits.
{
	int x = CountBits(a);
	int y = CountBits(b);

	return x > y;		// [Bit�� 1�� ���� ������ sort�Ѵ�.]
}

bool Check(vector<vector<string>>relation, int row_len, int col_len, int subset)	// [subset�� ���� �̿��Ͽ�, columns�� ���� set�� candiate key�� �� �� �ִ����� ���θ� Ȯ���Ѵ�.]
{
	for (int a = 0; a < row_len - 1; a++)		// [�񱳸� �ϱ� ���� table�� ù ��° �� ���.]
	{
		for (int b = a + 1; b < row_len; b++)	// [���õ� a�� ������ ��� ���� tuple�� b�� �����Ͽ� ��ü Ž���Ѵ�.]
		{
			bool flag = true;							// [Tuple a�� b�� ���� �ߺ��Ǵ� ���� �������� �ľ��ϱ� ���� flag ����.]
			for (int k = 0; k < col_len; k++)		// [��� columns���� 0~col_len���� ���ʴ�� Ȯ���ϱ� ����.]
			{	// [1�� column�� ��ȣ ��ŭ bit shift �Ͽ�, subset�� �ش���� �ʴ� column�� ��� 0�� return�ȴ�. -> ���� �ʿ� ���� column �̶�� �ǹ�.]
				if ((subset & 1 << k) == 0)		// [�Ź� a�� b�� ��� columns�� value���� ���ϴ� ���� �����ϱ� ����, 
					continue;							// subset�� �ش� �Ǵ� column�� ���Ѵ�.]
						
				if (relation[a][k] != relation[b][k])	// [Tuple a�� b�� �ߺ� ���θ� Ȯ��.]
				{
					flag = false;
					break;
				}
			}

			if (flag)										// [Tuple a�� b�� �ߺ��ȴٴ� ���� �ǹ�. -> Candidate key�� �� �� ���� column�� ���� set.]
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
	vector<int>candidate;						// The memory of candidate keys. [���ϼ��� �����ϴ� �ĺ�Ű�� ���� �޸�.]
					// [<< ��Ʈ������ ���� �켱 ������ ���� ���� ������ 1�� ��Ʈ ������ �̷���� ��� ���� i�� ���� ���ϰ� �ȴ�.]					
	for (int i = 1; i < 1 << col_len; i++)		// [i�� 1<<col_len ������ ���� �� ���� loop�� �ݺ��ϴ� ��.]
	{													// [���� ���������� col_len=4 �̱� ������, i�� 15���� loop�� �ݺ��Ѵ�.]	
		if (Check(relation, row_len, col_len, i))		// [���� set�� ��� search�ϸ鼭, candidate key�� �Ǵ��� ���θ� Ȯ���Ѵ�.]
			candidate.push_back(i);			// [�ּҼ��� �������� ����, candidate key�� �� �� �ִ� ��� ������ �����.]
	}

	sort(candidate.begin(), candidate.end(), comp);		// [Bit�� 1�� ���� ������ �������� sort.]
	// [���ϼ��� �����ϴ� candidate key�� ���տ���, �ּҼ��� ������Ű�� candidate key�� �����ϱ� ���� �۾�.]
	while (!candidate.empty())
	{
		int n = candidate.back();		// [Bit�� 1�� ���� �������� �������� sort�Ǿ��� ������, �� ���� ���� �ּҼ��� �����Ǵ� candidate key�� �ȴ�.]
		candidate.pop_back();
		answer++;							// [���ϼ� + �ּҼ��� ������Ų candidate key.]

		for (vector<int>::iterator it = candidate.begin(); it != candidate.end();)		// [Candidate key�� ���տ��� �ּҼ��� �����Ǵ� set�� �����ϱ� ����.]
		{
			if ((n&*it) == n)				// [���� �ּҼ��� ������Ų n�� bit�� *������ ���� n�� �����ϰ� �ִٴ� ����, ���� n�� column�� �����ϰ� �ִٴ� �ǹ�.]
				it = candidate.erase(it);		// [Candidate key�� �ּҼ� ���ǿ� ����Ǳ� ������, erase.]
			else								// [���� column�� �������� ���� candidate key�� ���, pass.]
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