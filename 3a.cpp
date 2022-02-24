#include <iostream>
#include <string.h>
#define lol long long

using namespace std;

FILE *fin = fopen("3.in", "r");
int has0[20];

int main()
{
    char s[20];
    int maxN = 0;
    int num = 0;
    while (fgets(s, 20, fin) != 0)
    {
        num++;
        for (int i = 0; s[i] != '\n' && s[i] != '\0'; i++)
        {
            has0[i] += s[i] == '0';
            maxN = max(maxN, i + 1);
        }
    }
    lol first = 0;
    lol second = 0;
    for (int i = 0; i < maxN; i++)
    {
        if (has0[i] < num - has0[i])
            first += 1 << (maxN - i - 1);
        else
            second += 1 << (maxN - i - 1);
    }
    printf("%lld\n", second * first);
}