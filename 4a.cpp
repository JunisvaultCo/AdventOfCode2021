#include <iostream>
#include <set>
#include <string.h>
#define lol long long

using namespace std;

FILE *fin = fopen("4.in", "r");

int boards[200][5][5];
char list[300];
int nums[300];

bool readBoard(int num)
{
    for (int i = 0; i < 5; i++)
    {
        char s[200];
        char *ptr = s;
        if (fgets(s, 200, fin) == 0)
            return false;
        for (int j = 0; j < 5; j++)
        {
            sscanf(ptr, "%d", &boards[num][i][j]);
            if (j != 4)
            {
                ptr = strchr(ptr, ' ');
                ptr += strcspn(ptr, "0123456789");
            }
        }
        fscanf(fin, "\n");
    }
    fscanf(fin, "\n");
    return true;
}

int main()
{
    fscanf(fin, "%s\n\n", list);
    char *ptr = strtok(list, ",");
    int num = 0;
    while (ptr != NULL)
    {
        nums[num] = atoi(ptr);
        ptr = strtok(NULL, ",");
        num++;
    }
    int countt = 0;
    while (readBoard(countt))
        countt++;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < countt; j++)
            for (int k = 0; k < 5; k++)
                for (int o = 0; o < 5; o++)
                    if (boards[j][k][o] == nums[i])
                        boards[j][k][o] = -1;
        for (int j = 0; j < countt; j++)
        {
            bool winner = false;
            // first, test on each line
            for (int k = 0; k < 5; k++)
                for (int o = 0; o < 5; o++)
                {
                    if (boards[j][k][o] != -1)
                        break;
                    if (o == 4)
                        winner = true;
                }
            // then, test on each collumn
            for (int k = 0; k < 5; k++)
                for (int o = 0; o < 5; o++)
                {
                    if (boards[j][o][k] != -1)
                        break;
                    if (o == 4)
                        winner = true;
                }
            if (winner)
            {
                lol sum = 0;
                for (int k = 0; k < 5; k++)
                    for (int o = 0; o < 5; o++)
                        if (boards[j][k][o] != -1)
                            sum += boards[j][k][o];
                printf("%lld\n", sum * nums[i]);
                exit(0);
            }
        }
    }
}