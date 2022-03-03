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

FILE *fin = fopen("20.in", "r");

int main()
{
    char s[2000];
    set<tuple<lol, lol> > actives[2];
    set<tuple<lol, lol> > inactives[2];
    set<tuple<lol, lol> > total[2];
    char key[2000];
    fgets(key, 2000, fin);
    fgets(s, 2000, fin);
    int num = 0;
    while (fgets(s, 2000, fin) != NULL)
    {
        for (int j = 0; s[j] == '#' || s[j] == '.'; j++)
        {
            if (s[j] == '#')
                actives[0].insert({num, j});
            else
                inactives[0].insert({num, j});
            for (int k = -1; k <= 1; k++)
                for (int o = -1; o <= 1; o++)
                    total[0].insert({num + k, j + o});
        }
        num++;
    }
    // we pray we never get a key with 1st position #
    // as well as 512nd position #
    bool alternating = key[0] == '#';
    for (int i = 0; i < 50; i++)
    {
        actives[(i + 1) % 2].clear();
        total[(i + 1) % 2].clear();
        for (auto j: total[i % 2])
        {
            int pos = 0;
            for (int k = -1; k <= 1; k++)
                for (int o = -1; o <= 1; o++)
                {
                    tuple<int, int> newPoint = {get<0>(j) + k, get<1>(j) + o};
                    pos <<= 1;
                    if (actives[i % 2].find(newPoint) != actives[i % 2].end() || (total[i % 2].find(newPoint) == total[i % 2].end() && alternating && i % 2 == 1))
                        pos += 1;
                    total[(i + 1) % 2].insert(newPoint);
                    if (total[i % 2].find(newPoint) == total[i % 2].end() && alternating && i % 2 == 0)
                        actives[(i + 1) % 2].insert(newPoint);
               }
            if (key[pos] == '#')
                actives[(i + 1) % 2].insert(j);
            else
                inactives[(i + 1) % 2].insert(j);
        }
    }
    printf("%d\n", actives[50 % 2].size());
    fclose(fin);
}