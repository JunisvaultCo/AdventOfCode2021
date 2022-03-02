// I deeply apologise to anyone reading this code

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

FILE *fin = fopen("19.in", "r");

struct point
{
    int x, y, z;
    point operator+ (point p1)
    {
        point a = {x, y, z};
        a.x += p1.x;
        a.y += p1.y;
        a.z += p1.z;
        return a;
    }
    point operator-()
    {
        return {-x, -y, -z};
    }
    bool operator==(point p1)
    {
        return x == p1.x && y == p1.y && z == p1.z;
    }
    tuple<int, int, int> transformIntoTuple()
    {
        return {x, y, z};
    }
    void saveIntoArray(int a[3])
    {
        a[0] = x;
        a[1] = y;
        a[2] = z;
    }
};
point transformFromArray(int a[3])
{
    return {a[0], a[1], a[2]};
}

struct edge
{
    int scanner;
    int delta[3];
    int rot[3]; // like { 0, 1, 2};
    int sgn[3]; // like {-1,-1, 1};
};

int systems[][3] = {
    {0, 1, 2},
    {1, 2, 0},
    {2, 0, 1}
};
int transformD[][3] = {
    {0, 1, 2},
    {0, 1, 2},
    {1, 0, 2},
    {1, 0, 2}
};
int transformF[2][4][3] = {
    {
        { 1, 1, 1},
        {-1,-1, 1},
        { 1,-1, 1},
        {-1, 1, 1}
    },
    {
        { 1,-1,-1},
        {-1, 1,-1},
        { 1, 1,-1},
        {-1,-1,-1}
    }
};
int coords2Aux[3];
int coords2Aux2[3];

point getTransformation(point pointt, int k, int ori, int f, point dp)
{
    coords2Aux[0] = pointt.x;
    coords2Aux[1] = pointt.y;
    coords2Aux[2] = pointt.z;
    coords2Aux2[0] = coords2Aux[systems[k][transformD[f][0]]];
    coords2Aux2[1] = coords2Aux[systems[k][transformD[f][1]]];
    coords2Aux2[2] = coords2Aux[systems[k][transformD[f][2]]];
    point elem;
    elem.x = dp.x - coords2Aux2[0] * transformF[ori][f][0];
    elem.y = dp.y - coords2Aux2[1] * transformF[ori][f][1];
    elem.z = dp.z - coords2Aux2[2] * transformF[ori][f][2];
    return elem;
}

point getTransformationCO(int transform1[3], int transform2[3])
{
    point elem;
    elem.x = transform2[transform1[0]];
    elem.y = transform2[transform1[1]];
    elem.z = transform2[transform1[2]];
    return elem;
}

point getTransformationCF(int transform[3], int sgn1[3], int sgn2[3])
{
    point elem;
    elem.x = sgn1[0] * sgn2[transform[0]];
    elem.y = sgn1[1] * sgn2[transform[1]];
    elem.z = sgn1[2] * sgn2[transform[2]];
    return elem;
}

point getCoordsSystem(point p, int rot[3], int sgn[3])
{
    point elem;
    coords2Aux[0] = p.x;
    coords2Aux[1] = p.y;
    coords2Aux[2] = p.z;
    elem.x = sgn[0] * coords2Aux[rot[0]];
    elem.y = sgn[1] * coords2Aux[rot[1]];
    elem.z = sgn[2] * coords2Aux[rot[2]];
    return elem;
}

int main()
{
    char s[2000];
    //at most of length 26
    vector<point> v[100];
    int rot[100][3];
    int sgn[100][3];
    point coords[100];
    int scanner = 0;
    int countt = 0;
    vector<edge> ties[100];
    while (fgets(s, 2000, fin) != NULL)
    {
        int attempt = -1;
        sscanf(s, "--- scanner %d ---", &attempt);
        if (attempt != -1)
            scanner = attempt;
        else
        {
            int x = -1;
            int y = -1;
            int z = -1;
            sscanf(s, "%d,%d,%d", &x, &y,&z);
            if (z == -1)
                continue;
            v[scanner].push_back({x, y, z});
            countt++;
        }
    }
    for (int i = 0; i <= scanner; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rot[i][j] = j;
            sgn[i][j] = 1;
        }
        coords[i] = {0, 0, 0};
    }
    for (int i = 0; i <= scanner; i++)
    {
        for (int j = 0; j <= scanner; j++)
        {
            if (i == j)
                continue;
            for (int k = 0; k < 3; k++)
                for (int ori = 0; ori < 2; ori++)
                    for (int f = 0; f < 4; f++)
                    {
                        map<tuple<int, int, int>, vector<pair<int, int> > > matches;
                        for (int o = 0; o < v[i].size(); o++)
                        {
                            for (int Anca = 0; Anca < v[j].size(); Anca++)
                            {
                                tuple<int, int, int> elem = getTransformation(v[j][Anca], k, ori, f, v[i][o])
                                    .transformIntoTuple();
                                if (matches.find(elem) == matches.end())
                                    matches.insert({elem, vector<pair<int, int> >()});
                                matches[elem].push_back({o, Anca});
                            }
                        }
                        for (auto a: matches)
                        {
                            if (a.second.size() >= 12)
                            {
                                edge b = {j};
                                b.delta[0] = get<0>(a.first);
                                b.delta[1] = get<1>(a.first);
                                b.delta[2] = get<2>(a.first);
                                for (int p = 0; p < 3; p++)
                                {
                                    b.rot[p] = systems[k][transformD[f][p]];
                                    b.sgn[p] = transformF[ori][f][p];
                                }
                                for (auto c: a.second)
                                    assert(getCoordsSystem(v[j][c.second], b.rot, b.sgn) + transformFromArray(b.delta) == v[i][c.first]);
                                ties[i].push_back(b);
                                goto end;
                            }
                        }
                    }
            end:
            continue;
        }
    }
    // we will make the coordinates compared to scanner 0
    set<tuple<int, int, int>> pointsSet;
    bool vis[50];
    for (int i = 0; i <= scanner; i++)
        vis[i] = false;
    queue<int> q;
    q.push(0);
    vis[0] = true;
    while (!q.empty())
    {
        int tp = q.front();
        q.pop();
        for (auto o: v[tp])
        {
            point a = getCoordsSystem(o, rot[tp], sgn[tp]);
            pointsSet.insert((a + coords[tp]).transformIntoTuple());
        }
        for (auto j: ties[tp])
        {
            if (!vis[j.scanner])
            {
                point p = getTransformationCO(rot[tp], j.rot);
                p.saveIntoArray(rot[j.scanner]);
                p = getTransformationCF(rot[tp], sgn[tp], j.sgn);
                p.saveIntoArray(sgn[j.scanner]);
                coords[j.scanner] = getCoordsSystem(transformFromArray(j.delta), rot[tp], sgn[tp]);
                coords[j.scanner] = coords[j.scanner] + coords[tp];
                vis[j.scanner] = true;
                q.push(j.scanner);
            }
        }
    }
    printf("%d\n", pointsSet.size());
    int maxx = 0;
    for (int i = 0; i <= scanner; i++)
        for (int j = 0; j <= scanner; j++)
            maxx = max(maxx, abs(coords[j].x - coords[i].x) + abs(coords[j].y - coords[i].y) + abs(coords[j].z - coords[i].z));
    printf("%d\n", maxx);
    fclose(fin);
}
