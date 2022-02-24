#include <iostream>
#include <set>
#include <string.h>
#include <algorithm>
#define lol long long

using namespace std;

FILE *fin = fopen("8.in", "r");

int main()
{
    char s[4000];
    int countt = 0;
    while (fgets(s, 4000, fin) != NULL)
    {
        char *ptr = strtok(s, "|");
        // for now we shall ignore the input
        ptr = strtok(NULL, " \r\n");
        while (ptr != NULL)
        {
            int len = strlen(ptr);
            if (len == 2) // we got ourselves a 1 boiiiis
                countt++;
            if (len == 3) // we got ourselves a 7 boiiiis
                countt++;
            if (len == 4) // we got ourselves a 4 boiiiis
                countt++;
            if (len == 7) // we got ourselves a 8 boiiiis
                countt++;
            ptr = strtok(NULL, " \r\n");
        }
    }
    printf("%d\n", countt);
}