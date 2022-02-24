#include <iostream>
#include <set>
#include <vector>
#include <string.h>
#include <algorithm>
#define lol long long

using namespace std;

FILE *fin = fopen("8.in", "r");
bool has[10][10];
int len[10];

vector<int> getWithLength(int length)
{
    vector<int> v = vector<int>();
    for (int i = 0; i < 10; i++)
        if (len[i] == length)
            v.push_back(i);
    return v;
}

vector<int> getWithCharacter(char c, vector<int> variations)
{
    vector<int> v = vector<int>();
    for (auto j: variations)
        if (has[j][c - 'a'])
            v.push_back(j);
    return v;
}

int oneDisplay(char *s)
{
    int countt = 0;
    int pos[10] = {0};
    char *ptr = strtok(s, "|");
    char *otherPtr = strtok(NULL, "|");
    char *ptr2 = strtok(ptr, " ");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 'a'; j <= 'g'; j++)
            has[i][j - 'a'] = 0;
        len[i] = 0;
    }
    int num = 0;
    // let's read in
    while (ptr2 != NULL)
    {
        for (int i = 0; ptr2[i] != '\0'; i++)
            has[num][ptr2[i] - 'a'] = true;
        len[num] = strlen(ptr2);
        num++;
        ptr2 = strtok(NULL, " ");
    }
    // first, let's get f by doing 7 - 1
    // and e with 8 - 4
    pos[1] = getWithLength(2)[0];
    pos[4] = getWithLength(4)[0];
    pos[7] = getWithLength(3)[0];
    pos[8] = getWithLength(7)[0];
    char ourA = 0;
    for (int i = 'a'; i <= 'g'; i++)
        if (has[pos[7]][i - 'a'] && !has[pos[1]][i - 'a'])
            ourA = i;
    // 0, 6 and 9 all have a,b, f, g. 4 has only
    // b, f from those. 1 has only f from those.
    // We can get f here(with 1), b (with 4),
    vector<int> with6 = getWithLength(6);
    char ourB = 0;
    char ourF = 0;
    for (int i = 'a'; i <= 'g'; i++)
    {
        int countt = 0;
        for (auto j: with6)
            countt += has[j][i - 'a'];
        if (countt == 3 && has[pos[1]][i - 'a'] && has[pos[4]][i - 'a'])
            ourF = i;
        else if (countt == 3 && has[pos[4]][i - 'a'])
            ourB = i;
    }
    //4 has d, besides b and what 1 has.
    char ourD = 0;
    for (int i = 'a'; i <= 'g'; i++)
        if (has[pos[4]][i - 'a'] && !has[pos[1]][i -'a'] && i != ourB)
            ourD = i;
    //we can now tell c from 1 (we know f)
    char ourC = 0;
    for (int i = 'a'; i <= 'g'; i++)
        if (has[pos[1]][i - 'a'] && i != ourF)
            ourC = i;
    // e is only unknown along with g in 2, and 2 only that doesn't have f among length 5s.
    // we can get rid of g since g is in any of the other poses
    vector<int> with5 = getWithLength(5);
    vector<int> length5WithF = getWithCharacter(ourF, with5);
    pos[3] = getWithCharacter(ourC, length5WithF)[0];
    for (auto j : with5)
        if (!has[j][ourF - 'a'])
            pos[2] = j;
    char ourE = 0;
    for (int i = 'a'; i <= 'g'; i++)
        if (has[pos[2]][i - 'a'] && i != ourA && i != ourB && i != ourC && i != ourD
        && i != ourF && !has[pos[3]][i - 'a'])
            ourE = i;
    //fun fact: g is unnecessary so I won't bother
    vector<int> length6WithC = getWithCharacter(ourC, with6);
    pos[0] = getWithCharacter(ourE, length6WithC)[0];
    pos[5] = getWithCharacter(ourB, length5WithF)[0];
    pos[6] = getWithCharacter(ourD, getWithCharacter(ourE, with6))[0];
    pos[9] = getWithCharacter(ourD, length6WithC)[0];
    int inversePos[10] = {0};
    for (int i = 0; i < 10; i++)
        inversePos[pos[i]] = i;
    //finally, calculate...
    ptr = otherPtr;
    ptr = strtok(otherPtr, " \r\n");
    while (ptr != NULL)
    {
        bool currentHas[10] = {0};
        for (int j = 0; ptr[j] != '\0'; j++)
            currentHas[ptr[j] - 'a'] = true;
        for (int i = 0; i < 10; i++)
        {
            bool ok = true;
            for (int j = 'a'; j <= 'g'; j++)
                if (has[i][j - 'a'] != currentHas[j - 'a'])
                    ok = false;
            if (ok)
            {
                countt = countt * 10;
                countt += inversePos[i];
            }
        }
        ptr = strtok(NULL, " \r\n");
    }
    return countt;
}

int main()
{
    char s[4000];
    int countt = 0;
    while (fgets(s, 4000, fin) != NULL)
        countt += oneDisplay(s);
    printf("%d\n", countt);
}