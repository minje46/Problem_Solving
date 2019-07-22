#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Node			// The struct memory for node to store coordination and index and children's info as well.
{
	int idx;				// Index.
	int x, y;				// Coordinations.
	Node *left;		
	Node *right;

	// Compare method #1
	const bool operator<(const Node &a)	// Define the compare function to do sort.
	{
		if (y == a.y)
			return x < a.x;		// Ascending order in X.
		
		return y > a.y;			// Descending order in Y.
	}
};

vector<Node> node;		// The memory of all nodes.

void Preorder(vector<int>& ans, Node *node)			// To figure out traversal of preorder. 
{
	if (node == NULL)		// The base case. [기저 사례.]
		return;

	ans.push_back(node->idx);		// Root.
	Preorder(ans, node->left);		// Left.
	Preorder(ans, node->right);		// Right.		의 순서를 가진다.
}

void Postorder(vector<int> &ans, Node *node)		// To figure out traversal of postorder. 
{
	if (node == NULL)		// The base case. [기저 사례.]
		return;

	Postorder(ans, node->left);		// Left.
	Postorder(ans, node->right);	// Right.
	ans.push_back(node->idx);		// Root.		의 순서를 가진다.
}

void Insert(Node *parent, Node *child)		// To insert(link) the node as child node from parent node.
{
	if(child->x < parent->x)		// The case of left child node. [Parent node 보다 작은 x 값을 가지는 경우.]
	{
		if (parent->left == NULL)	
			parent->left = child;
		else								// There is already child node in left side. So it should be checked again.
			Insert(parent->left, child);
	}
	else									// The case of right child node. [Parent node 보다 큰 x 값을 가지는 경우.]
	{
		if (parent->right == NULL)
			parent->right = child;
		else								// There is already child node in right side. So it should be checked again.
			Insert(parent->right, child);
	}
}

// Compare method #2
/*
bool comp(Node const &a, Node const &b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y > b.y;
}
*/

vector<vector<int>> solution(vector<vector<int>> nodeinfo)		// To figure out tree's order.
{
	for (int i = 0; i < nodeinfo.size(); i++)			// Input of each node such as index, x, y coordinations.
		node.push_back({ i + 1, nodeinfo[i][0], nodeinfo[i][1] });		// [idx, x, y 좌표 값을 node struct에 입력.]

	// Compare method #1
	sort(node.begin(), node.end());

	// Compare method #2
	//sort(node.begin(), node.end(), comp);			// [Y 기준, 내림차순. X 기준, 오름차순으로 Sorting.]

	Node *root = &node[0];						// The memory of root node.
	for (int i = 1; i < node.size(); i++)			// Build the tree.
		Insert(root, &node[i]);						// [Tree 형성.]


	vector<vector<int>> answer{ {}, {} };	// The fixed format of answer. [정해진 answer 형식.]
	Preorder(answer[0], root);					// To figure out preorder of tree.
	Postorder(answer[1], root);					// To figure out postorder of tree.

	return answer;										// Answer.
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	vector<vector<int>> input = { {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} };		// Input.
	
	vector<vector<int>> output = solution(input);		// Output.

	for (int i = 0; i < output.size(); i++)
	{
		for (int j = 0; j < output[i].size(); j++)
			cout << output[i][j] << ", ";
		cout << endl;
	}
}