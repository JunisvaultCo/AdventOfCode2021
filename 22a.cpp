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

FILE *fin = fopen("22.in", "r");

int main()
{
    char s[2000];
    set<tuple<int, int, int>> points;
    while (fgets(s, 2000, fin))
    {
        int x1, x2, y1, y2, z1, z2;
        char c = 'f';
        sscanf(s, "o%c x=%d..%d,y=%d..%d,z=%d..%d", &c, &x1, &x2, &y1, &y2, &z1, &z2);
        if (c == 'n')
        {
            for (int x = max(-50, x1); x <= min(50, x2); x++)
                for (int y = max(-50, y1); y <= min(50, y2); y++)
                    for (int z = max(-50, z1); z <= min(50, z2); z++)
                        points.insert({x, y, z});
        }
        else
        {
            sscanf(s, "off x=%d..%d,y=%d..%d,z=%d..%d", &x1, &x2, &y1, &y2, &z1, &z2);
            for (int x = max(-50, x1); x <= min(50, x2); x++)
                for (int y = max(-50, y1); y <= min(50, y2); y++)
                    for (int z = max(-50, z1); z <= min(50, z2); z++)
                        points.erase({x, y, z});
        }
    }
    printf("%d\n", points.size());
    fclose(fin);
}