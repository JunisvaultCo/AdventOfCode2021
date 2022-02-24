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
    int steps[300][300];
    bool taken[300];
    fgets(s, 2000, fin);
    int startX, endX, startY, endY;
    sscanf(s, "target area: x=%d..%d, y=%d..%d", &startX, &endX, &startY, &endY);
    lol maxStep = 0;
    // y and x are somewhat independent
    // we only care about the number of steps
    for (int i = 0; i < 300; i++)
        for (int j = 0; j < 300; j++)
            steps[i][j] = 0;
    for (int posX = 0; posX < 300; posX++)
    {
        int currentX = 0;
        int step = 0;
        int velocityX = posX;
        while (currentX < startX)
        {
            currentX += velocityX;
            step++;
            if (velocityX > 0)
                velocityX--;
            else
                break;
        }
        while (currentX >= startX && currentX <= endX)
        {
            steps[posX][step]++;
            step++;
            currentX += velocityX;
            if (velocityX > 0)
                velocityX--;
            if (step >= 300)
                break;
        }
    }
    lol total = 0;
    for (int posY = -1000; posY < 1000; posY++)
    {
        lol currentY = 0;
        lol velocityY = posY;
        lol step = 0;
        while (currentY > endY)
        {
            currentY += velocityY;
            velocityY--;
            step++;
        }
        for (int i = 0; i < 300; i++)
            taken[i] = false;
        while (currentY <= endY && currentY >= startY)
        {
            for (int j = 0; j < 300; j++)
            {
                if (!taken[j] && steps[j][step])
                {
                    total += steps[j][step];
                    taken[j] = true;
                }
            }
            currentY += velocityY;
            velocityY--;
            step++;
            maxStep = max(maxStep, step);
        }
    }
    printf("%lld\n", total);
}