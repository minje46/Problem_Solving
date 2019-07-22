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
{														// [�� ���� �Ÿ��� ���Ѵ�.]
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));		// Return the distance.
}

long long CCW(point A, point B, point C)		// Figure out the angle is counter clock wise or not.
{																// [CCW�� CW�� �Ǵ��Ѵ�.]	
	return ((B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x));	// Based on cross product formula.
}

bool Angle_sort(point A, point B)		// Figure out whiconvex_hull one is smaller between point a and point b.			
{													// [Sort�� �ϱ� ����, �� a�� b �� ����� �� ���� ������ �Ǵ����� comparator method.]	
	long long left = CCW(pivot, A, B);	// Judge the points have left way or right way. [Left�� ��� CCW��� �Ǵ� / Right�� ��� CW ��� �Ǵ�.]
										// [3���� �̾��� ��, 3�� ° ���� ���ʿ� ��ġ�ϴ���, �����ʿ� ��ġ�ϴ��� �Ǵ�.]
	if (left > 0)			// It has CCW.
		return true;		// [���� ���� CCW�� �����ٰ� �Ǵ�.]

	if (left < 0)			// It has CW.
		return false;	// [���� ���� CW�� �����ٰ� �Ǵ�.]

	else					// If it has zero, it should be considered it is located further.
	{						// [���ϼ��� ���� ���, �Ÿ��� ���ؼ� �ָ� �ִ� ������ Ȯ���Ѵ�.]	
		if (Distance(pivot, A) < Distance(pivot, B))		// Compare the distance from pivot point.
			return true;			// [�ָ� ��ġ�� ���� ����ص� ������, ������ ��ġ�� ���� ���ʿ��ϴ�.]
		else						// [������ ��ġ�� ���� ���߿� �ָ� ��ġ�� ���� ���п� ���Ե� ���̱� ����.]
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
			idx_pivot = i;						// [y��ǥ �� ���� ���� ���� pivot�� �ȴ�. y��ǥ�� ���� ��쿡�� x��ǥ�� �Բ� ���ؼ� pivot�� �����Ѵ�.]

	pivot = pts[idx_pivot];					// Set pivot point.
	swap(pts[0], pts[idx_pivot]);		// Let pivot point be first one as P[0]. [pivot�� P[0]�� ��ġ��Ű�� ���� Swap.]
	sort(pts.begin() + 1, pts.end(), Angle_sort);	// Do angle sort whole of points except pivot. [Pivot�� ������ ��� ���� Angle sort�Ѵ�.]

	vector<point> convex_hull;			// The memory of convex hull's points.	[Stack ��� vector�� ����ؼ� convex hull�� �׸� �� �ִ� points�� ����.]
	convex_hull.push_back(pts[0]);	// The pivot. (pts[0] == pivot)	
	convex_hull.push_back(pts[1]);	// The first point except pivot. [Pivot�� P1, P2�� �������� P[N]���� �񱳸� �Ѵ�.]
	for (int i = 2; i < pts.size(); i++)		// Except P[0] and P[1].
	{
		while (convex_hull.size() >= 2 && CCW(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) <= 0)	// [Convex hull�� �׸��� ���ؼ�, ������ ����(����)���� ���̴��� �Ǵ��Ѵ�.]
			convex_hull.pop_back();		// Pop the present point which has uncorrect conditions. (P[i])		// [�ֱ� 3���� ���� ������ �ٱ����̶��, ���ο� ��(P[i])�� pop.]

		convex_hull.push_back(pts[i]);	// Push the next point. (P[i])
	}

	double max_dist = -1;					// The memory of maximum distance between points.
	for (int i = 0; i < convex_hull.size(); i++)		// [Convex hull�� �̷�� ������ ���տ��� �� �� ������ �ִ� �Ÿ��� ���� ��.]	-> ���� O(n^2 logn)
		for(int j=i+1; j<convex_hull.size(); j++)	// [�̸� �����ϴ� ���� rotating calipers �̷�.] -> �̿��ϸ� O(nlogn) ���� ���� ���� �� �ִ�.
			max_dist = max(Distance(convex_hull[i], convex_hull[j]), max_dist);		// Compare two points inside convex hull.

	printf("%.6f \n", max_dist);			// Output of maximum distance.
}