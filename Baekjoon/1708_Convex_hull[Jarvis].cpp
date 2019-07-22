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
{														// [�� ���� �Ÿ��� ���Ѵ�.]
	return pow(A.x - B.x, 2) + pow(A.y - B.y, 2);		// Return the distance.
}

long long Cross_product(point A, point B, point C)		// Figure out the angle is counter clock wise or not.
{																			// [CCW�� CW�� �Ǵ��Ѵ�.]	
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
			idx_pivot = i;						// [y��ǥ �� ���� ���� ���� pivot�� �ȴ�. y��ǥ�� ���� ��쿡�� x��ǥ�� �Բ� ���ؼ� pivot�� �����Ѵ�.]

	pivot = pts[idx_pivot];					// Set pivot point.
	swap(pts[0], pts[idx_pivot]);		// Let pivot point be first one as P[0]. [pivot�� P[0]�� ��ġ��Ű�� ���� Swap.]

	// [���� ������ Same as Graham Scan algorithm.] [y,x ��ǥ �� ���� �Ʒ��� ���� pivot �����ϰ� P[0]���� ���ñ���.]

	vector<point> convex_hull;				// The memory of convex hull's points.	[Stack ��� vector�� ����ؼ� convex hull�� �׸� �� �ִ� points�� ����.]
	convex_hull.push_back(pts[0]);		// The pivot. (pts[0] == pivot)	
	convex_hull.push_back(pts[1]);

	while (true)
	{
		int idx = 0;
		for (int i = 0; i < pts.size(); i++)
		{
			if (Cross_product(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) > 0)	// [���� ���� ���� ū ���� ����.]
			{	// convex_hull.size()-2 = pivot.		convex_hull.back() = random value or previous big cross product coordinate.		pts[i] = compared coordinate.
				convex_hull.back() = pts[i];		// Update the coordinate. [back�� ����Ǿ� �ִ� ��ǥ����, �������� �� ū ��ǥ�� ã��.] 
				idx = i;									// Remember the index of that coordinate. [��ǥ�� index ����.]
			}

			else if (Cross_product(convex_hull[convex_hull.size() - 2], convex_hull.back(), pts[i]) == 0)	// [���ϼ��� �ִ� ���.]
			{
				if (Distance(convex_hull[convex_hull.size() - 2], convex_hull.back()) < Distance(convex_hull[convex_hull.size() - 2], pts[i]))	// [�� �ָ� �ִ� ��ǥ�� ����.]
				{												// �����ϰ� �־���� ���̶�, ���� �ּ� �����̶� ����
					convex_hull.back() = pts[i];		// Update the coordinate. [back�� ����Ǿ� �ִ� ��ǥ����, �������� �� ū ��ǥ�� ã��.] 
					idx = i;									// Remember the index of that coordinate. [��ǥ�� index ����.]
				}
			}
		}
		if (idx != 0)		// [idx==0 �� ����, start coordinate�� �ٽ� ã�� ���̹Ƿ�, convex hull�� �ϼ��� �ǹ�.]
			swap(pts[idx], pts.back());			// �������߿��� �ּ� �������� ���õ� ���� �ǵڷ� �̵�.
		pts.pop_back();								// �ּ� ������ ���� ���Ǿ����� ��.

		if (Same(convex_hull[0], convex_hull.back()))	// [Convex hull�� �ϼ��� Ȯ��.]
		{
			convex_hull.pop_back();								// [�ߺ��Ǵ� ��ǥ�̹Ƿ� ����.]
			break;
		}

		convex_hull.push_back(pts.back());	// �ǵڿ� �ִ� ������ �����ϰ� Ǫ��.
	}

	cout << convex_hull.size() << endl;
}