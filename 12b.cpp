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
#define lol unsigned long long

using namespace std;

FILE *fin = fopen("12.in", "r");
string c[50];
map<string, int> mapp;
vector<int> v[50];
int visited[20];

struct stElem
{
    int node, turn;
};

int main()
{
    char s[1000];
    while (fgets(s, 1000, fin) != NULL)
    {
        strtok(s, "\r \n");
        char *ptr = strtok(s, "-");
        if (mapp.find(ptr) == mapp.end())
            mapp.insert(make_pair(ptr, mapp.size()));
        int first = mapp[ptr];
        c[first] = ptr;
        ptr = strtok(NULL, "-");
        if (mapp.find(ptr) == mapp.end())
            mapp.insert(make_pair(ptr, mapp.size()));
        int second = mapp[ptr];
        c[second] = ptr;
        v[first].push_back(second);
        v[second].push_back(first);
    }
    stack<stElem> st;
    int beginn = mapp["start"];
    int endd = mapp["end"];
    st.push({beginn, 0});
    visited[beginn] = 1;
    int countt = 0;
    int possible = 2;
    while (!st.empty())
    {
        stElem tp = st.top();
     //   cout << c[tp.node] << " " << visited[tp.node] << "\n";
        if (tp.node == endd)
        {
            countt++;
            st.pop();
            visited[tp.node]--;
            continue;
        }
        bool found = false;
        for (int j = tp.turn; j < v[tp.node].size(); j++)
        {
            st.pop();
            st.push({tp.node, j + 1});
            int elem = v[tp.node][j];
            if (visited[elem] < 1 ||
            (visited[elem] < possible && elem != beginn && elem != endd) ||
            (c[elem][0] >= 'A' && c[elem][0] <= 'Z'))
            {
                visited[elem]++;
                if (c[elem][0] >= 'a' && c[elem][0] <= 'z' && visited[elem] == 2)
                    possible = 1;
                st.push({elem, 0});
                found = true;
                break;
            }
        }
        if (!found)
        {
            st.pop();
            visited[tp.node]--;
            if (visited[tp.node] == 1 && c[tp.node][0] >= 'a' && c[tp.node][0] <= 'z')
                possible = 2;
        }
    }
    printf("%d\n", countt);
}