#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct instruct
{
	char op;
	int num, pivot;
};
vector<instruct> in;

struct Node
{
	int value;
	struct Node *lptr;
	struct Node *rptr;
};
struct Node *head = (struct Node*)malloc(sizeof(struct Node));
struct Node *cur = (struct Node*)malloc(sizeof(struct Node));

void Insert(struct Node *ptr, int key)
{
	struct Node *next = ptr->rptr;
	struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->value = key;
	new_node->lptr = NULL;
	new_node->rptr = NULL;

	new_node->lptr = ptr;
	ptr->rptr = new_node;

	if (cur != NULL)
		cur = ptr->rptr;

	else
	{
		new_node->rptr = next;
		next->lptr = new_node;
	}
}

void Delete(struct Node *ptr)
{
	struct Node *prev = ptr->lptr;
	struct Node *next = ptr->rptr;

	prev->rptr = next;
	if (next != NULL)
		next->lptr = prev;
	free(ptr);
}

struct Node *Search(int key)
{
	struct Node *ptr = head;

	while (ptr != NULL)
	{
		if (ptr->value == key)
			return ptr;

		ptr = ptr->rptr;
	}

	return NULL;
}

void Reorganize(int n)
{
	struct Node *ptr = head;

	for (int i = 0; i <= n; i++)
	{
		if (i == 0)
		{
			ptr = ptr->rptr;
			continue;
		}

		if (ptr->value == i)
		{
			ptr = ptr->rptr;
			continue;
		}
		else
		{
			struct Node *prev = Search(i - 1);
			struct Node *cur = Search(i);
			Delete(cur);
			Insert(prev, i);

			cur = Search(i);
			in.push_back({ 'A', i, (cur->rptr)->value });
		}
	}
}

void Change(char op, int moving, int pivot)
{
	struct Node *ptr = Search(pivot);
	struct Node *mov = Search(moving);
	struct Node *prev = ptr->lptr;
	struct Node *next = ptr->rptr;

	if (op == 'A')
		Insert(prev, moving);

	else
		Insert(ptr, moving);

	Delete(mov);
}

void Print()
{
	struct Node *ptr = head;

	while (ptr->rptr != NULL)
	{
		cout << ptr->value << " ";
		ptr = ptr->rptr;
	}
	cout << endl;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	int N, M;						// N = The number of nodes.			M = The number of operations.
	cin >> N >> M;
	for (int i = 0; i <= N; i++)
	{
		if (i == 0)
		{
			head->value = 0;
			head->lptr = NULL;
			head->rptr = NULL;
			cur = head;
			continue;
		}
		Insert(cur, i);		// 연결 리스트 만들기.
	}
	cur = cur->rptr;
	free(cur);
	for (int i = 0; i < M; i++)
	{
		char ch;
		int moving, pivot;		// moving = The value to move.		pivot = The pivot.
		cin >> ch >> moving >> pivot;
		Change(ch, moving, pivot);
	}

	Print();

	Reorganize(N);
	cout << in.size() << endl;
	for (int i = 0; i < in.size(); i++)
		cout << in[i].op << " " << in[i].num << " " << in[i].pivot << endl;

}