#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

struct point					// The memory of point's coordinate.
{
	long long x, y;
};
point pivot;					// The memory of first point to start.

double Distance(point A, point B)			// Figure out the distance between two points.
{														// [두 점의 거리를 비교한다.]
	return pow(A.x - B.x, 2) + pow(A.y - B.y, 2);		// Return the distance.
}

long long Cross_product(point A, point B, point C)		// Figure out the angle is counter clock wise or not.
{																			// [CCW와 CW를 판단한다.]	
	return ((B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x));	// Based on cross product formula.
}

bool Same(point A, point B)
{
	if (A.x == B.x && A.y == B.y)
		return true;
	else
		return false;
}

int main(void)
{
	int N;											// The number of points.
	cin >> N;

	vector<point>pts(N);					// The memory of whole points.
	for (int i = 0; i < N; i++)
		cin >> pts[i].x >> pts[i].y;		// Input of points coordinate.

	int idx_pivot = 0;							// The memory of pivot's index to swap based on index.
	for (int i = 0; i < pts.size(); i++)		// To figure out pivot point.(=P[0])
		if (pts[i].x < pts[idx_pivot].x || (pts[i].x == pts[idx_pivot].x && pts[i].y < pts[idx_pivot].y))	// The lowest y-coordinate and x-coordinate will be pivot.
			idx_pivot = i;						// [y좌표 중 가장 작은 점이 pivot이 된다. y좌표가 같은 경우에는 x좌표도 함께 비교해서 pivot을 설정한다.]

	pivot = pts[idx_pivot];					// Set pivot point.
	swap(pts[0], pts[idx_pivot]);		// Let pivot point be first one as P[0]. [pivot을 P[0]에 위치시키기 위해 Swap.]

	// [여기 까지는 Same as Graham Scan algorithm.] [y,x 좌표 중 가장 아래의 점을 pivot 설정하고 P[0]으로 세팅까지.]

	vector<point> convex_hull;				// The memory of convex hull's points.	[Stack 대신 vector를 사용해서 convex hull을 그릴 수 있는 points을 저장.]
	convex_hull.push_back(pts[0]);		// The pivot. (pts[0] == pivot)	
	convex_hull.push_back(pts[1]);

	while (true)
	{
		int idx = 0;
		for (int i = 0; i < pts.size(); i++)
		{
			if (Cross_product(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) > 0)	// [외적 값이 가장 큰 것을 선택.]
			{	// convex_hull.size()-2 = pivot.		convex_hull.back() = random value or previous big cross product coordinate.		pts[i] = compared coordinate.
				convex_hull.back() = pts[i];		// Update the coordinate. [back에 저장되어 있던 좌표보다, 외적값이 더 큰 좌표를 찾음.] 
				idx = i;									// Remember the index of that coordinate. [좌표의 index 저장.]
			}

			else if (Cross_product(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) == 0)	// [동일선상에 있는 경우.]
			{
				if (Distance(convex_hull[convex_hull.size() - 2], convex_hull.back()) < Distance(convex_hull[convex_hull.size() - 2], pts[i]))	// [더 멀리 있는 좌표를 선택.]
				{												// 랜덤하게 넣어놨던 점이랑, 실제 최소 정점이랑 변경
					convex_hull.back() = pts[i];		// Update the coordinate. [back에 저장되어 있던 좌표보다, 외적값이 더 큰 좌표를 찾음.] 
					idx = i;									// Remember the index of that coordinate. [좌표의 index 저장.]
				}
			}
		}
		if (idx != 0)		// [idx==0 인 경우는, start coordinate를 다시 찾은 것이므로, convex hull의 완성을 의미.]
			swap(pts[idx], pts.back());			// 정점들중에서 최소 정점으로 선택된 것을 맨뒤로 이동.
		pts.pop_back();								// 최소 정점은 이제 사용되었으니 팝.

		if (Same(convex_hull[0], convex_hull.back()))	// [Convex hull의 완성을 확인.]
		{
			convex_hull.pop_back();								// [중복되는 좌표이므로 제거.]
			break;
		}

		convex_hull.push_back(pts.back());	// 맨뒤에 있는 정점을 랜덤하게 푸쉬.
	}

	cout << convex_hull.size() << endl;
}