#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#pragma warning(disable:4996)

using namespace std;

struct point				// The memory of point's coordinate.
{
	long long x, y;
};
point pivot;				// The memory of first point to start.

double Distance(point A, point B)			// Figure out the distance between two points.
{														// [두 점의 거리를 비교한다.]
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));		// Return the distance.
}

long long CCW(point A, point B, point C)		// Figure out the angle is counter clock wise or not.
{																// [CCW와 CW를 판단한다.]	
	return ((B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x));	// Based on cross product formula.
}

bool Angle_sort(point A, point B)		// Figure out whiconvex_hull one is smaller between point a and point b.			
{													// [Sort를 하기 위해, 점 a와 b 중 어떤것이 더 작은 값인지 판단해줄 comparator method.]	
	long long left = CCW(pivot, A, B);	// Judge the points have left way or right way. [Left일 경우 CCW라고 판단 / Right일 경우 CW 라고 판단.]
										// [3점을 이었을 때, 3번 째 점이 왼쪽에 위치하는지, 오른쪽에 위치하는지 판단.]
	if (left > 0)			// It has CCW.
		return true;		// [양의 값은 CCW를 가진다고 판단.]

	if (left < 0)			// It has CW.
		return false;	// [음의 값은 CW를 가진다고 판단.]

	else					// If it has zero, it should be considered it is located further.
	{						// [동일선상에 있을 경우, 거리를 비교해서 멀리 있는 점인지 확인한다.]	
		if (Distance(pivot, A) < Distance(pivot, B))		// Compare the distance from pivot point.
			return true;			// [멀리 위치한 점은 사용해도 되지만, 가까이 위치한 점은 불필요하다.]
		else						// [가까이 위치한 점은 나중에 멀리 위치한 점의 선분에 포함될 것이기 때문.]
			return false;
	}
}

int main(void)
{
	int C;
	scanf("%d", &C);

	vector<point>pts(C);					// The memory of whole points.
	for (int i = 0; i < C; i++)
		scanf("%lld %lld", &pts[i].x, &pts[i].y);	// Input of points coordinate.

	int idx_pivot = 0;							// The memory of pivot's index to swap based on index.
	for (int i = 0; i<pts.size(); i++)		// To figure out pivot point.(=P[0])
		if (pts[i].y < pts[idx_pivot].y || (pts[i].y == pts[idx_pivot].y && pts[i].x < pts[idx_pivot].x))	// The lowest y-coordinate and x-coordinate will be pivot.
			idx_pivot = i;						// [y좌표 중 가장 작은 점이 pivot이 된다. y좌표가 같은 경우에는 x좌표도 함께 비교해서 pivot을 설정한다.]

	pivot = pts[idx_pivot];					// Set pivot point.
	swap(pts[0], pts[idx_pivot]);		// Let pivot point be first one as P[0]. [pivot을 P[0]에 위치시키기 위해 Swap.]
	sort(pts.begin() + 1, pts.end(), Angle_sort);	// Do angle sort whole of points except pivot. [Pivot을 제외한 모든 점을 Angle sort한다.]

	vector<point> convex_hull;			// The memory of convex hull's points.	[Stack 대신 vector를 사용해서 convex hull을 그릴 수 있는 points을 저장.]
	convex_hull.push_back(pts[0]);	// The pivot. (pts[0] == pivot)	
	convex_hull.push_back(pts[1]);	// The first point except pivot. [Pivot과 P1, P2를 시작으로 P[N]까지 비교를 한다.]
	for (int i = 2; i < pts.size(); i++)		// Except P[0] and P[1].
	{
		while (convex_hull.size() >= 2 && CCW(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) <= 0)	// [Convex hull을 그리기 위해서, 선분이 내부(왼쪽)으로 꺽이는지 판단한다.]
			convex_hull.pop_back();		// Pop the present point which has uncorrect conditions. (P[i])		// [최근 3점의 선분 방향이 바깥쪽이라면, 새로운 점(P[i])를 pop.]

		convex_hull.push_back(pts[i]);	// Push the next point. (P[i])
	}

	double max_dist = -1;					// The memory of maximum distance between points.
	for (int i = 0; i < convex_hull.size(); i++)		// [Convex hull을 이루는 점들의 집합에서 두 점 사이의 최대 거리가 나올 것.]	-> 현재 O(n^2 logn)
		for(int j=i+1; j<convex_hull.size(); j++)	// [이를 증명하는 것이 rotating calipers 이론.] -> 이용하면 O(nlogn) 으로 성능 높일 수 있다.
			max_dist = max(Distance(convex_hull[i], convex_hull[j]), max_dist);		// Compare two points inside convex hull.

	printf("%.6f \n", max_dist);			// Output of maximum distance.
}