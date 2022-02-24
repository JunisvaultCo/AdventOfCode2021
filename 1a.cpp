#include <iostream>

FILE *fin = fopen("1.in", "r");

int main()
{
    int num;
    int prev = -1;
    int countt = 0;
    while (fscanf(fin, "%d", &num) == 1)
    {
        if (prev == -1)
            prev = num;
        else
        {
            countt += num > prev;
            prev = num;
        }
    }
    printf("%d\n", countt);
}