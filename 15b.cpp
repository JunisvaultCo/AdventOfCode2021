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

FILE *fin = fopen("15.in", "r");
int matrix[605][605];
int dp[605][605];

struct point
{
    int x, y;
};

queue<point> q;

int main()
{
    char s[1000];
    int num = 0;
    int len = 0;
    while (fgets(s, 1000, fin) != NULL)
    {
        strtok(s, "\r\n");
        for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        {
            matrix[num][i] = s[i] - '0';
            len = i + 1;
        }
        num++;
    }
    for (int i = 0; i < num * 5; i++)
    {
        for (int j = 0; j < len * 5; j++)
        {
            if (i < num && j < len)
                continue;
            if (i < num)
                matrix[i][j] = matrix[i][j - len] % 9 + 1;
            else
                matrix[i][j] = matrix[i - num][j] % 9 + 1;
        }
    }
    num = num * 5;
    len = len * 5;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < len; j++)
            dp[i][j] = INT_MAX;
    dp[0][0] = 0;
    q.push({0, 0});
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = { 0,-1, 0, 1};
    while (!q.empty())
    {
        point tp = q.front();
        q.pop();
       // printf("%d %d\n", tp.x, tp.y);
        for (int k = 0; k < 4; k++)
        {
            int newX = tp.x + dx[k];
            int newY = tp.y + dy[k];
            if (newX < 0 || newY < 0 || newX >= len || newY >= num)
                continue;
            if (dp[newY][newX] <= dp[tp.y][tp.x] + matrix[newY][newX])
                continue;
            dp[newY][newX] = dp[tp.y][tp.x] + matrix[newY][newX];
            q.push({newX, newY});
        }
    }
    printf("%d\n", dp[num - 1][len - 1]);
}