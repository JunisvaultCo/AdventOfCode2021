#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#define lol long long

using namespace std;

FILE *fin = fopen("10.in", "r");

char pos[10] = ")]}>";
char match[10] = "([{<";
int scoring[10] = {3, 57, 1197, 25137};


int main()
{
    char s[1000][1000];
    int num = 0;
    stack<char> st;
    int countt = 0;
    while (fgets(s[num], 1000, fin) != NULL)
    {
        strtok(s[num], "\r \n");
        for (int i = 0; s[num][i] != '\0'; i++)
        {
            if (find(match, match + 4, s[num][i]) != match + 4)
                st.push(s[num][i]);
            else
            {
                int index = find(pos, pos + 4, s[num][i]) - pos;
                if (st.empty())
                {
                    countt += scoring[index];
                    break;
                }
                else if (st.top() != match[index])
                {
                    countt += scoring[index];
                    break;
                }
                else
                    st.pop();
            }
        }
        num++;
    }
    printf("%d\n", countt);
}