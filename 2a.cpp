#include <iostream>
#include <string.h>

FILE *fin = fopen("2.in", "r");

int main()
{
    char s[20];
    int num;
    int x = 0;
    int y = 0;
    while (fscanf(fin, "%s %d\n", s, &num) == 2)
    {
        if (strcmp(s, "forward") == 0)
            x += num;
        if (strcmp(s, "up") == 0)
            y -= num;
        if (strcmp(s, "down") == 0)
            y += num;
    }
    printf("%d\n", x * y);
}