#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#define lol unsigned long long

using namespace std;

FILE *fin = fopen("11.in", "r");

struct point
{
    int x, y;
};

void print(int matrix[1000][1000], int num, int m)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    char s[1000][1000];
    int matrix[1000][1000];
    int num = 0;
    int countt = 0;
    while (fgets(s[num], 1000, fin) != NULL)
    {
        strtok(s[num], "\r \n");
        for (int i = 0; s[num][i] != '\0'; i++)
            matrix[num][i] = s[num][i] - '0';
        num++;
    }
    int m = strlen(s[num - 1]);
    int dx[8] = {-1, 0, 1, 0, 1,-1, 1,-1};
    int dy[8] = { 0, 1, 0,-1, 1, 1,-1,-1};
    for (int step = 0; step < 100; step++)
    {
        bool hasFlashed[num][m];
        for (int i = 0; i < num; i++)
            for (int j = 0; j < m; j++)
                hasFlashed[i][j] = false;
        for (int i = 0; i < num; i++)

        {
            for (int j = 0; j < m; j++)
            {
                if (hasFlashed[i][j])
                    continue;
                matrix[i][j]++;
                if (matrix[i][j] <= 9)
                    continue;
                hasFlashed[i][j] = true;
                matrix[i][j] = 0;
                countt++;
                queue<point> q;
                q.push({j, i});
                while (!q.empty())
                {
                    point tp = q.front();
                    q.pop();
                    for (int k = 0; k < 8; k++)
                    {
                        int newX = tp.x + dx[k];
                        int newY = tp.y + dy[k];
                        if (newX < 0 || newY < 0 || newY >= num || newX >= m)
                            continue;
                        if (hasFlashed[newY][newX])
                            continue;
                        matrix[newY][newX]++;
                        if (matrix[newY][newX] <= 9)
                            continue;
                        matrix[newY][newX] = 0;
                        q.push({newX, newY});
                        hasFlashed[newY][newX] = true;
                        countt++;
                    }
                }
            }
        }
        int countTurn = 0;
        for (int i = 0; i < num; i++)
            for (int j = 0; j < m; j++)
                countTurn += hasFlashed[i][j];
    }
    printf("%d\n", countt);
}