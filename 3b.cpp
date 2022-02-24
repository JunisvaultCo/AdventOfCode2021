#include <iostream>
#include <set>
#include <string.h>
#define lol long long

using namespace std;

FILE *fin = fopen("3.in", "r");
int has0[20];
int v[2005];
multiset<int> s;
int maxN;

lol toNumber(char c[20])
{
    lol num = 0;
    int numTotal = 0;
    for (int i = 0; c[i] != '\0' && c[i] != '\n' && c[i] != '\r'; i++, numTotal++);
    for (int i = 0; c[i] != '\0' && c[i] != '\n' && c[i] != '\r'; i++)
        if (c[i] == '1')
            num += 1 << (numTotal - i - 1);
    maxN = numTotal;
    return num;
}

int main()
{
    char ss[20];
    int num = 0;
    while (fgets(ss, 20, fin) != 0)
    {
        v[num] = toNumber(ss);
        num++;
    }
    for (int i = 0; i < num; i++)
        s.insert(v[i]);
    for (int i = maxN - 1; i >= 0; i--)
    {
        int has0 = 0;
        for (auto j: s)
            has0 += (j & (1 << i)) == 0;
        int required = 1 << i;
        if (has0 > s.size() - has0)
            required = 0;
        for (set<int>::iterator it = s.begin(); it != s.end();)
        {
            if (((*it) & (1 << i)) != required)
            {
                auto aux = it;
                aux++;
                s.erase(it);
                it = aux;
            }
            else
                it++;
        }
    }
    lol first = *s.begin();
    s.clear();
    for (int i = 0; i < num; i++)
        s.insert(v[i]);
    for (int i = maxN - 1; i >= 0; i--)
    {
        int has0 = 0;
        for (auto j: s)
            has0 += (j & (1 << i)) == 0;
        int required = 1 << i;
        if (has0 <= s.size() - has0)
            required = 0;
        for (set<int>::iterator it = s.begin(); it != s.end();)
        {
            if (((*it) & (1 << i)) != required)
            {
                auto aux = it;
                aux++;
                s.erase(it);
                it = aux;
            }
            else
                it++;
        }
        if (s.size() == 1)
            break;
    }
    lol second = *s.begin();
    printf("%lld\n", first * second);
}