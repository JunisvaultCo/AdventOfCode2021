#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#define lol unsigned long long

using namespace std;

FILE *fin = fopen("10.in", "r");

char pos[10] = ")]}>";
char match[10] = "([{<";
int scoring[10] = {1, 2, 3, 4};
vector<lol> results;


int main()
{
    char s[1000][1000];
    int num = 0;
    stack<char> st;
    while (fgets(s[num], 1000, fin) != NULL)
    {
        strtok(s[num], "\r \n");
        bool ok = true;
        while (!st.empty())
            st.pop();
        for (int i = 0; s[num][i] != '\0'; i++)
        {
            if (find(match, match + 4, s[num][i]) != match + 4)
                st.push(s[num][i]);
            else
            {
                int index = find(pos, pos + 4, s[num][i]) - pos;
                if (st.empty())
                {
                    ok = false;
                    break;
                }
                else if (st.top() != match[index])
                {
                    ok = false;
                    break;
                }
                else
                    st.pop();
            }
        }
        if (ok)
        {
            lol total = 0;
            while (!st.empty())
            {
                total = total * 5;
                total += scoring[find(match, match + 4, st.top()) - match];
                st.pop();
            }
            results.push_back(total);
        }
        num++;
    }
    sort(results.begin(), results.end());
    printf("%lld\n", results[results.size() / 2]);
}