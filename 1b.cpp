#include <iostream>

int nums[3];

FILE *fin = fopen("1.in", "r");

int main()
{
    int place = 1;
    int sum = -1;
    int prev = -1;
    int countt = 0;
    while (fscanf(fin, "%d", &nums[place % 3]) == 1)
    {
        if (place >= 3)
            sum = nums[0] + nums[1] + nums[2];
        if (prev != -1)
            countt += sum > prev;
        prev = sum;
        place++;
    }
    printf("%d\n", countt);
}