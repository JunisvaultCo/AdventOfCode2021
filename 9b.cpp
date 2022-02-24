#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#define lol long long

using namespace std;

FILE *fin = fopen("9.in", "r");

struct point
{
    int x, y;
};

queue<point> q;

int main()
{
    char s[1000][1000];
    bool visited[1000][1000] = {0};
    int num = 0;
    while (fgets(s[num], 1000, fin) != NULL)
    {
        strtok(s[num], "\r \n");
        num++;
    }
    lol sum = 0;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = { 0,-1, 0, 1};
    vector<int> results = vector<int>();
    for (int i = 0; i < num; i++)
        for (int j = 0; s[i][j] != '\0'; j++)
        {
            if (visited[i][j] || s[i][j] == '9')
                continue;
            visited[i][j] = true;
            q.push({j, i});
            int all = 1;
            while (!q.empty())
            {
                point tp = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int newX = tp.x + dx[k];
                    int newY = tp.y + dy[k];
                    if (newY < 0 || newX < 0 || newY >= num || s[newY][newX] == '\0')
                        continue;
                    // this means it has flowed down
                    if (!visited[newY][newX] && s[newY][newX] != '9')// s[tp.y][tp.x])
                    {
                        q.push({newX, newY});
                        visited[newY][newX] = true;
                        all++;
                    }
                }
            }
            results.push_back(all);
        }
    sort(results.begin(), results.end(), greater<int>());
    sum = results[0];
    for (int i = 1; i < 3; i++)
        sum *= results[i]; 
    printf("%lld\n", sum);
}