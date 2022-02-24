#include <iostream>
#include <set>
#include <string.h>
#define lol long long

using namespace std;

FILE *fin = fopen("6.in", "r");
lol fishes[2][10];

int main()
{
    char s[800];
    fscanf(fin, "%s", s);
    char *ptr = strtok(s, ",");
    while (ptr != NULL)
    {
        fishes[0][atoi(ptr)]++;
        ptr = strtok(NULL, ",");
    }
    for (int day = 0; day < 80; day++)
    {
        for (int i = 0; i < 10; i++)
            fishes[(day + 1) % 2][i] = 0;
        for (int i = 0; i < 10; i++)
        {
            int prev = i - 1;
            if (prev < 0)
            {
                prev = 6;
                fishes[(day + 1) % 2][8] += fishes[day % 2][i];
            }
            fishes[(day + 1) % 2][prev] += fishes[day % 2][i]; 
        }
    }
    lol sum = 0;
    for (int i = 0; i < 10; i++)
        sum += fishes[0][i];
    printf("%lld\n", sum);
}