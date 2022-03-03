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
#include <assert.h>
#define lol long long

using namespace std;

FILE *fin = fopen("21.in", "r");

int current;

//pos1, pos2, score1, score2, whose turn
lol dp[11][11][35][35][2];

int main()
{
    char s[2000];
    int p1, p2;
    fscanf(fin, "Player 1 starting position: %d\n", &p1);
    fscanf(fin, "Player 2 starting position: %d", &p2);
    dp[p1][p2][0][0][0] = 1;
    int turn = 0;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            for (int p1 = 1; p1 <= 10; p1++)
            {
                for (int p2 = 1; p2 <= 10; p2++)
                {
                    for (int turn = 0; turn < 2; turn++)
                    {
                        for (int f1 = 1; f1 <= 3; f1++)
                        {
                            for (int f2 = 1; f2 <= 3; f2++)
                            {
                                for (int f3 = 1; f3 <= 3; f3++)
                                {
                                    if (turn == 0)
                                    {
                                        int actualP1 = p1 + f1 + f2 + f3;
                                        actualP1 = (actualP1 + 9) % 10 + 1;
                                        dp[actualP1][p2][i + actualP1][j][1] += dp[p1][p2][i][j][0];
                                    }
                                    else
                                    {
                                        int actualP2 = p2 + f1 + f2 + f3;
                                        actualP2 = (actualP2 + 9) % 10 + 1;
                                        dp[p1][actualP2][i][j + actualP2][0] += dp[p1][p2][i][j][1];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    lol sum1 = 0;
    lol sum2 = 0;
    for (int i = 0; i <= 30; i++)
        for (int j = 0; j <= 30; j++)
            for (int p1 = 1; p1 <= 10; p1++)
                for (int p2 = 1; p2 <= 10; p2++)
                    for (int turn = 0; turn < 2; turn++)
                    {
                        if (i >= 21)
                            sum1 += dp[p1][p2][i][j][turn];
                        if (j >= 21)
                            sum2 += dp[p1][p2][i][j][turn];
                    }
    printf("%lld\n", max(sum1, sum2));
    fclose(fin);
}