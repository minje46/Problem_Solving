#include<iostream>

using namespace std;

long long Decreased_number(long long n)
{
	long long cnt = 0, num = 211;
	
	while (cnt != n)										// cnt == n means it is success to search the n'th index of decreased number.
	{														// (cnt==n이라는 것은, n번째의 감소하는 수를 찾았다는 것.) 	
		long long prev = -1, now = num;			// prev = saving previous digit.		now = saving present digit.
		int jump = 1;										// jump = jump not decreased number.
		bool check = true;								// check = Judge wheter the number is decreased or not.
		while(now)										// while(now) == true means now has more digit's number. 
		{													// (now==true라는 것은, 나눌 수 있는 자릿수가 더 있다는 것을 의미한다.)
			if (now % 10 <= prev)						// now%10 should be larger than prev for being decreased number.
			{												// (number의 뒷자리 부터 앞으로 계산하기 때문에, now%10이 prev보다 커야 감소하는 수가 된다.)
				check = false;							// check = false means this number is not decreased number. (false라는 것은 감소하는 수가 아니라는 것.)
				break;
			}
			jump *= 10;									// jump is only used to jump that there is no more decreased number in these digit. (jump를 통해 해당 자리 수에 더 이상 없는 감소하는 수의 연산을 피한다.)
			prev = now % 10;							// prev is updated.
			now /= 10;									// now is updated to front digit. (앞의 자릿수로 변경.)
		}

		if (check)											// check = true means this number is decreased number.
			cnt++;

		else												// In not decreased number, jump unnecessary operation.
		{													// jump를 통해 해당 자릿 수에 더 이상 없는 감소하는 수의 연산을 피한다.
			num += jump;								// num += jump 를 통해 num을 다음 자릿 수로 update 해준다.
			num = (num / jump) * jump;				// 단순 + 연산으로 update 해주면, 자릿 수 초반의 감소하는 수를 skip하게 되므로 num을 재조정.
			continue;										// continue를 통해 해당 number부터 다시 decreased number를 확인.
		}
		num++;
	}
	return num-1;
}

int main(void)
{
	long long N;
	cin >> N;
		
	if (N == 0)						// The "0" is counted as 0th decreased number. (0은 0번째 감소하는 숫자로 간주된다.)
		cout << "0" << endl;		
	else if (N > 1022)				// There are only 1022's decreased number under maximum size of long long. (감소하는 수는 1022개 밖에 없다.)
		cout << "-1" << endl;		// 1022nd decreased number is "98765432210". (long long size를 초과하지 않는 경우에)
	else
		cout << Decreased_number(N) << endl;
}

