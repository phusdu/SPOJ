//using memoization
#include<stdio.h>
#include<string.h>

using namespace std;

long long int dp [5010];
char encodedString[5010];

long long int calcDecodes (int length)
{
    if (length == 1 || length == 0)
    {
        dp [0] = 1;
        return 1;
    }

    if (dp [length - 1] != 0)
    {
        return dp [length - 1];
    }

    int num = (encodedString [length - 1] - '0') + ((encodedString [length - 2] - '0') * 10); // number formed by last 2 digits
    if (encodedString [length - 1] != '0' && (num > 9 && num < 27))
    {
        dp [length - 1] = calcDecodes (length - 2) + calcDecodes (length -1);
    }
    else if (encodedString [length - 1] == '0' && (num > 9 && num < 27))
    {
        dp [length - 1] = calcDecodes (length - 2);
    }

    return dp [length - 1];
}

int main() 
{
    long long int numDecodes;
    int i, strLength;

    scanf("%s", encodedString);
    
    while (encodedString[0] != '0')
    {
        strLength = strlen (encodedString);
        for (i = 0; i < strLength; i ++)
        {
            dp [i] = 0;
        }

        numDecodes = calcDecodes (strlen (encodedString) - 1);
        printf("%lli\n", numDecodes);

        scanf("%s", encodedString);
    }

    return 0;
}