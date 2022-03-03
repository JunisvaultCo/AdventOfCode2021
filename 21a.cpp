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

int rollDie()
{
    current++;
    return (current - 1) % 100 + 1;
}

int main()
{
    char s[2000];
    int p1, p2;
    fscanf(fin, "Player 1 starting position: %d\n", &p1);
    fscanf(fin, "Player 2 starting position: %d", &p2);
    int score1 = 0;
    int score2 = 0;
    int turn = 0;
    while (score1 < 1000 && score2 < 1000)
    {
        if (turn % 2 == 0)
        {
            for (int i = 0; i < 3; i++)
                p1 += rollDie();
            p1 = (p1 + 9) % 10 + 1;
            score1 += p1;
        }
        else
        {
            for (int i = 0; i < 3; i++)
                p2 += rollDie();
            p2 = (p2 + 9) % 10 + 1;
            score2 += p2;
        }
        turn++;
    }
    printf("%d %d %d\n", current, score1, score2);
    printf("%lld\n", ((lol)current) * min(score1, score2));
    fclose(fin);
}