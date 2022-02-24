#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#define lol long long

using namespace std;

FILE *fin = fopen("7.in", "r");
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
    lol countt = 0;
    
    for (int i = 0; i < num; i++)
        countt += abs(crabs[i] - crabs[num / 2]);
    printf("%lld\n", countt);
}