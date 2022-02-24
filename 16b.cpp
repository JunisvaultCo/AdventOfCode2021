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

FILE *fin = fopen("16.in", "r");
char indexing[] = "0123456789ABCDEF";

lol calculatePacket(int type, bool set, lol a1, lol a2)
{
    if (!set)
    {
        if (type == 0)
            a1 = 0;
        else if (type == 1)
            a1 = 1;
        else if (type == 2)
            a1 = LLONG_MAX;
        else if (type == 3)
            a1 = LLONG_MIN;
    }
    if (type == 0)
        return a1 + a2;
    if (type == 1)
        return a1 * (lol)a2;
    if (type == 2)
        return min(a1, a2);
    if (type == 3)
        return max(a1, a2);
    if (type == 5 && set)
        return a1 > a2;
    if (type == 5 && !set)
        return a2;
    if (type == 6 && set)
        return a1 < a2;
    if (type == 6 && !set)
        return a2;
    if (type == 7 && !set)
        return a2;
    return a1 == a2;
}

lol readPacket(vector<int> v, int &pos)
{
    lol result = 0;
    int version = 0;
    for (int j = 0; j < 3; j++)
        version = version * 2 + v[pos + j];
    pos += 3;
    int type = 0;
    for (int j = 0; j < 3; j++)
        type = type * 2 + v[pos + j];
    pos += 3;
    if (type == 4)
    {
        do
        {
            int continues = v[pos];
            pos++;
            for (int j = 0; j < 4; j++)
            {
                result = result * 2 + v[pos];
                pos++;
            }
            if (!continues)
                break;
        } while (true);
    }
    else
    {
        int lengthType = v[pos];
        pos++;
        int length = 0;
        if (lengthType == 0)
        {
            for (int j = 0; j < 15; j++)
            {
                length = length * 2 + v[pos];
                pos++;
            }
            bool set = false;
            int start = pos;
            while (pos != start + length)
            {
                result = calculatePacket(type, set, result, readPacket(v, pos));
                set = true;
            }
        }
        else
        {
            for (int j = 0; j < 11; j++)
            {
                length = length * 2 + v[pos];
                pos++;
            }
            bool set = false;
            for (int j = 0; j < length; j++)
            {
                result = calculatePacket(type, set, result, readPacket(v, pos));
                set = true;
            }
        }
    }
    return result;
}

int main()
{
    char s[2000];
    vector<int> v; // decoded bits
    fgets(s, 2000, fin);
    for (int i = 0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F'); i++)
    {
        int value = strchr(indexing, s[i]) - indexing;
        int pow2 = 8;
        while (pow2 != 0)
        {
            v.push_back((pow2 & value) != 0);
            pow2 >>= 1;
        }
    }
    int pos = 0;
    printf("%lld\n", readPacket(v, pos));
}