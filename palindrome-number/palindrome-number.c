#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *reverse(char *num)
{
    int len = strlen(num);
    char *retString = malloc(len+1);
    memset(retString, 0, len+1);
    int i;

    for (i = 0; i < len; i++)
    {
        retString[i] = num[len-1-i];
    }

    return retString;
}

bool isPalindrome(int x)
{
    char num[32];
    char *reversed;

    if (x < 0)
        return false;

    sprintf(num, "%i", x);


    reversed = reverse(num);
    printf("num: %s\n", num);
    printf("reversed: %s\n", reversed);
    printf("strcmp: %d\n", strcmp(reversed, num));

    if (strcmp(reversed, num) == 0)
        return true;
    else
        return false;
}

int
main(int argc, char *argv[])
{
    printf("%d\n", isPalindrome(121));
    return 0;
}
