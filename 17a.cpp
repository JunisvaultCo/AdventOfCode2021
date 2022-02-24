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
#define lol long long

using namespace std;

FILE *fin = fopen("17.in", "r");

int main()
{
    char s[2000];
    fgets(s, 2000, fin);
    int startX, endX, startY, endY;
    sscanf(s, "target area: x=%d..%d, y=%d..%d", &startX, &endX, &startY, &endY);
    lol maxx = 0;
    for (int posY = 0; posY < 3000; posY++)
    {
        lol currentY = 0;
        lol maxCurrent = 0;
        lol velocityY = posY;
        while (currentY > endY)
        {
            currentY += velocityY;
            velocityY--;
            maxCurrent = max(maxCurrent, currentY);
        }
        if (currentY <= endY && currentY >= startY)
        maxx = max(maxx, maxCurrent);
    }
    printf("%lld\n", maxx);
}