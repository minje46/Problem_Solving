#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct instruct
{
	char op;
	int num, pivot;
};

vector<int> vc;
vector<instruct> in;

void Reorganize()
{
	for (int i = 1; i < vc.size(); i++)
	{
		if (vc[i] == i)
			continue;
	
		else
		{
			vector<int>::iterator it = find(vc.begin(), vc.end(), i);
			vc.erase(it);
			vc.insert(vc.begin()+i, i);
			in.push_back({ 'A', i, vc[i] + 1 });
		}
	}
}

void Change(char op, int moving, int pivot)
{
	vector<int>::iterator idx = find(vc.begin(), vc.end(), moving);		// �̵���ų �� search.
	vc.erase(idx);				// �ߺ��� ���ϱ� ����, ���� delete.

	idx = find(vc.begin(), vc.end(), pivot);
	if (op == 'A')				// A ������ ����, pivot�� ã�� �� ������ insert.
		vc.insert(idx, moving);

	else							// B ������ ����, pivot�� ã�� �� �ڷ� insert.
		vc.insert(idx + 1, moving);
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;						// N = The number of nodes.			M = The number of operations.
	cin >> N >> M;
	for (int i = 0; i <= N; i++)
		vc.push_back(i);		// ���� ����Ʈ �����.

	for (int i = 0; i < M; i++)
	{
		char ch;
		int moving, pivot;		// moving = The value to move.		pivot = The pivot.
		cin >> ch >> moving >> pivot;
		Change(ch, moving, pivot);
	}
	/*
	for (int i = 1; i < vc.size(); i++)
		cout << vc[i] << " ";
	cout << endl;
	*/
	Reorganize();
	/*
	for (int i = 1; i < vc.size(); i++)
		cout << vc[i] << " ";
	cout << endl;
	*/
	cout << in.size() << endl;
	for (int i = 0; i < in.size(); i++)
		cout << in[i].op << " " << in[i].num << " " << in[i].pivot << endl;
}