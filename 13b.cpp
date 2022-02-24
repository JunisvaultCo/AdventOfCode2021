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
#define lol unsigned long long

using namespace std;

FILE *fin = fopen("13.in", "r");


int matrix[2000][2000];

int main()
{
    char s[1000];
    bool readDots = true;
    int lengthX = 0;
    int lengthY = 0;
    while (fgets(s, 1000, fin) != NULL)
    {
        strtok(s, "\r\n");
        if (strlen(s) <= 2)
        {
            readDots = false;
            continue;
        }
        if (readDots)
        {
            int first, second;
            sscanf(s, "%d,%d", &first, &second);
            lengthX = max(lengthX, first);
            lengthY = max(lengthY, second);
            matrix[first][second] = 1;
        }
        else
        {
            int y = -1;
            int x = -1;
            sscanf(s, "fold along x=%d", &x);
            sscanf(s, "fold along y=%d", &y);
            if (x != -1)
            {
                for (int i = 0; i < x; i++)
                    for (int j = 0; j <= lengthY; j++)
                        matrix[i][j] = matrix[i][j] | matrix[2 * x - i][j];
                lengthX -= lengthX - x + 1;
            }
            if (y != -1)
            {
                for (int i = 0; i <= lengthX; i++)
                    for (int j = 0; j < y; j++)
                        matrix[i][j] = matrix[i][j] | matrix[i][2 * y - j];
                lengthY -= lengthY - y + 1;
            }
        }
    }
    for (int i = 0; i <= lengthY; i++)
    {
        for (int j = 0; j <= lengthX; j++)
        {
            if (matrix[j][i])
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
}