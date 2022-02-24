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

FILE *fin = fopen("16.in", "r");
char indexing[] = "0123456789ABCDEF";

struct packet
{
    int version = 0;
    int type = -1;
    int lengthType = 0;
    int length = 0;
    int value = 0;
    vector<packet> packets;
};

packet base;
int countt = 0;

packet readPacket(vector<int> v, int &pos)
{
    int version = 0;
    packet current;
    for (int j = 0; j < 3; j++)
        version = version * 2 + v[pos + j];
    pos += 3;
    int type = 0;
    for (int j = 0; j < 3; j++)
        type = type * 2 + v[pos + j];
    pos += 3;
    if (type == 4)
    {
        int value = 0;
        do
        {
            int continues = v[pos];
            pos++;
            for (int j = 0; j < 4; j++)
            {
                value = value * 2 + v[pos];
                pos++;
            }
            if (!continues)
                break;
        } while (true);
        current.value = value;
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
            current.length = length;
            int start = pos;
            while (pos != start + length)
                current.packets.push_back(readPacket(v, pos));
        }
        else
        {
            for (int j = 0; j < 11; j++)
            {
                length = length * 2 + v[pos];
                pos++;
            }
            current.length = length;
            for (int j = 0; j < length; j++)
                current.packets.push_back(readPacket(v, pos));
        }
        current.lengthType = lengthType;
    }
    countt += version;
    current.version = version;
    current.type = type;
    return current;
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
    base = readPacket(v, pos);
    printf("%d\n", countt);
}