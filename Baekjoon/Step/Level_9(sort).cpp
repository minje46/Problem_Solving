// 9 - 2 (Merge_Sort) <- Array 로 구현
/*
#include <iostream>
using namespace std;

#define Size 1000005
int input[Size];
int output[Size];

void Merge_Sort(int front, int mid, int end)
{
	int i = front, j = mid + 1, k = front;

	while (i <= mid && j <= end)		// Compare the index of each array.
	{
		if (input[i] < input[j])
		{
			output[k] = input[i];
			i++;
			k++;
		}

		else if (input[i] > input[j])
		{
			output[k] = input[j];
			j++;
			k++;
		}
	}

	while (i <= mid)				// The rest of array after comparing two arrays. 
	{
		output[k] = input[i];
		i++;
		k++;
	}

	while (j <= end)
	{
		output[k] = input[j];
		j++;
		k++;
	}

	for (int i = front; i <= end; i++)
		input[i] = output[i];
}
// Split the array by binary.
void Split(int front, int end)
{
	int mid = (front + end) / 2;

	if (front != end)
	{
		Split(front, mid);
		Split(mid + 1, end);
		Merge_Sort(front, mid, end);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> input[i];


	Split(0, N - 1);

	for (int i = 0; i < N; i++)
		cout << input[i] << "\n";
}
*/

// 9 - 2 (Heap_Sort) <- Array 로 구현
/*
#include <iostream>
using namespace std;

#define Size 1000005
int arr[Size];

void Heap(int N, int i)
{
	int max = i;				// Initialize largest as root.
	int left = 2 * i + 1;		// left node.
	int right = 2 * i + 2;		// right node.

								// If left child is larger than root.
	if (left < N && arr[left] > arr[max])
		max = left;

	// If right child is larger than root.
	if (right < N && arr[right] > arr[max])
		max = right;

	// If largest value is not root node. It should be swapped.
	if (max != i)
	{
		swap(arr[i], arr[max]);

		// Recursively checking the sub tree of node which has largest value.
		Heap(N, max);
	}
}

void Sort(int N)
{
	// Build max heap first.
	// (It is not perfect max heap. Just pick the biggest value in root node.)
	for (int i = N / 2 - 1; i >= 0; i--)	// i = N/2-1 means binary access.. i guess.
		Heap(N, i);

	// Swap the first node which is the biggest value and last node.
	// Build max heap again with reduced array. (The biggest value is located in tail of array.)
	// (Reduced array means from zero to last -1.)
	for (int i = N - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);

		Heap(i, 0);		// Compare with root node(index = 0) because of swapping right befroe.
	}
}

void Print(int N)
{
	for (int i = 0; i < N; i++)
		cout << arr[i] << "\n";
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> arr[i];

	Sort(N);

	Print(N);
}
*/

// 9 - 3 (Counting_Sort) <- Array 로 구현
/*
#include <iostream>
using namespace std;

#define Size 10001
int arr[Size] = { 0, };

void Sort()
{
	for (int i = 1; i <= Size; i++)
	{
		while (arr[i] > 0)
		{
			cout << i << "\n";
			arr[i]--;
		}
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int N, input;
	cin >> N;

	for (int i = 0; i < N; i++)	// Count the value which user sets.
	{
		cin >> input;
		arr[input]++;
	}

	Sort();
}
*/

// 9 - 4
/*
#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int Range(vector<int> v)
{
	int max = v.front(), min = v.front();		// Initialize the max and min value.
	vector<int>::iterator iter = v.begin();		// The iterator of vector.
	
	for (iter; iter != v.end(); iter++)
	{
		if (max < *iter)
			max = *iter;

		if (min > *iter)
			min = *iter;
	}
	
	return (max - min);
}

bool compare(const pair<int, int> &p1, const pair<int, int> &p2)
{
	if (p1.second == p2.second)
		return p1.first < p2.first;			// This condition means comparing the second value which means counting of value.
												// And if there are some values which have same counting value, it returns smaller value first.
	return p1.second > p2.second;		// It compares the counting value of vectors.
}

int Mode(vector<int> v)
{
	vector<pair<int, int>> count;
	vector<int>::size_type i;

	sort(v.begin(), v.end());

	for (i = 0; i < v.size(); i++)
	{
		if (count.empty())		// It means when i is 0. 
		{							// When the count vector is empty, set the first element in count vector.
			count.push_back(pair<int, int>(v[i], 1));
			continue;				// After continue condition, it will be started at i = 1 which means second index.
		}

		if (count.back().first == v[i])		// Check the next value is duplicate or not. 
		{										// The reason why it is possible is original vecotr v is already sorted once.
			pair<int, int> temp = count.back();	// If the value of count vector is duplicate with next value of v vector which will be set next time. 
			temp.second++;				// It increase the counting in vector's second element which means for counting of value.
			count.pop_back();				// To update modified value which was increased the counting from previous count vector.
			count.push_back(temp);		// Set new modified vector.
		}
		else
			count.push_back(pair<int, int>(v[i], 1));		// It means there is no duplicate value in original v vector. 
	}

	sort(count.begin(), count.end(), compare);				// Sort with mode. (Depends on count how many times it is used.)

	if (count[0].second == count[1].second)
		return count[1].first;									// It means the second small value with the largest count value.
	else
		return count[0].first;									// It means the value of largest count value.
}

int Median(vector<int> v)
{
	sort(v.begin(), v.end());

	return v[(0 + v.size()) / 2];
}

double Sum(vector<int> v)
{
	double result = 0;

	for (int i = 0; i < v.size(); i++)
		result += v[i];

	result = round(result / v.size());

	return result;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	vector<int> v;		// Allocate vecotr memory by int type.
	int value;

	for (int i = 0; i < N; i++)
	{
		cin >> value;
		v.push_back(value);	// Allocate the value in end of vector.
	}

	cout << Sum(v) << endl;
	cout << Median(v) << endl;
	cout << Mode(v) << endl;
	cout << Range(v) << endl;
}
*/

// 9 - 5

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	string str;
	cin >> str;
	
	sort(str.begin(), str.end(), greater<char>());

	for (auto c : str)
		cout << c;
	cout << endl;
}


// 9 - 6
/*
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(string first, string second)
{
	// The first condition of sorting is the length of string.
	if (first.length() < second.length())
		return true;
	else if (first.length() == second.length())		// If the length of string are same, the alphabetic order is the second standard of sorting.
	{														// The smaller one is sorted frist.
		if (first < second)	
			return true;
		else
			return false;
	}
	else
		return false;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);

	int N;
	cin >> N;

	string temp;
	vector<string> v;

	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		v.push_back(temp);

		// To remove duplicate value in v vector with searching from begin to end - 1.
		for (int i = 0; i < v.size()-1; i++)
			if (temp == v[i])
				v.pop_back();
	}

	sort(v.begin(), v.end(), compare);

	for (int i = 0; i < v.size(); i++)
		cout << v[i] << "\n";
}
*/