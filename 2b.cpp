#include <iostream>
#include <string.h>
#define lol long long

FILE *fin = fopen("2.in", "r");

int main()
{
    char s[20];
    int num;
    lol x = 0;
    lol y = 0;
    lol aim = 0;
    while (fscanf(fin, "%s %d\n", s, &num) == 2)
    {
        if (strcmp(s, "forward") == 0)
        {
            x += num;
            y += num * aim;
        }
        if (strcmp(s, "up") == 0)
            aim -= num;
        if (strcmp(s, "down") == 0)
            aim += num;
    }
    printf("%lld\n", x * y);
}