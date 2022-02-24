#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#define lol long long

using namespace std;

FILE *fin = fopen("9.in", "r");

int main()
{
    char s[1000][1000];
    int num = 0;
    while (fgets(s[num], 1000, fin) != NULL)
    {
        strtok(s[num], "\r \n");
        num++;
    }
    int countt = 0;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = { 0,-1, 0, 1};
    for (int i = 0; i < num; i++)
        for (int j = 0; s[i][j] != '\0'; j++)
        {
            int ok = 1;
            for (int k = 0; k < 4; k++)
            {
                int newX = j + dx[k];
                int newY = i + dy[k];
                if (newY < 0 || newX < 0 || newY >= num || s[newY][newX] == '\0')
                    continue;
                if (s[newY][newX] <= s[i][j])
                    ok = 0;
            }
            countt += ok * (s[i][j] - '0' + 1);
        }
    printf("%d\n", countt);
}