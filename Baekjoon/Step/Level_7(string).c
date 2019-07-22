#pragma warning(disable:4996)
#include <stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

// 7 - 1
/*
int main()
{
char input;

scanf("%c", &input);
printf("%d \n", input);
}
*/

// 7 - 2
/*
int main()
{
int alp[26];
char word[100];

for (int i = 0; i <26; i++)
alp[i] = -1;

scanf("%s", &word);

for (int i = 0; i < strlen(word); i++)
{
for (int j = 0; j < 26; j++)
{
if (alp[j] > -1)
continue;

if (word[i] == (j + 97))
alp[j] = i;
}
}
for (int i = 0; i < 26; i++)
printf("%d ", alp[i]);
printf("\n");
}
*/

// 7 - 3
/*
int main()
{
int T, R, count = 0;
char word[20], new[170];

scanf("%d", &T);
for (int i = 0; i < T; i++)
{
scanf("%d", &R);
scanf("%s", &word);
for (int l = 0; l < strlen(word); l++)
for (int j = 0; j < R; j++)
new[count++] = word[l];

for (int k = 0; k < count; k++)
printf("%c", new[k]);

printf("\n");
count = 0;
}
}
*/

// 7 - 4
/*
int main()
{
int alp[26] = { 0, }, dup = 0, max, idx = 0, len;
char word[1000000];

scanf("%s", word);
len = strlen(word);					// <- 이를 줄이기 위해서 For 문 밖에서 따로 변수에 입력받는다.
for (int i = 0; i < len; i++)		// For 문 안에서 strlen() 을 이용시 O(N^2)의 시간이 소요된다.
{
for (int j = 0; j < 26; j++)
{
if ((word[i] == (j + 97)) || (word[i] == (j + 65)))
alp[j]++;
}
}

for (int i = 0; i < 26; i++)
{
if (i == 0)
max = alp[i];

if (max < alp[i])
{
max = alp[i];
idx = i;
}
}

for (int j = 0; j < 26; j++)
if (alp[j] == max)
dup++;

if (dup != 1)
printf("? \n");
else
printf("%c \n", (idx + 65));
}
*/

// 7 - 5
/*
int main()
{
int N, alp[26] = { 0, }, count = 0, len, idx, check = 1;
char word[100], prev = NULL;

scanf("%d", &N);
for (int i = 0; i < N; i++)
{
scanf("%s", word);
len = strlen(word);
for (int k = 0; k < len; k++)
{
if (prev == word[k])
alp[idx]--;

for (int j = 0; j < 26; j++)
{
if (word[k] == (j + 97))
{
alp[j]++;
prev = word[k];
idx = j;
}
}
}
prev = NULL;
for (int i = 0; i < 26; i++)
{
if (alp[i] > 1)
check = 0;
}
if (check == 1)
count++;
else
check = 1;

for (int i = 0; i < 26; i++)
alp[i] = 0;
}
printf("%d \n", count);
}
*/

// 7 - 7
/*
int Compare(int, int);
int main()
{
int a, b;

scanf("%d %d", &a, &b);
printf("%d \n",Compare(a, b));
}

int Compare(int a, int b)
{
char num1[10], num2[10], cha1[10], cha2[10];
int j = 2, big;

sprintf(num1, "%d", a);
sprintf(num2, "%d", b);

for (int i = 0; i < 3; i++)
{
cha1[i] = num1[j];
cha2[i] = num2[j];
j--;
}
if (atoi(cha1) > atoi(cha2))
return atoi(cha1);
else
return atoi(cha2);
}
*/

// 7 - 8
/*
int Time(char*);
int main()
{
char word[20];

fgets(word, sizeof(word), stdin);
printf("%d \n",Time(&word));
}

int Time(char word[20])
{
int sec = 0, num[10] = { 0, };

for (int i = 0; i < strlen(word)-1; i++)
{
if (word[i] == '0')
sec += 2;
if ((word[i] >= 65) && (word[i] <= 67))
sec += 3;
else if ((word[i] >= 68) && (word[i] <= 70))
sec += 4;
else if ((word[i] >= 71) && (word[i] <= 73))
sec += 5;
else if ((word[i] >= 74) && (word[i] <= 76))
sec += 6;
else if ((word[i] >= 77) && (word[i] <= 79))
sec += 7;
else if ((word[i] >= 80) && (word[i] <= 83))
sec += 8;
else if ((word[i] >= 84) && (word[i] <= 86))
sec += 9;
else if ((word[i] >= 87) && (word[i] <= 90))
sec += 10;
else
sec += 11;
}
return sec;
}
*/

// 7 - 9
/*
int Count(char *);
int main()
{
	char word[100];

	fgets(word, sizeof(word), stdin);
	printf("%d \n", Count(&word));
}

int Count(char word[100])
{
	int count = 0, len = strlen(word), i = 0;

	while (1)
	{
		if (word[i] == '\n')
			break;
		else
		{
			if (word[i] == 'c' && (word[i + 1] == '=' || word[i + 1] == '-'))
				count++, i += 2;
			else if (word[i] == 'd')
			{
				if (word[i + 1] == 'z'&&word[i + 2] == '=')
					count++, i += 3;
				else if (word[i + 1] == '-')
					count++, i += 2;
				else
					count++, i++;
			}
			else if (word[i] == 'l'&&word[i + 1] == 'j')
				count++, i += 2;
			else if (word[i] == 'n'&&word[i + 1] == 'j')
				count++, i += 2;
			else if (word[i] == 's'&&word[i + 1] == '=')
				count++, i += 2;
			else if (word[i] == 'z'&&word[i + 1] == '=')
				count++, i += 2;
			else
				count++, i++;
		}
	}
	return count;
}
*/
