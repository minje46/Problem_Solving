#include<iostream>

using namespace std;

long long Decreased_number(long long n)
{
	long long cnt = 0, num = 211;
	
	while (cnt != n)										// cnt == n means it is success to search the n'th index of decreased number.
	{														// (cnt==n�̶�� ����, n��°�� �����ϴ� ���� ã�Ҵٴ� ��.) 	
		long long prev = -1, now = num;			// prev = saving previous digit.		now = saving present digit.
		int jump = 1;										// jump = jump not decreased number.
		bool check = true;								// check = Judge wheter the number is decreased or not.
		while(now)										// while(now) == true means now has more digit's number. 
		{													// (now==true��� ����, ���� �� �ִ� �ڸ����� �� �ִٴ� ���� �ǹ��Ѵ�.)
			if (now % 10 <= prev)						// now%10 should be larger than prev for being decreased number.
			{												// (number�� ���ڸ� ���� ������ ����ϱ� ������, now%10�� prev���� Ŀ�� �����ϴ� ���� �ȴ�.)
				check = false;							// check = false means this number is not decreased number. (false��� ���� �����ϴ� ���� �ƴ϶�� ��.)
				break;
			}
			jump *= 10;									// jump is only used to jump that there is no more decreased number in these digit. (jump�� ���� �ش� �ڸ� ���� �� �̻� ���� �����ϴ� ���� ������ ���Ѵ�.)
			prev = now % 10;							// prev is updated.
			now /= 10;									// now is updated to front digit. (���� �ڸ����� ����.)
		}

		if (check)											// check = true means this number is decreased number.
			cnt++;

		else												// In not decreased number, jump unnecessary operation.
		{													// jump�� ���� �ش� �ڸ� ���� �� �̻� ���� �����ϴ� ���� ������ ���Ѵ�.
			num += jump;								// num += jump �� ���� num�� ���� �ڸ� ���� update ���ش�.
			num = (num / jump) * jump;				// �ܼ� + �������� update ���ָ�, �ڸ� �� �ʹ��� �����ϴ� ���� skip�ϰ� �ǹǷ� num�� ������.
			continue;										// continue�� ���� �ش� number���� �ٽ� decreased number�� Ȯ��.
		}
		num++;
	}
	return num-1;
}

int main(void)
{
	long long N;
	cin >> N;
		
	if (N == 0)						// The "0" is counted as 0th decreased number. (0�� 0��° �����ϴ� ���ڷ� ���ֵȴ�.)
		cout << "0" << endl;		
	else if (N > 1022)				// There are only 1022's decreased number under maximum size of long long. (�����ϴ� ���� 1022�� �ۿ� ����.)
		cout << "-1" << endl;		// 1022nd decreased number is "98765432210". (long long size�� �ʰ����� �ʴ� ��쿡)
	else
		cout << Decreased_number(N) << endl;
}

