#include<iostream>

using namespace std;

int N, pre_idx = 0;															// N = the number of elements.			pre_idx = index of preorder.
int *pre, *post, *in, *position;											// Array memory for each orders.

void init(int in_start, int in_end, int po_start, int po_end)		// Do recursive divide to find original tree using inorder and post order.
{
	if (in_start > in_end || po_start > po_end)						// It is the cases of overflow.
		return;																

	int node = post[po_end];												// The post order's last value is root of tree.	
	pre[pre_idx++] = node;												// root value is stored in preorder.

	int in_idx = position[node];											// Find the root value's index in inorder.
	init(in_start, in_idx - 1, po_start, po_start+in_idx-in_start - 1);	// [Root value를 제외하고 Left child root 와 Right child root만 이용하기 위함.]
	init(in_idx + 1, in_end, po_start+in_idx-in_start, po_end - 1);	// 	[po_start+in_idx-in_idx = 	inorder에서 post order의 마지막 값을 뺀 index 계산.]
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	cin >> N;												// N = the number of elements.						
	pre = new int[N];									// Allocate the memory of pre order.

	in = new int[N];										// Allocate the memory of in order.
	for (int i = 0; i < N; i++)	
		cin >> in[i];										// Input of in order.

	post = new int[N];									// Allocate the memory of post order.
	for (int i = 0; i < N; i++)		
		cin >> post[i];									// Input of post order.	

	position = new int[N];								// Allocate the memory of in order's index.
	for (int i = 0; i < N; i++)
		position[in[i]] = i;								// Save the each index of inorder value.
																// [Inorder의 값에 대한 index를 저장.]
	init(0, N - 1, 0, N - 1);							// Initialize the segment tree.	[ Inorder_start, Inorder_end, Postorder_start, Postorder_end]

	for (int i = 0; i < N; i++)
		cout << pre[i] << " ";							// Output of pre order.
	cout << endl;
}