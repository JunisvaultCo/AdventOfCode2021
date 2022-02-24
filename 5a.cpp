#include <iostream>
#include <set>
#include <string.h>
#define lol long long

using namespace std;

FILE *fin = fopen("5.in", "r");
int matrix[1005][1005];

int main()
{
    int x1, y1, x2, y2;
    char s[200];
    while (fgets(s, 200, fin) != 0)
    {
        sscanf(s, "%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2);
        if (x1 != x2 && y1 != y2)
            continue;
        
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        if (x1 != x2)
            for (int i = x1; i <= x2; i++)
                matrix[y1][i]++;
        else if (y1 != y2)
            for (int i = y1; i <= y2; i++)
                matrix[i][x1]++;
        else
            matrix[y1][x1]++;
    }
    int countt = 0;
    for (int i = 0; i < 1005; i++)
        for (int j = 0; j < 1005; j++)
            countt += matrix[i][j] >= 2;
    printf("%d\n", countt);
}