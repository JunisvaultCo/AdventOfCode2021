#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <stack>
#include <limits.h>
#define lol unsigned long long

using namespace std;

FILE *fin = fopen("14.in", "r");
int pairs[2][256][256];
char rules[256][256];

int main()
{
    char s[1000];
    fgets(s, 1000, fin);
    char first = s[0];
    char last = s[1];
    for (int i = 0; s[i + 1] >= 'A' && s[i + 1] <= 'Z'; i++)
    {
        pairs[0][s[i]][s[i + 1]]++;
        last = s[i + 1];
    }
    fgets(s, 1000, fin); //clear the empty line
    while (fgets(s, 1000, fin) != NULL)
    {
        strtok(s, "\r\n");
        char p1, p2, result;
        sscanf(s, "%c%c -> %c", &p1, &p2, &result);
        rules[p1][p2] = result;
    }
    for (int i = 0; i < 10; i++)
    {
        for (char a = 'A'; a <= 'Z'; a++)
            for (char b = 'A'; b <= 'Z'; b++)
                pairs[(i + 1) % 2][a][b] = 0;
        for (char a = 'A'; a <= 'Z'; a++)
            for (char b = 'A'; b <= 'Z'; b++)
            {
                char neww = rules[a][b];
                if (neww == 0)
                    continue;
                pairs[(i + 1) % 2][a][neww] += pairs[i % 2][a][b];
                pairs[(i + 1) % 2][neww][b] += pairs[i % 2][a][b];
            }
    }
    lol maxx = 0;
    lol minn = LLONG_MAX;
    for (char a = 'A'; a <= 'Z'; a++)
    {
        lol countt = 0;
        if (a == first)
            countt++;
        if (a == last)
            countt++;
        for (char b = 'A'; b <= 'Z'; b++)
        {
            countt += pairs[0][a][b];
            countt += pairs[0][b][a];
        }
        countt = countt / 2;
        if (countt == 0)
            continue;
        maxx = max(maxx, countt);
        minn = min(minn, countt);
    }
    printf("%lld\n", maxx - minn);
}