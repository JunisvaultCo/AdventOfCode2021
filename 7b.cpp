#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#define lol long long

using namespace std;

FILE *fin = fopen("7ex.in", "r");
int crabs[4000];

int main()
{
    char s[4000];
    fscanf(fin, "%s", s);
    char *ptr = strtok(s, ",");
    int num = 0;
    while (ptr != NULL)
    {
        crabs[num] = atoi(ptr);
        ptr = strtok(NULL, ",");
        num++;
    }
    sort(crabs, crabs + num);
    lol minn = -1;
    for (int i = crabs[0]; i <= crabs[num - 1]; i++)
    {
        lol countt = 0;
        for (int j = 0; j < num; j++)
        {
            lol normalSteps = abs(crabs[j] - i);
            countt += (normalSteps * (normalSteps + 1)) / 2;
        }
        if (countt < minn || minn == -1)
            minn = countt;
    }
    printf("%lld\n", minn);
}