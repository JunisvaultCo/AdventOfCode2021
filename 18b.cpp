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
#define lol long long

using namespace std;

FILE *fin = fopen("18.in", "r");

struct number
{
    lol val = -1;
    number *left = NULL;
    number *right = NULL;
    number *parent = NULL;
    bool isLeft = false;
};

number *formNumber(number *parent, bool isLeft)
{
    number *num = (number *)(malloc(sizeof(number)));
    num->val = -1;
    num->parent = parent;
    num->right = NULL;
    num->left = NULL;
    num->isLeft = isLeft;
    return num;
}

inline char *readNumber(char *s, number *current)
{
    if ((*s) == '\r' || (*s) == '\0' || (*s) == '\n')
        return s;
    if ((*s) >= '0' && (*s) <= '9')
    {
        lol val = 0;
        while ((*s) >= '0' && (*s) <= '9')
        {
            val = val * 10 + (*s) - '0';
            s++;
        }
        current->val = val;
    }
    else
    {
        s++;//ignore the [
        current->left = formNumber(current, true);
        s = readNumber(s, current->left);
        s++; //ignore the ,
        current->right = formNumber(current, false);
        s = readNumber(s, current->right);
        s++;//ignore the ]
    }
    return s;
}

void addToLeft(number *current, int a)
{
    if (current->parent == NULL)
        return;
    if (!current->isLeft)
    {
        current = current->parent->left;
        while (current->val == -1)
            current = current->right;
        current->val += a;
    }
    else
        return addToLeft(current->parent, a);
}

void addToRight(number *current, int a)
{
    if (current->parent == NULL)
        return;
    if (current->isLeft)
    {
        current = current->parent->right;
        while (current->val == -1)
            current = current->left;
        current->val += a;
    }
    else
        return addToRight(current->parent, a);
}

bool explode(number *current, int level)
{
    if (current->val != -1)
        return false;
    if (level == 4)
    {
        addToRight(current, current->right->val);
        addToLeft(current, current->left->val);
        current->val = 0;
        current->left = NULL;
        current->right = NULL;
        return true;
    }
    if (explode(current->left, level + 1))
        return true;
    return explode(current->right, level + 1);
}
bool split(number *current, int level)
{
    if (current->val >= 10)
    {
        current->left = formNumber(current, true);
        current->left->val = current->val / 2;
        current->right = formNumber(current, false);
        current->right->val = current->val - current->left->val;
        current->val = -1;
        return true;
    }
    if (current->val != -1)
        return false;
    if (split(current->left, level + 1))
        return true;
    return split(current->right, level + 1);
}


void print(number *a)
{
    if (a->val != -1)
        printf("%lld", a->val);
    else if (a->left != NULL)
    {
        printf("[");
        print(a->left);
        printf(", ");
        print(a->right);
        printf("]");
    }
}

lol magnitude(number *a)
{
    if (a->val != -1)
        return a->val;
    return magnitude(a->left) * 3 + magnitude(a->right) * 2;
}

lol addition(number *a, number *b)
{
    number *current = (number *)malloc(sizeof(number));
    current->parent = NULL;
    current->val = -1;
    current->left = a;
    current->left->parent = current;
    current->left->isLeft = true;
    current->right = b;
    current->right->parent = current;
    current->right->isLeft = false;
    //marvelous
    //now... to actually reducing the damn number
    while (true)
        if (!explode(current, 0))
            if (!split(current, 0))
                break;
    return magnitude(current);
}

number* copy(number *a)
{
    number *result = (number *)malloc(sizeof(number));
    result->isLeft = a->isLeft;
    result->val = a->val;
    result->parent = a->parent;
    if (result->val == -1)
    {
        result->right = copy(a->right);
        result->right->parent = result;
        result->left = copy(a->left);
        result->left->parent = result;
    }
    else
    {
        result->left = NULL;
        result->right = NULL;
    }
    return result;
}

int main()
{
    char s[2000];
    number v[2000];
    int num = 0;
    while (fgets(s, 2000, fin) != NULL)
    {
        readNumber(s, &(v[num]));
        num++;
    }
    lol maxx = 0;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (i == j)
                continue;
            number *a = copy(&v[i]);
            number *b = copy(&v[j]);
            maxx = max(maxx, addition(a, b));
        }
    }
    printf("%lld\n", maxx);
}
